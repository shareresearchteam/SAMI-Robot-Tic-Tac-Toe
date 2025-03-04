


import time
import serial
import json

class JamieControl:
    def __init__(self, arduino_port='/dev/ttyUSB0', baud_rate=115200,joint_config_file='/home/antara/JamieExercise/Jamie/Joint_config.json'):
        self.arduino_port = arduino_port
        self.baud_rate = baud_rate
        self.ser = None
        self.joint_map = self.load_joint_config(joint_config_file)
    
    def load_joint_config(self, joint_config_file):
        with open(joint_config_file, 'r') as file:
            joint_config = json.load(file)
        
        joint_map = {}
        for joint in joint_config["JointConfig"]:
            joint_map[joint["JointName"]] = joint["JointID"]
        
        return joint_map

    def initialize_serial_connection(self):
        try:
            # Establish Serial Connection
            self.ser = serial.Serial(self.arduino_port, self.baud_rate, timeout=1)  # 1-second timeout
            time.sleep(2)  # Give the connection time to settle
            print("Serial connection to Arduino established")

            # Example: Send an initial packet to check communication
            packet = [0x3C] #<
            packet.append(0x50) # P
            packet.append(0x01) #power on 
            packet.append(0x45) #everything
            packet.append(0x3E) # >
            self.ser.write(bytearray(packet))
            print (bytearray(packet))  # Short delay for transmission
            print("Data Sent!")

            if self.ser.in_waiting > 0:
                message = self.ser.readline().decode()
                print(f"Arduino Response: {message}")

        except serial.SerialException as e:
            print(f"Failed to connect to Arduino: {e}")

    def send_joint_command(self, joint_ids, joint_angles,joint_time):
        if len(joint_ids) != len(joint_angles):
            raise ValueError("Joint IDs and angles must have the same length.")

        packet = [0x3C, 0x4A, joint_time]
        for joint_id, joint_angle in zip(joint_ids, joint_angles):
            packet.extend([joint_id, joint_angle])
        packet.append(0x3E)

        self.ser.write(bytearray(packet))
        print(f"Sent Joint Command Packet: {bytearray(packet)}")

    def send_emote(self, emote_id):
        packet = [0x3C, 0x45, emote_id, 0x3E]
        self.ser.write(bytearray(packet))
        print(f"Sent Emote Command Packet: {bytearray(packet)}")
        time.sleep(1)

    def close_connection(self):
        if self.ser:
            self.ser.close()
            print("Serial connection closed.")

    def read_json(self, filename):
        with open(filename, 'r') as file:
            data = json.load(file)
        for keyframe in data["Keyframes"]:
            if keyframe["HasEmote"] == "True":
                self.send_emote(1) # eventually this will also be json
            
            if keyframe["HasJoints"] == "True" :
                joint_ids=[]
                joint_angles = []
                joint_time = keyframe["JointMoveTime"]
                for joint in keyframe["JointAngles"]:
                    joint_ids.append(self.get_joint_id(joint["Joint"]))
                    joint_angles.append(joint["Angle"])
                self.send_joint_command(joint_ids, joint_angles,joint_time)
            
            time.sleep(keyframe["WaitTime"] / 1000)

    #gets joint ids from joint config file
    def get_joint_id(self, joint_name): 
        return self.joint_map.get(joint_name, 0)

def main():
    robot = JamieControl()
    robot.initialize_serial_connection()
    time.sleep(1)
    test= robot.read_json("/home/antara/JamieExercise/Jamie/Wave.json")
    print(test)
    time.sleep(1)
    robot.close_connection()

if __name__ == "__main__":
    main()
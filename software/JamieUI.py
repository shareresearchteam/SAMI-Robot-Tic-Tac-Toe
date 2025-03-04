import time
import serial
import json
import os
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLabel, QLineEdit, QComboBox

class JamieControl(QWidget):
    def __init__(self, arduino_port='/dev/ttyUSB0', baud_rate=115200, joint_config_file='/home/antara/JamieExercise/Jamie/Joint_config.json', behavior_folder='/home/antara/JamieExercise/Jamie/behaviors'):
        super().__init__()
        self.arduino_port = arduino_port
        self.baud_rate = baud_rate
        self.ser = None
        self.joint_config = self.load_joint_config(joint_config_file)
        self.joint_map = {joint['JointName']: joint for joint in self.joint_config}
        self.behavior_folder = behavior_folder if os.path.exists(behavior_folder) else '/home/antara/JamieExercise/Jamie/behaviors'

        self.initUI()
        self.initialize_serial_connection()

    def delay(self, t):
        time.sleep(t)

    # Load joint configuration from file
    def load_joint_config(self, joint_config_file):
        with open(joint_config_file, 'r') as file:
            return json.load(file)['JointConfig']
    #Load behaviors from folder
    def load_behavior(self, behavior_file):
        with open(behavior_file, 'r') as file:
            return json.load(file)['Keyframes']

    # Initialize serial connection
    def initialize_serial_connection(self):
        try:
            self.ser = serial.Serial(self.arduino_port, self.baud_rate, timeout=1)
            self.delay(2)
            print("Serial connection to Arduino established")

            packet = [0x3C, 0x50, 0x01, 0x45, 0x3E]
            self.ser.write(bytearray(packet))
            print("Data Sent: ", bytearray(packet))

            if self.ser.in_waiting > 0:
                message = self.ser.readline().decode()
                print(f"Arduino Response: {message}")

        except serial.SerialException as e:
            print(f"Failed to connect to Arduino: {e}")

    # Send joint command
    def send_joint_command(self, joint_ids, joint_angles, joint_time):
        if len(joint_ids) != len(joint_angles):
            raise ValueError("Joint IDs and angles must have the same length.")

        packet = [0x3C, 0x4A, joint_time]
        for joint_id, joint_angle in zip(joint_ids, joint_angles):
            packet.extend([joint_id, joint_angle])
        packet.append(0x3E)

        self.ser.write(bytearray(packet))
        print(f"Sent Joint Command Packet: {bytearray(packet)}")

    # Close serial connection
    def close_connection(self):
        if self.ser:
            self.ser.close()
            print("Serial connection closed.")
    def initUI(self):
        self.resize(600, 400)
        layout = QVBoxLayout()

        self.joint_name_dropdown = QComboBox(self)
        self.joint_name_dropdown.addItems(self.joint_map.keys())
        layout.addWidget(self.joint_name_dropdown)

        self.angle_input = QLineEdit(self)
        self.angle_input.setPlaceholderText("Enter Angle")
        layout.addWidget(self.angle_input)

        self.time_input = QLineEdit(self)
        self.time_input.setPlaceholderText("Enter Move Time")
        layout.addWidget(self.time_input)

        send_button = QPushButton("Send Command", self)
        send_button.clicked.connect(self.handle_send_command)
        layout.addWidget(send_button)

        home_button = QPushButton("Home", self)
        home_button.clicked.connect(self.move_to_home)
        layout.addWidget(home_button)

        self.behavior_dropdown = QComboBox(self)
        self.behavior_dropdown.addItems(self.get_behavior_files())
        layout.addWidget(self.behavior_dropdown)

        behavior_button = QPushButton("Perform Behavior", self)
        behavior_button.clicked.connect(self.perform_behavior)
        layout.addWidget(behavior_button)

        

        self.setLayout(layout)
        self.setWindowTitle("Jamie Control")
        self.show()

    def get_joint_id(self, joint_name):
        return self.joint_map[joint_name]['JointID']

    def get_home_angle(self, joint_name):
        return self.joint_map[joint_name]['HomeAngle']

    def handle_send_command(self):
        joint_name = self.joint_name_dropdown.currentText()
        angle = int(self.angle_input.text())
        move_time = int(self.time_input.text())

        joint_id = self.get_joint_id(joint_name)

        self.send_joint_command([joint_id], [angle], move_time)

    def move_to_home(self):
        joint_ids = [joint['JointID'] for joint in self.joint_config]
        home_angles = [joint['HomeAngle'] for joint in self.joint_config]
        self.send_joint_command(joint_ids, home_angles, 1)

    def get_behavior_files(self):
        return [f for f in os.listdir(self.behavior_folder) if f.endswith('.json')]

    def perform_behavior(self):
        selected_behavior = self.behavior_dropdown.currentText()
        behavior_path = os.path.join(self.behavior_folder, selected_behavior)
        behavior_motion = self.load_behavior(behavior_path)

        for frame in behavior_motion:
            joint_ids = [self.get_joint_id(j['Joint']) for j in frame['JointAngles']]
            angles = [j['Angle'] for j in frame['JointAngles']]
            move_time = frame['JointMoveTime']

            self.send_joint_command(joint_ids, angles, move_time)
            self.delay(frame['WaitTime'] / 1000)

    def closeEvent(self, event):
        self.close_connection()
        event.accept()

def main():
    app = QApplication([])
    window = JamieControl()
    app.exec_()

if __name__ == "__main__":
    main()

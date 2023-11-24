from robot_hat import PWM, Servo
from robot_hat.utils import reset_mcu
from time import sleep

import motor_setup

reset_mcu()
sleep(0.2)

if __name__ == '__main__':
#     P_0 = Servo(PWM('P0'))         
#     P_0.angle(0)
#     P_1 = Servo(PWM('P1'))         
#     P_1.angle(0)
    motor_setup.from_json('./simple_config.json')
    
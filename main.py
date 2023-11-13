#!/usr/bin/env python3
import logging
import json

# Robot HAT specifics
from robot_hat import Servo, PWM

# This logger should always provides the config as extra
logger = logging.getLogger(__name__)


# Using the robot hat
def create_motor(pin, starting_angle = 0)
    ser = Servo(PWM(pin))                      # create a Servo object
    val = ser.angle(60)                   # set the servo angle
    return ser

def from_config(config, strict=True, sync=True, use_dummy_io=False, **extra):
    """ Returns a :class:`~pypot.robot.robot.Robot` instance created from a configuration dictionnary.

        :param dict config: robot configuration dictionary
        :param bool strict: make sure that all ports, motors are availaible.
        :param bool sync: choose if automatically starts the synchronization loops

        For details on how to write such a configuration dictionnary, you should refer to the section :ref:`config_file`.

        """
    logger.info('Loading config... ', extra={'config': config})

    alias = config['motorgroups']

    # Instatiate the different motor controllers
    controllers = []
    for c_name, c_params in config['controllers'].items():
        motor_names = sum([_motor_extractor(alias, name)
                           for name in c_params['attached_motors']], [])

        attached_motors = [motor_from_confignode(config, name)
                           for name in motor_names]

    #     # at least one of the motor is set as broken
    #     if [m for m in attached_motors if m._broken]:
    #         strict = False

    #     attached_ids = [m.id for m in attached_motors]
    #     if not use_dummy_io:
    #         dxl_io = dxl_io_from_confignode(config, c_params, attached_ids, strict)

    #         check_motor_eprom_configuration(config, dxl_io, motor_names)

    #         logger.info('Instantiating controller on %s with motors %s',
    #                     dxl_io.port, motor_names,
    #                     extra={'config': config})

    #         syncloop = (c_params['syncloop'] if 'syncloop' in c_params
    #                     else 'BaseDxlController')
    #         SyncLoopCls = getattr(pypot.dynamixel.syncloop, syncloop)

    #         c = SyncLoopCls(dxl_io, attached_motors)
    #         controllers.append(c)
    #     else:
    #         controllers.append(DummyController(attached_motors))

    # try:
    #     robot = Robot(motor_controllers=controllers, sync=sync)
    # except RuntimeError:
    #     for c in controllers:
    #         c.io.close()

    #     raise

    # make_alias(config, robot)

    # # Create all sensors and attached them
    # try:
    #     if 'sensors' in config and not use_dummy_io:
    #         sensors = []
    #         for s_name in config['sensors'].keys():
    #             if s_name in extra and extra[s_name] == 'dummy':
    #                 config['sensors'][s_name]['type'] = 'Dummy{}'.format(s_name.capitalize())

    #             sensor = sensor_from_confignode(config, s_name, robot)
    #             setattr(robot, s_name, sensor)
    #             sensors.append(sensor)
    #             robot.sensors.append(sensor)

    #         [s.start() for s in sensors if hasattr(s, 'start')]

    # # If anything goes wrong when adding sensors
    # # We have to make sure we close the robot properly
    # # Otherwise trying to open it again will fail.
    # except Exception:
    #     robot.close()
    #     raise

    # logger.info('Loading complete!',
    #             extra={'config': config})

    # return robot

def from_json(json_file, sync=True, strict=True, use_dummy_io=False, **extra):
    """ Returns a :class:`~pypot.robot.robot.Robot` instance created from a JSON configuration file.

    For details on how to write such a configuration file, you should refer to the section :ref:`config_file`.

    """
    with open(json_file) as f:
        config = json.load(f, object_pairs_hook=OrderedDict)
    return from_config(config, sync=sync, strict=strict, use_dummy_io=use_dummy_io, **extra)

def _motor_extractor(alias, name):
    motors = []

    if name not in alias:
        return [name]

    for key in alias[name]:
        motors += _motor_extractor(alias, key) if key in alias else [key]
    return motors

def motor_from_confignode(config, motor_name):
    params = config['motors'][motor_name]

    type = params['type']
    if type == 'MG996R':
        m = create_motor(params['pin'])
    # elif type == 'XL-320':
    #     MotorCls = pypot.dynamixel.motor.DxlXL320Motor
    # elif type == 'MX-64' or type == 'MX-106':
    #     MotorCls = pypot.dynamixel.motor.DxlMX64106Motor
    # elif type.startswith('MX'):
    #     MotorCls = pypot.dynamixel.motor.DxlMXMotor
    # elif type.startswith('AX') or type.startswith('RX'):
    #     MotorCls = pypot.dynamixel.motor.DxlAXRXMotor
    # elif type.startswith('SR'):
    #     MotorCls = pypot.dynamixel.motor.DxlSRMotor

    # broken = 'broken' in params and params['broken']

    # if 'wheel_mode' in params and params['wheel_mode']:
    #     params['angle_limit'] = (0, 0)

    # m = MotorCls(id=params['id'],
    #              name=motor_name,
    #              model=type,
    #              direct=True if params['orientation'] == 'direct' else False,
    #              offset=params['offset'],
    #              broken=broken,
    #              angle_limit=params['angle_limit'])

    # logger.info("Instantiating motor '%s' id=%d direct=%s offset=%s",
    #             m.name, m.id, m.direct, m.offset,
    #             extra={'config': config})

    return m
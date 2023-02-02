1. set_tacho_command_inx()

The function takes three arguments:

    int motor: the index of the motor

    int command: the command you want to set for the motor. This can be one of the following values:
        TACHO_RUN_FOREVER: Run the motor indefinitely.
        TACHO_RUN_TIMED: Run the motor for a specified amount of time.
        TACHO_RUN_TO_REL_POS: Run the motor to a relative position.
        TACHO_RUN_TO_ABS_POS: Run the motor to an absolute position.
        TACHO_STOP: Stop the motor immediately.
        TACHO_RESET: Reset the motor.

    int value: The value to be used with the command. The meaning of this value depends on the command being used. For example, if the TACHO_RUN_TIMED command is used, the value argument should be the number of milliseconds to run the motor. If the TACHO_RUN_TO_REL_POS command is used, the value argument should be the number of degrees to run the motor.

2. set_tacho_speed_sp()

The function takes two arguments:

    int motor: the index of the motor

    int speed: the target speed you want to set for the motor. This should be a value between -100 and 100, where negative values indicate that the motor should run in reverse.

3. Modes of sensors

Gyro sensor:

    Mode 0: Angular velocity
    Mode 1: Angle
    Mode 2: Rotational speed

Touch sensor:

    Mode 0: Touch
    Mode 1: Bounce

Color sensor:

    Mode 0: Reflected light intensity
    Mode 1: Ambient light intensity
    Mode 2: Color
    Mode 3: Reflective or ambient
    Mode 4: RGB color
    Mode 5: Raw reflected
    Mode 6: Raw color components
    Mode 7: Calibrated reflected
    Mode 8: Calibrated color components

Ultrasonic sensor:

    Mode 0: Distance
    Mode 1: Presence
    Mode 2: Continuous measurement
    Mode 3: Listen



set_sensor_mode_inx(0, 0);



# Applications
psudo-code:
turn around: make one motor rolls and the other fixes. Choose the running to forever until the gyro show 90 degree
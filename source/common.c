#include "../include/common.h"

// motors[0] is left
// motors[1] is right
// COMMON MOVING FUNCTION
void stop_motor(uint8_t motor){
    set_tacho_command_inx(motor, TACHO_STOP);
}

void go_forwards_forever(uint8_t *motors, int speed) {
    multi_set_tacho_stop_action_inx(motors, TACHO_BRAKE);
    set_tacho_speed_sp( motors[0], speed);
	set_tacho_speed_sp( motors[1], speed);
    set_tacho_command_inx(motors[0], TACHO_RUN_TIMED);
    set_tacho_command_inx(motors[1], TACHO_RUN_TIMED);
}


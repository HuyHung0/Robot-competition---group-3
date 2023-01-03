#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SLEEP_TIME 1000

int main(void)
{
    // Initialize the EV3
    if ( ev3_init() == -1 ) return ( 1 );

    // Open the tacho motors
    tacho_desc_t arm_motor;
    if ( ev3_search_tacho_plugged_in(PORT_D, 0, &arm_motor, 0 ) == 0) {
        printf( "Tacho motor is found\n" );
    } else {
        printf( "Tacho motor is NOT found\n" );
        return ( 1 );
    }

    // Set the arm motor to run at 50% power for 3 seconds
    set_tacho_stop_action_inx( arm_motor.port, TACHO_COAST );
    set_tacho_speed_sp( arm_motor.port, 50 );
    set_tacho_time_sp( arm_motor.port, 3 );
    set_tacho_command_inx( arm_motor.port, TACHO_RUN_TIMED );

    // Wait for the arm to move
    sleep( 3 );

    // Close the tacho motors
    ev3_uninit();

    return 0;
}
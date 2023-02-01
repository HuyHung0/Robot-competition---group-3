#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#define PORT_LEFT 66 ///< Left motor port
#define PORT_RIGHT 67 ///< Right motor port
#define COLOR_SENSOR_MODE COL-REFLECT
#define ANGLE_THRESHOLD 5 ///< Gyro angle precision

// WIN32 ///
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

#endif
const char *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static int _validate_speed(int speed, int max_speed){
    if(speed == 0){
        speed = max_speed;
    }
    if (abs(speed) > max_speed){
        printf("Speed %d cannot be bigger than max_speed %d\n", speed, max_speed);
        return 0;
    }
    return speed;
}

int main(void){
    int val;
    int result;
    int speed = 20;
    int max_speed;
    // uint8_t sn; // Sequence number
    uint8_t sn_color; // Sequence number for color
    // uint8_t sn_sonar; //Sense the wall to turn left and right//
    uint8_t sn_motor_left;
    uint8_t sn_motor_right;

    #ifndef __ARM_ARCH_4T__
    /* Disable auto-detection of the brick (you have to set the correct address below) */
    // ev3_brick_addr = "192.168.0.204";

    #endif
    if ( ev3_init() == -1 ) return ( 1 );

    #ifndef __ARM_ARCH_4T__
    // printf( "The EV3 brick auto-detection is DISABLED,\nwaiting %s online with plugged tacho...\n", ev3_brick_addr );

    #else
    printf( "Waiting tacho is plugged...\n" );

    #endif
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

    printf( "*** ( EV3 ) Hello! ***\n" );

    //Run all sensors
    ev3_sensor_init();

    // Init movement
    int max_speed_left;
    int max_speed_right;
    while (ev3_tacho_init() < 1)
        sleep(1);
    ev3_search_tacho_plugged_in(PORT_LEFT, 0, &sn_motor_left, 0);
    ev3_search_tacho_plugged_in(PORT_RIGHT, 0, &sn_motor_right, 0);
    get_tacho_max_speed(sn_motor_left, &max_speed_left);
    get_tacho_max_speed(sn_motor_right, &max_speed_right);
    max_speed = max_speed_right > max_speed_left ? max_speed_left : max_speed_right;
    // End of init movement

    if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        printf( "COLOR sensor is found, reading COLOR...\n" );
        set_sensor_mode( sn_color, "COL-COLOR");
        for ( ; ; ){
            // Run motor
            speed = _validate_speed(speed, max_speed);
            set_tacho_speed_sp(sn_motor_left, speed);
            set_tacho_command_inx(sn_motor_left, TACHO_RUN_TIMED);
            set_tacho_speed_sp(sn_motor_right, speed);
            set_tacho_command_inx(sn_motor_right, TACHO_RUN_TIMED);

            if (!get_sensor_value( 0, sn_color, &val )) {
                val = 0;
            }else {
                get_sensor_value( 0, sn_color, &val );
            }
            
            printf( "\r(%s) value color \n", color[val]);
            // if (color[ val ] == color[3]){
            if (val == 4){
                // result = 1;
                printf( "Is the robot detect the line\r(%d) \n", result);
                // Stop action
                set_tacho_stop_action_inx(sn_motor_left, TACHO_COAST);
                set_tacho_command_inx(sn_motor_left, TACHO_STOP);
                set_tacho_stop_action_inx(sn_motor_right, TACHO_COAST);
                set_tacho_command_inx(sn_motor_right, TACHO_STOP);
                // Randomly choose to go left or right
                // Use sonor sensor to detect the wall
                // In an suitable distance, Running around the base.
            }
            printf( "Is the robot detect the line\r(%d) \n", result);
            fflush( stdout );
        }
    }

    ev3_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );

    return ( 0 );
}

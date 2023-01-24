#include "../include/common.h"

#define PORT_LEFT 66 ///< Left motor port
#define PORT_RIGHT 67 ///< Right motor port

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
    int speed = 20;
    int max_speed;
    // uint8_t sn_sonar; //Sense the wall to turn left and right//
    uint8_t sn_motors[2];

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
    ev3_search_tacho_plugged_in(PORT_LEFT, 0, &sn_motors[0], 0);
    ev3_search_tacho_plugged_in(PORT_RIGHT, 0, &sn_motors[1], 0);
    get_tacho_max_speed(sn_motors[0], &max_speed_left);
    get_tacho_max_speed(sn_motors[1], &max_speed_right);
    max_speed = max_speed_right > max_speed_left ? max_speed_left : max_speed_right;
    // End of init movement


    for ( ; ; ){
        // Run motor
        speed = _validate_speed(speed, max_speed);
        go_forwards_forever(sn_motors, speed);
    }

    ev3_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );

    return ( 0 );
}

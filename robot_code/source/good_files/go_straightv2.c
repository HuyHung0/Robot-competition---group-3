// LEHuyHung
// This code to make the robot go straigt forward by setting left and right motors with the same information.
// max_speed: 1050
// speed set to motor: 2/3 * max_speed = 700
// run time: 5s
// ram_up: 2s
// ram_down: 2s
// distance travel: around 165 cm. However, we didn't put the grabber to avoid run other by mistake. So it may heavier in real life and travel shorter.
// also, the surface not very flat


#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"


#define MAX_SPEED = 1050
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

//mostly we put time_ram_up=time_ram_down=0
void go_straight(uint8_t sn, int speed, int time_total, int time_ram_up, int time_ram_down){

	//set information for the motors
	set_tacho_stop_action_inx( sn, TACHO_COAST );
	set_tacho_speed_sp( sn, speed );
	set_tacho_time_sp( sn, time_total );
	set_tacho_ramp_up_sp( sn, time_ram_up );
	set_tacho_ramp_down_sp( sn, time_ram_down );
	set_tacho_command_inx( sn, TACHO_RUN_TIMED );
}

int main( void )
{
	int i;
	char s[ 256 ];

#ifndef __ARM_ARCH_4T__
	/* Disable auto-detection of the brick (you have to set the correct address below) */
	ev3_brick_addr = "192.168.0.204";

#endif
	if ( ev3_init() == -1 ) return ( 1 );

#ifndef __ARM_ARCH_4T__
	printf( "The EV3 brick auto-detection is DISABLED,\nwaiting %s online with plugged tacho...\n", ev3_brick_addr );

#else
	printf( "Waiting tacho is plugged...\n" );

#endif
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Found tacho motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
			printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
			printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
		}
	}
	
	// run left and right motor

	uint8_t sn_left;	//pointer to the address of left motor (red motor)
	uint8_t sn_right;	//pointer to the address of left motor (red motor)

	int port_left = 66;
	int port_right = 67;
	
	int speed, time_total, time_ram_up;

	//read and store information of left and right motors
	ev3_search_tacho_plugged_in(port_left,0, &sn_left, 0 );
	ev3_search_tacho_plugged_in(port_right,0, &sn_right, 0 );

	printf("input the speed. It should be less than 1050 (maxspeed). Input negative number for go back:\n");
	scanf("%d",&speed);
	printf("input total run time (in ms): \n");
	scanf("%d", &time_total);
	printf("input ram up and down time (in ms): \n");
	scanf("%d", &time_ram_up);

	printf("it is running:...\n");
	go_straight(sn_left,speed,time_total,time_ram_up,time_ram_up);
	go_straight(sn_right,speed,time_total,time_ram_up,time_ram_up);

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

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
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

int main( void )
{
	int i;
	uint8_t sn;
	FLAGS_T state;
	uint8_t sn_touch;
	uint8_t sn_color;
	uint8_t sn_compass;
	uint8_t sn_sonar;
	uint8_t sn_mag;
	char s[ 256 ];
	int val;
	float value;
	uint32_t n, ii;
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

	uint8_t sn_orange;  //pointer to address of orange motor
	uint8_t sn_left;	//pointer to the address of left motor (red motor)
	uint8_t sn_right;	//pointer to the address of left motor (red motor)
	uint8_t sn_weak;	//pointer to address of weak motor (no color)

	int port_orange = 65;	//corresponding port of the cable
	int port_left = 66;
	int port_right = 67;
	int port_weak = 68;
	

	int max_speed_left;
	int max_speed_right;

	//read and store information of left and right motors
	ev3_search_tacho_plugged_in(port_left,0, &sn_left, 0 );
	ev3_search_tacho_plugged_in(port_right,0, &sn_right, 0 );

	get_tacho_max_speed( sn_left, &max_speed_left );
	printf("  max speed_left = %d\n", max_speed_left );
	get_tacho_max_speed( sn_right, &max_speed_right );
	printf("  max speed_right = %d\n", max_speed_right );
	
	//set information for the left motors
	set_tacho_stop_action_inx( sn_left, TACHO_COAST );
	set_tacho_speed_sp( sn_left, max_speed_left * 2 / 3 );
	set_tacho_time_sp( sn_left, 5000 );
	set_tacho_ramp_up_sp( sn_left, 2000 );
	set_tacho_ramp_down_sp( sn_left, 2000 );
	set_tacho_command_inx( sn_left, TACHO_RUN_TIMED );

	//set information for the right motors
	set_tacho_stop_action_inx( sn_right, TACHO_COAST );
	set_tacho_speed_sp( sn_right, max_speed_right * 2 / 3 );
	set_tacho_time_sp( sn_right, 5000 );
	set_tacho_ramp_up_sp( sn_right, 2000 );
	set_tacho_ramp_down_sp( sn_right, 2000 );
	set_tacho_command_inx( sn_right, TACHO_RUN_TIMED );
	

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

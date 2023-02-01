// Test finger motor with input
// Speed negative to close finger, possitive to open finger
// Speed 200 is good. Max is 1650
// Time 4.5 is good (for close to open)

#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

// WIN32 //////////Keep this block///////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX /
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

#endif
//////////////////////////////////////////////////


const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))



//////****** check pressed for touch sensor 
static bool _check_pressed( uint8_t sn )
{
	int val;

	if ( sn == SENSOR__NONE_ ) {
		return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
	}
	return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}
//////******

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


//-------------------Keep this block
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
//-------------------
	
	
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );


//*********find motors
	printf( "Found tacho motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
			printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
			printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
		}
	}
//*********



	uint8_t sn_left;	//pointer to the address of left motor (red motor)
	uint8_t sn_right;	//pointer to the address of left motor (red motor)

	uint8_t sn_arm;
	uint8_t sn_finger;

	int port_left = 66;
	int port_right = 67;
	int port_arm = 65;
	int port_finger = 68;
	
	int max_speed, speed;
	float time_total;

	//read and store information of left and right motors
	ev3_search_tacho_plugged_in(port_left,0, &sn_left, 0 );
	ev3_search_tacho_plugged_in(port_right,0, &sn_right, 0 );
	ev3_search_tacho_plugged_in(port_arm,0, &sn_arm, 0 );
	ev3_search_tacho_plugged_in(port_finger,0, &sn_finger, 0 );


	get_tacho_max_speed( sn_left, &max_speed );
	printf(" Motor left port 66 max speed = %d\n", max_speed );
	get_tacho_max_speed( sn_right, &max_speed );
	printf(" Motor right port 67 max speed = %d\n", max_speed );
	get_tacho_max_speed( sn_arm, &max_speed );
	printf(" Motor arm port 65 max speed = %d\n", max_speed );
	get_tacho_max_speed( sn_finger, &max_speed );
	printf(" Motor finger port 68 max speed = %d\n", max_speed );
	
	
	
	printf("Input the speed:\n");
	printf("Negative to close finger, Possitive to open finger.\n");
	printf("200 is ok. It should be less than 1560 (maxspeed):\n");
	scanf("%d",&speed);
	printf("input total run time (in s, can be float number). 4.5s is ok: \n");
	scanf("%f", &time_total);

	set_tacho_speed_sp( sn_finger, speed );
	set_tacho_time_sp( sn_finger, time_total*1000 );
	set_tacho_command_inx( sn_finger, TACHO_RUN_TIMED );

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

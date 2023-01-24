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

	uint8_t sn_color;
	uint8_t sn_compass;
	uint8_t sn_sonar;
	uint8_t sn_mag;
	uint8_t sn_gyro;

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
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
//-------------------



	printf( "*** ( EV3 ) Hello! ***\n" );


// //*********find motors
// 	printf( "Found tacho motors:\n" );
// 	for ( i = 0; i < DESC_LIMIT; i++ ) {
// 		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
// 			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
// 			printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
// 			printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
// 		}
// 	}
// //*********



	// //Run motors in order from port A to D
	// int port=65;
	// for (port=65; port<69; port++){
	// 	if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
	// 		int max_speed;

	// 		printf( "LEGO_EV3_M_MOTOR 1 is found, run for 5 sec...\n" );
	// 		get_tacho_max_speed( sn, &max_speed );
	// 		printf("  max speed = %d\n", max_speed );
	// 		set_tacho_stop_action_inx( sn, TACHO_COAST );
	// 		set_tacho_speed_sp( sn, max_speed * 2 / 3 );
	// 		set_tacho_time_sp( sn, 5000 );
	// 		set_tacho_ramp_up_sp( sn, 2000 );
	// 		set_tacho_ramp_down_sp( sn, 2000 );
	// 		set_tacho_command_inx( sn, TACHO_RUN_TIMED );
	// 		/* Wait tacho stop */
	// 		Sleep( 100 );
	// 		do {
	// 			get_tacho_state_flags( sn, &state );
	// 		} while ( state );
	// 		printf( "run to relative position...\n" );
	// 		set_tacho_speed_sp( sn, max_speed / 2 );
	// 		set_tacho_ramp_up_sp( sn, 0 );
	// 		set_tacho_ramp_down_sp( sn, 0 );
	// 		set_tacho_position_sp( sn, 90 );
	// 		for ( i = 0; i < 8; i++ ) {
	// 			set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
	// 			Sleep( 500 );
	// 		}

	// 	} else {
	// 		printf( "LEGO_EV3_M_MOTOR 1 is NOT found\n" );
	// 	}
	// }

	//Run all sensors
	ev3_sensor_init();

	printf( "Found sensors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
			printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
			if ( get_sensor_mode( i, s, sizeof( s ))) {
				printf( "  mode = %s\n", s );
			}
			if ( get_sensor_num_values( i, &n )) {
				for ( ii = 0; ii < n; ii++ ) {
					if ( get_sensor_value( ii, i, &val )) {
						printf( "  value%d = %d\n", ii, val );
					}
				}
			}
		}
	}


	//Found sensor and assign the address for these sensors
	if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
		printf("Untrasonic sensor found!\n");
	}
	if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
		printf( "Color sensor is found!\n" );
	}
	if (ev3_search_sensor(LEGO_EV3_GYRO, &sn_gyro,0)){
		printf("Gyro sensor found!\n");
	}
	if (ev3_search_sensor(HT_NXT_COMPASS, &sn_compass,0)){
		printf("Compass sensor found!\n");
	}
	
	
	printf("************");
	Sleep(200);

	float ini_value;
	if ( !get_sensor_value0(sn_gyro, &ini_value )) {
		value = 0;
	}

	printf("Initial value of gyro sensor is %f\n", ini_value);
	
	Sleep( 200 );
	float angle = 0;
	while(angle < 90){
		get_sensor_value0(sn_gyro, &value );
		angle = abs(value - ini_value);
		printf("\r value:%f\n",angle);
		fflush( stdout );
		Sleep(200);
	}
	printf("stop!");
	

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

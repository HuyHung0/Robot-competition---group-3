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
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
//-------------------



	printf( "*** ( EV3 ) Hello! ***\n" );

	//Run all sensors
	ev3_sensor_init();

	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
			ev3_sensor_port_name( i, s );
            printf(" Name = %s\n",s);
			printf("  Port = %s\n", ev3_sensor_port_name( i, s ));
            
            printf("  ev3_sensor_type( ev3_sensor[ %d ].type_inx =   %s\n", i, ev3_sensor_type( ev3_sensor[ i ].type_inx ));
			if ( get_sensor_mode( i, s, sizeof( s ))) {
				printf( "  Mode = %s\n", s );
			}
		}
	}
	

	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

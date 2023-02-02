//Define Libraries
#include <stdarg.h>
#include <time.h>
#include <sys/socket.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "/home/robot/ev3dev-c/source/ev3/ev3.h"
#include "/home/robot/ev3dev-c/source/ev3/ev3_port.h"
#include "/home/robot/ev3dev-c/source/ev3/ev3_tacho.h"
#include "/home/robot/ev3dev-c/source/ev3/ev3_sensor.h"
#include "/home/robot/ev3dev-c/source/ev3/ev3_dc.h"
#include "/home/robot/ev3dev-c/source/ev3/brick.h"
#define MAX_SPEED 1050
uint8_t motors[4];
uint8_t sn_color;
int val;
int result;
//#define STOP_ACTION TACHO_BRAKE
//#define WHEEL_RADIUS 0.0275
//#define COMP_SX -1.0
//#define COMP_DX -1.0000
int IMAX;


//Define Motors
#define MOT_SX 66
#define MOT_DX 67

//Initialisation
int motor_init(uint8_t *motor0, uint8_t *motor1);
void go_forwards_cm_foratime(uint8_t *motors, float cm, int speed);
void go_backwards_cm_foratime(uint8_t *motors, float cm, int speed);
void turn_right_motors(uint8_t *motors, int speed, int deg);


//Color Detection
const char *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))


//Main program
int main(void)
{
	int run = 1;

	if(run == 1){
		motor_init( &motors[0], &motors[1]);
		ev3_sensor_init();
	}

	while (run == 1){
	if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        printf( "COLOR sensor is found, reading COLOR...\n" );
        set_sensor_mode( sn_color, "COL-COLOR");
        for ( ; ; ){
			go_forwards_cm_foratime(motors, 10, MAX_SPEED/10);
			if (!get_sensor_value( 0, sn_color, &val )) {
                val = 0;
            }else {
                get_sensor_value( 0, sn_color, &val );
            }
            printf( "\r(%s) value color \n", color[val]);


        	if (val == 4){
            printf( "Is the robot detect the line\r(%d) \n", result);
			turn_right_motors(motors, MAX_SPEED/10, 90);
			go_forwards_cm_foratime(motors, 50, MAX_SPEED/10);
			}

			printf( "Is the robot detect the line\r(%d) \n", result);
        	fflush( stdout );
		}
	}

	} return run;
}

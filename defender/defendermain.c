/*Author of this file : Ikhwan, Khairul */


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

//Main program
int main(void)
{
	int run = 1;

	if(run == 1){
		motor_init( &motors[0], &motors[1]);
	}

	while (run == 1){
		go_forwards_cm_foratime(motors, 3, MAX_SPEED/3);
		turn_right_motors(motors, MAX_SPEED/10, 90);
		go_forwards_cm_foratime(motors, 10, MAX_SPEED/3);
		turn_right_motors(motors, MAX_SPEED/10, 90);
		go_forwards_cm_foratime(motors, 10, MAX_SPEED/3);
		turn_right_motors(motors, MAX_SPEED/10, 90);
		go_forwards_cm_foratime(motors, 10, MAX_SPEED/3);
		turn_right_motors(motors, MAX_SPEED/10, 90);
		go_forwards_cm_foratime(motors, 10, MAX_SPEED/3);
		turn_right_motors(motors, MAX_SPEED/10, 90);
		go_forwards_cm_foratime(motors, 10, MAX_SPEED/3);
		//go_backwards_cm_foratime(motors, 115, MAX_SPEED/3);
		//go_forwards_cm_foratime(motors, 57.5, MAX_SPEED/3);
		return run;
	} return run;

		//ev3_uninit();
       	//printf( "*** ( EV3 ) Bye! ***\n" );
        //close();
        //return 0;

}

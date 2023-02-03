/*Author of this file*/
//Main Function : Ikhwan
//Function used in this main file : Ikhwan, Khai Nguyen, Khairul, Hung


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


#ifdef _WIN32_
#include <windows.h>
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#endif


//Define Motors
#define MOT_SX 66
#define MOT_DX 67
#define ARM 68
#define PINCER 65
#define COLOR_SENSOR_MODE COL-REFLECT //Khai Nguyen

//Initialisation
int motor_init(uint8_t *motor0, uint8_t *motor1, uint8_t *arm, uint8_t *pincer); //Ikhwan
void go_forwards_cm_foratime(uint8_t *motors, float cm, int speed); //Ikhwan & Khairul
void go_backwards_cm_foratime(uint8_t *motors, float cm, int speed); //Ikhwan & Khairul
void turn_right_motors(uint8_t *motors, int speed, int deg); //Ikhwan & Khairul
void turn_left_motors(uint8_t *motors, int speed, int deg); //Ikhwan & Khairul
void go_forwards_cm_forever(uint8_t *motors, int speed); //Ikhwan & Khairul
void stop_motor(uint8_t motor); //Ikhwan & Khairul
void control_arm(int speed, float time); //Khairul & Ikhwan
void control_pincer(int speed, float time); //Khairul & Ikhwan
void grab_ball(); //Khairul & Hung
void reset_pincer(); //Khairul & Hung

//Khai Nguyen
//Define Colors
const char *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

//Main program
int main(void)
{
        int val;
        uint8_t sn_sonar;
        uint8_t sn_color;
        float value;
        float range = 77; //Hung (Determine distance for sonar sensor)
        motor_init( &motors[0], &motors[1], &motors[2], &motors[3]);
        ev3_sensor_init();

        /*-----------------Khai Nguyen, Ikhwan, Khairul----------------*/
        if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        printf( "COLOR sensor is found, reading COLOR...\n" );
        set_sensor_mode( sn_color, "COL-COLOR");
        for ( ; ; ){
            // Run motor
            go_forwards_cm_forever(motors, MAX_SPEED/20);

            if (!get_sensor_value( 0, sn_color, &val )) {
                val = 0;
            }else {
                get_sensor_value( 0, sn_color, &val );
            }

            printf( "\r(%s) value color \n", color[val]);
            if (val == 4){
                stop_motor( motors[0]);
                stop_motor( motors[1]);
                //Kick first ball which is already on the launcher
                control_arm(-1000,1);
                control_arm(200,2);
                //Put the ball from grabber to launcher and kick
                control_pincer(300,2.5);
                reset_pincer();
                control_arm(-1000,1);
                control_arm(200,2);
                //Reverse a bit to avoid crossing colored line
                go_backwards_cm_foratime(motors, 2, MAX_SPEED/10);
                turn_right_motors(motors, MAX_SPEED/10, 105);
                break;
            }
        }
    }
    /*------------------------------------------------------------------------*/


    /*------------------Khai Nguyen, Ikhwan, Khairul---------------------------*/
        if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
        printf("SONAR found, reading sonar...\n");
        for (; ; ){
            go_forwards_cm_forever(motors, MAX_SPEED/20);
            if ( !get_sensor_value0(sn_sonar, &value )) {
                value = 0;
            } else {
                get_sensor_value0(sn_sonar, &value );
            }

            if (value < range){
                stop_motor( motors[0]);
                stop_motor( motors[1]);
                grab_ball();
                reset_pincer();
                turn_left_motors(motors, MAX_SPEED/10, 105);
                control_arm(-1000, 1);
                control_arm(200, 2);
                turn_left_motors(motors, MAX_SPEED/10, 105);
                break;
            }

                   printf ("\r(%f) \n", value);
                   fflush( stdout );
        }
        }
    /*--------------------------------------------------------------------*/

    /*--------------------------Khai Nguyen, Ikhwan, Khairul----------------------*/
        if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
        	printf("SONAR found, reading sonar...\n");
        	for (; ;){
        		go_forwards_cm_forever(motors, MAX_SPEED/20);
        		if ( !get_sensor_value0(sn_sonar, &value )) {
        			value = 0;
        		} else {
        			get_sensor_value0(sn_sonar, &value );
        		}

        		if (value < range){
        			stop_motor( motors[0]);
        			stop_motor( motors[1]);
        			grab_ball();
        			reset_pincer();
        			turn_right_motors(motors, MAX_SPEED/10, 105);
        			control_arm(-1000,1);
        			control_arm(200,2);
        			break;
        		}

        		printf ("\r(%f) \n", value);
        		fflush( stdout );
        	}
        }
    /*-------------------------------------------------------------------*/
        ev3_uninit();
        printf( "*** ( EV3 ) Bye! ***\n" );
        //close();
        return 0;

}

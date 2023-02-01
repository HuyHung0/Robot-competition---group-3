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
#define COLOR_SENSOR_MODE COL-REFLECT

//Initialisation
int motor_init(uint8_t *motor0, uint8_t *motor1, uint8_t *arm, uint8_t *pincer);
void go_forwards_cm_foratime(uint8_t *motors, float cm, int speed);
void go_backwards_cm_foratime(uint8_t *motors, float cm, int speed);
void turn_right_motors(uint8_t *motors, int speed, int deg);
void go_forwards_cm_forever(uint8_t *motors, int speed);
void stop_motor(uint8_t motor);
void control_arm(int speed, float time);
void control_pincer(int speed, float time);
void grab_ball();
void reset_pincer();

//Define Colors
const char *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))



//Main program
int main(void)
{
        int val;
        //int result=0;
        uint8_t sn_color;
        motor_init( &motors[0], &motors[1], &motors[2], &motors[3]);
        ev3_sensor_init();

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
            // if (color[ val ] == color[3]){
            if (val == 4){
                stop_motor( motors[0]);
                stop_motor( motors[1]);
                reset_pincer();
                grab_ball();
                control_arm(1000, 0.3);
                go_backwards_cm_foratime(motors, 2, MAX_SPEED/10);
                turn_right_motors(motors, MAX_SPEED/10, 100);
                break;

            }
            
            fflush( stdout );
        }
    }

                //go_forwards_cm_foratime(motors, 140, MAX_SPEED/5);
                //turn_right_motors(motors, MAX_SPEED/10, 90);
                //go_backwards_cm_foratime(motors, 115, MAX_SPEED/3);
                //go_forwards_cm_foratime(motors, 57.5, MAX_SPEED/3);

                ev3_uninit();
        printf( "*** ( EV3 ) Bye! ***\n" );
        //close();
        return 0;

}
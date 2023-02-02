/*Author of this file : Ikhwan, Khairul*/

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
uint8_t motors[4];
FLAGS_T state;
#define STOP_ACTION TACHO_BRAKE
#define WHEEL_RADIUS 0.0275
#define COMP_SX -1.0
#define COMP_DX -1.0000

#ifdef _WIN32_
#include <windows.h>
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#endif

//Initialisation
void stop_motor(uint8_t motor);
void wait_motor_stop(uint8_t motor);

//Define Motors
#define MOT_SX 66
#define MOT_DX 67
#define ARM 68
#define PINCER 65
#define MOT_DIR 1
#define TURN360 620

//To stop motors
void stop_motor(uint8_t motor){
        set_tacho_command_inx( motor, TACHO_STOP );
}

//To wait motors
void wait_motor_stop(uint8_t motor){
        FLAGS_T state;
        do {
            get_tacho_state_flags (motor, &state );
        } while (state);
}


//Left-Right Motors Initilization
int motor_init(uint8_t *motor0, uint8_t *motor1, uint8_t *arm, uint8_t *pincer)
{
  int all_ok = 1;
  ev3_tacho_init();

  //Left motor initialisation
  if ( !ev3_search_tacho_plugged_in( MOT_SX, 0, motor0, 0)) {
    fprintf( stderr, "Motor left is missing!\n" );
    set_tacho_stop_action_inx( *motor0, STOP_ACTION );
    set_tacho_command_inx( *motor0, TACHO_STOP );
    all_ok = 0;
  } else {
    set_tacho_stop_action_inx( *motor0, STOP_ACTION );
    set_tacho_command_inx( *motor0, TACHO_STOP );
  }

  //Right motor initialisation
  if ( !ev3_search_tacho_plugged_in( MOT_DX, 0, motor1, 0 )) {
    fprintf( stderr, "Motor Right not found!\n" );
    set_tacho_stop_action_inx( *motor1, STOP_ACTION );
    set_tacho_command_inx( *motor1, TACHO_STOP );
    all_ok = 0;
  } else {
    set_tacho_stop_action_inx( *motor1, STOP_ACTION );
    set_tacho_command_inx( *motor1, TACHO_STOP );
  }


  //Arm motor initialisation
  if ( !ev3_search_tacho_plugged_in( ARM, 0, arm, 0 )){
    fprintf ( stderr, "Arm motor is missing!\n" );
    set_tacho_stop_action_inx( *arm, TACHO_COAST );
    set_tacho_command_inx( *arm, TACHO_STOP );
    all_ok = 0;
  } else {
    set_tacho_stop_action_inx( *arm, TACHO_COAST );
    set_tacho_command_inx( *arm, TACHO_STOP );
  }


  //Pincer motor initialisation
  if ( !ev3_search_tacho_plugged_in( PINCER, 0, pincer, 0 )){
    fprintf ( stderr, "Pincer motor is missing!\n" );
    set_tacho_stop_action_inx( *pincer, TACHO_COAST );
    set_tacho_command_inx( *pincer, TACHO_STOP );
    all_ok = 0;
  } else {
    set_tacho_stop_action_inx( *pincer, TACHO_COAST );
    set_tacho_command_inx( *pincer, TACHO_STOP );
  }



  if (all_ok){
    stop_motor(*motor0);
    stop_motor(*motor1);
    stop_motor(*arm);
    stop_motor(*pincer);
  }
  return all_ok;
}

//Function to make robot go reverse in defined cm
void go_backwards_cm_foratime(uint8_t *motors, float cm, int speed) {
  float time = ((360.0*cm)/(2*M_PI*WHEEL_RADIUS)/speed)*10;
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  set_tacho_speed_sp( motors[0], speed * COMP_SX);
  set_tacho_speed_sp( motors[1], speed * COMP_DX);
  set_tacho_time_sp( motors[0], time );
  set_tacho_time_sp( motors[1], time );
  set_tacho_command_inx( motors[0], TACHO_RUN_TIMED);
  set_tacho_command_inx( motors[1], TACHO_RUN_TIMED );
  wait_motor_stop(motors[0]);
  wait_motor_stop(motors[1]);
}

//Function to make robot go forward in defined cm
void go_forwards_cm_foratime(uint8_t *motors, float cm, int speed) {
  float time = ((360.0*cm)/(2*M_PI*WHEEL_RADIUS)/speed)*10;
  speed = -speed;
  printf("time %f \n", time);
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  set_tacho_speed_sp( motors[0], speed * COMP_SX);
  set_tacho_speed_sp( motors[1], speed * COMP_DX);
  set_tacho_time_sp( motors[0], time );
  set_tacho_time_sp( motors[1], time );
  set_tacho_command_inx( motors[0], TACHO_RUN_TIMED);
  set_tacho_command_inx( motors[1], TACHO_RUN_TIMED );
  wait_motor_stop(motors[0]);
  wait_motor_stop(motors[1]);
}


//Function to make robot turn right
void turn_right_motors(uint8_t *motors, int speed, int deg){
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  multi_set_tacho_speed_sp ( motors, speed );
  multi_set_tacho_ramp_up_sp (motors, 0 );
  multi_set_tacho_ramp_down_sp ( motors, 0 );
  set_tacho_position_sp ( motors[0], -MOT_DIR*(TURN360*deg)/360 );
  set_tacho_position_sp ( motors[1], MOT_DIR*(TURN360*deg)/360 );
  multi_set_tacho_command_inx ( motors, TACHO_RUN_TO_REL_POS );
  wait_motor_stop (motors[0]); wait_motor_stop(motors[1]);
}



//Function to make robot turn left
void turn_left_motors(uint8_t *motors, int speed, int deg){
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  multi_set_tacho_speed_sp ( motors, speed );
  multi_set_tacho_ramp_up_sp ( motors, 0 );
  multi_set_tacho_ramp_down_sp ( motors, 0 );
  set_tacho_position_sp ( motors[0], MOT_DIR*(TURN360*deg)/360 );
  set_tacho_position_sp ( motors[1], -MOT_DIR*(TURN360*deg)/360 );
  multi_set_tacho_command_inx ( motors, TACHO_RUN_TO_REL_POS );
  wait_motor_stop (motors[0]); wait_motor_stop(motors[1]);
}


//Function to make robot go backwards without destination in his life
void go_backwards_cm_forever(uint8_t *motors, int speed) {
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  set_tacho_speed_sp( motors[0], speed * COMP_SX);
  set_tacho_speed_sp( motors[1], speed * COMP_DX);
  set_tacho_command_inx( motors[0], TACHO_RUN_FOREVER);
  set_tacho_command_inx( motors[1], TACHO_RUN_FOREVER );
}

//Function to make robot go straight without destination in his life
void go_forwards_cm_forever(uint8_t *motors, int speed) {
  speed = -speed;
  multi_set_tacho_stop_action_inx( motors, STOP_ACTION );
  set_tacho_speed_sp( motors[0], speed * COMP_SX);
  set_tacho_speed_sp( motors[1], speed * COMP_DX);
  set_tacho_command_inx( motors[0], TACHO_RUN_FOREVER);
  set_tacho_command_inx( motors[1], TACHO_RUN_FOREVER);
}


//Function to control robot arm, time is a float, enter in seconds
//If speed negative, tacho goes counter clockwise
void control_arm(int speed, float time){
  if ( ev3_search_tacho_plugged_in(ARM,0, &motors[2], 0 )) {
      printf( "Arm Motor is found, moving the arm\n" );
      set_tacho_stop_action_inx( motors[2], TACHO_COAST );
      set_tacho_speed_sp( motors[2], speed);
      set_tacho_time_sp( motors[2], time*1000 );
      set_tacho_command_inx( motors[2], TACHO_RUN_TIMED );
      Sleep( 1000 );
      do {
        get_tacho_state_flags( motors[2], &state );
      } while ( state );
      Sleep( 100 );
  } else {
      printf( "Arm motor is not found\n" );
    }
}


//Function to control robot pincer, time is a float, enter in seconds
//If speed negative, tacho goes counter clockwise
void control_pincer(int speed, float time){
   if ( ev3_search_tacho_plugged_in(PINCER,0, &motors[3], 0 )) {
      printf( "Pincer found, start moving \n" );
      set_tacho_stop_action_inx( motors[3], TACHO_COAST );
      set_tacho_speed_sp( motors[3], speed);
      set_tacho_time_sp( motors[3], time*1000 );
      set_tacho_command_inx( motors[3], TACHO_RUN_TIMED );
      Sleep( 1000 );
      do {
        get_tacho_state_flags( motors[3], &state );
      } while ( state );
      Sleep( 100 );
  } else {
      printf( "Pincer motor is not found\n" );
    }
}


//Function to grab ball
void grab_ball(){
    printf("grabbing\n");
    control_pincer(500, 3.2);
}


//Function to reset pincer
void reset_pincer(){
    printf("resetting\n");
    control_pincer(-500, 5);
}

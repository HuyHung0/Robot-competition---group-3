#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

// WIN32 /////////////////////////////////////////
#ifdef _WIN32_
#include <windows.h>
// UNIX //////////////////////////////////////////
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#endif

// COMMON MOVING FUNCTION
void go_forwards_forever(uint8_t *motors, int speed);
void go_backwards_cm(uint8_t *motors, int speed, float cm);
void turn_right(uint8_t *motors, int speed, int deg);
void turn_left(uint8_t *motors, int speed, int deg);
void stop_motor(uint8_t motor);

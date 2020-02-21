#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include <time.h>
#include "queue.h"
#include "motor_control.h"
#include "lights.h"

typedef enum{
	UP,
	DOWN,
}direction;

typedef enum {
	IDLE,
	DOOR_OPEN,
	MOVING_DOWN,
	MOVING_UP,
	STOP,
}states;


int prev_floor;

states state;


int get_floor_number();

void set_prev_floor();

void initialize();

void open_door();

void check_stop();
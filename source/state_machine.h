#include <stdio.h>
#include <stdlib.h>
#include "motor_control.h"
#include "queue.h"
#include "elevator_cart.h"
#include "hardware.h" //trengs denne?

void state_machine();

void update_elevator();

void move_upwards();

void move_downwards();

void stop_elevator();

void set_elevator_state();
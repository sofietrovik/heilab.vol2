#pragma once

#include <stdbool.h>
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include "elevator_cart.h"

unsigned int Q_MATRIX[HARDWARE_NUMBER_OF_FLOORS][3];


void update_queue(); 

void reset_queue();

bool check_empty_queue();

void delete_order(int floor);

bool order_at_current_floor();

bool orders_below_floor();

bool orders_above_floor();


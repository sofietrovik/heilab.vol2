#pragma once

#include "elevator_cart.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



void set_moving_state();

void set_destination_up();

void set_destination_down();

bool order_at_current_floor();

bool orders_below_floor();

bool orders_above_floor();

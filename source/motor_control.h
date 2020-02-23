/**
* @file 
* @brief file that will calculate the distination and how to get there. 
*/

#pragma once

#include "elevator_cart.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum{
	UP,
	DOWN,
}Direction;



/**
* @brief saves the last direction the elevator had. It can only be up or down.
*/

Direction prev_direction;

/**
* @brief Global variable for the next floor the elevator should move to. 
*/

int destination;

/**
* @brief chooses between two states MOVING_UP or MOVING_DOWN according to last direction and orders. 
*/

void set_moving_state();

/**
* @brief Elevator is moving upwards, and this function will set the destination by prioritizing inside or up buttons pushed over down buttons pushed. 
*/

void set_destination_up();

/**
* @brief Elevator is moving downwards, and this function will set the destination by prioritizing inside or down buttons pushed over up buttons pushed. 
*/
void set_destination_down();


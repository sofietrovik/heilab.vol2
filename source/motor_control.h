/**
* @file 
* @brief FIle that will calculate the next floor the elevator needs to move to. 
*/

#pragma once

#include "elevator_cart.h"
#include <stdio.h>
#include <stdlib.h>



/**
* @brief saves the last direction the elevator had. It can only be up or down.
*/

direction prev_direction;

/**
* @brief Global variable for the next floor the elevator wants to move to. 
*/

int destination;

/**
* @brief chooses between two states MOVING_UP or MOVING_DOWN according to last direction and orders. 
*/

void set_moving_state();

/**
* @brief Elevator is moving upwards, and this function will choose the closest floor with an order to move to. 
*/

void set_destination_up();

/**
* @brief Elevator is moving downwards, and this function will choose the closest floor with an order to move to. 
*/
void set_destination_down();


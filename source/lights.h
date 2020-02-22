
/**
* @file 
* @brief File that will turn on and off all the lights for the entire elevator when needed. 
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h" //orders
#include "elevator_cart.h" //current floor


/**
* @brief updates all the lights, including order lights, stop light and floor indicator lights. 
*/

void set_lights();

/**
* @brief Turns the lights on for which buttons are pushed. 
*/

void set_order_lights();

/**
* @brief updates the floor indicator lights when the elevator switches floor

*/

void set_floor_lights();

/**
* @brief checks if state in stop, and then turns on stop light
*/

void set_stop_light();


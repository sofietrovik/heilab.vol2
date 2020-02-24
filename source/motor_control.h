/**
* @file 
* @brief file that will calculate the distination and how to get there. 
*/



#include "elevator_cart.h"
#include <stdio.h>
#include <stdlib.h>


typedef enum{
	UP,
	DOWN,
}Direction;


/**
* @brief Global variable for the last floor the elevator was on
*/
int g_prev_floor;



/**
* @brief saves the last direction the elevator had. It can only be up or down.
*/

Direction g_prev_direction;

/**
* @brief Global variable for the next floor the elevator should move to. 
*/

int g_destination;

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


/**
* @brief Returns which floor the elevator is currelty on or if it is between floors. 
*
* @return Returns 0 for the first floor, returns 1 for the second floor, returns 2 for the third floor and 3 for the fourth floor. Returns -1 if the elevator is between floors or not on any of the four floors.  
*
* @warning Elevator has to be between 1 and 4 floors.
*/
int get_floor_number();

/**
* @brief Updates which floor the last passed. 
*/

void set_prev_floor();

/**
* @brief Initializes the elevator by moving the elevator to the first floor. 
*/

void initialize();



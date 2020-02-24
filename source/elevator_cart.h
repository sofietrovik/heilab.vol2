#ifndef ELEVATOR_CART_H
#define ELEVATOR_CART_H

#include "hardware.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
* @brief Global variable for the last floor the elevator was on
*/
int g_prev_floor;




/**
*@brief Enum for elevator @c g_state. 
*/

typedef enum {
	IDLE,
	DOOR_OPEN,
	MOVING_DOWN,
	MOVING_UP,
	STOP,
}Elevator_states;

/**
* @brief Global variable for the current state the machine is on
*/

Elevator_states g_state;


typedef enum{
	UP,
	DOWN,
}Direction;


/**
* @brief saves the last direction the elevator had. It can only be up or down.
*/

Direction g_prev_direction;


///**
//* @brief Global variable for the next floor the elevator should move to. 
//*/

//int g_destination;



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


#endif //ELEVATOR_CART_H
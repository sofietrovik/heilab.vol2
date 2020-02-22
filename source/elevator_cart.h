#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include <time.h>
/**
* @file 
* @brief 

*/

#include "queue.h"
#include "motor_control.h"
#include "lights.h"
#include "state_machine.h"



typedef enum{
	UP,
	DOWN,
}direction;




/**
* @brief Global variable for the last floor the elevator was on
*/
int prev_floor;



/**
* @brief Returns which floor the elevator is currelty on or if it is between floors. 
*
* @return Returns 0 for the first floor, returns 1 for the second floor, returns 2 for the third floor and 3 for the fourth floor. Returns -1 if the elevator is between floors or not on any of the four floors.  
*
* @warning Elevator has to be between 1 and 4 floors.
*/
int get_floor_number();

/**
* @brief Updates which floor the elevator was last on. 

*/
void set_prev_floor();

/**
* @brief Inizalizes the elevator by moving the elevator to the first floor. 
*/

void initialize();

/**
* @brief Stops the elevator and then opens the elevator doors for 3 seconds (if there is no obstructions). If there is a obstruction it starts again. 
*/

void open_door();

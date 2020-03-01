/**
*@file
*@brief State machine and the way they move between the @c g_state .
*/
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "motor_control.h"










/**
* @brief switches between states and executes state behaviour.
*/

void state_machine();


/**
*@brief Chooses which @c elevatpr_states the elevator will go to next by updating @c g_state. 
*/

void set_elevator_state();

/**
* @brief chooses between two states MOVING_UP or MOVING_DOWN according to last direction and orders. 
*/

void set_moving_state();

/**
*@brief Checks to see if the emergency stop button is pressed. If button is presses @c g_state changes to @c STOP
*/


void check_stop();



#endif //STATE_MACHINE_H
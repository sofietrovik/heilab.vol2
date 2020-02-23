/**
*@file
*@brief
*/
#include <stdio.h>
#include <stdlib.h>
#include "motor_control.h"
#include "queue.h"
#include "elevator_cart.h"
#include "hardware.h" //trengs denne?


/**
* @brief 
*/

void state_machine();

/**
*@brief Will update @c Q_MATRIX, @c prev_floor and the lights by calling @c update_queue , @c set_lights and @c set_prev_floor .
*/

void update_elevator();

/**
*@brief Moves the elevator upwards to its @c destination.
*/

void move_upwards();

/**
*@brief Moves the elevator downwards to its @c destination.
*/

void move_downwards();

/**
*@brief Stops the elevator only when there is an emergency
*/

void stop_elevator();

/**
*@brief Chooses which @c states the elevator will go to next by updating @c state. 
*/

void set_elevator_state();

/**
*@brief Checks to see if the emergency stop button is pressed. 
*/

void check_stop();
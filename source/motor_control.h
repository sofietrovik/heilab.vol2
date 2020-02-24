/**
* @file 
* @brief file that will calculate the distination and how to get there. 
*/
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "queue.h"

#include <time.h>




void initialize();

/**
*@brief Moves the elevator upwards to its @c g_destination.
*/

void move_upwards();

/**
*@brief Moves the elevator downwards to its @c g_destination.
*/

void move_downwards();


/**
*@brief Stops the elevator only when there is an emergency
*/

void stop_elevator();

/**
* @brief Stops the elevator and then opens the elevator doors for 3 seconds. If there is a obstruction or if a button at the floor is being pushed, it restarts the timer. 
*/

void open_door();


/**
* @brief Elevator is moving upwards, and this function will set the destination by prioritizing inside or up buttons pushed over down buttons pushed. 
*/

int set_destination_up();

/**
* @brief Elevator is moving downwards, and this function will set the destination by prioritizing inside or down buttons pushed over up buttons pushed. 
*/
int set_destination_down();

/**
*@brief Will update @c G_Q_MATRIX, @c g_prev_floor and the lights by calling @c update_queue , @c set_lights and @c set_prev_floor .
*/

void update_elevator();




#endif //MOTOR_CONTROL_H
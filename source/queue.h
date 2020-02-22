/**
* @file
* @brief File that will make and update the queue system for all the orders.
*/
#pragma once

#include <stdbool.h>
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include "elevator_cart.h"


/**
* @brief An array to save alle the orders in. The rows indicate which floor has the orders, while the colums indicate what kind of order it is, and this elevator can only have 3 types of orders. 
*/
unsigned int Q_MATRIX[HARDWARE_NUMBER_OF_FLOORS][3];

/**
* @brief Updates the Q_MATRIX to see if any buttons are pushed. 1 means that there is a button pushed for a floor and a order type. 0 means that there are no new orders
*/
void update_queue(); 

/**
* @brief Empties the entire Q_MATRIX. Every number turns to zero in the array to indicate that there are no more orders.
*/

void reset_queue();

/**
* @brief checks to see if there are any orders in the Q_MATRIX. 
* @returns 1 if there are only 0 in the Q_MATRIX. If there is one or more 1 in the Q_MATRIX the function will return false. 
*/

bool check_empty_queue();

/**
* @brief Deletes an entire row in the Q_MATRIX by turning all the numbers in that row to zero. 
* @param[in] floor 	The floor that indicates which row in the matrix we want to turn all the numbers to zero
*/

void delete_order(int floor);

/**
* @brief Checks to see if the destination is on the current floor the elevator is on
* @return Returns true if the floor is on the floor the elvevator is one. Else it returns false.
*/

bool order_at_current_floor();

bool orders_below_floor();

bool orders_above_floor();


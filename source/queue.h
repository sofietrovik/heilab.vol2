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
* @brief A matrix to save all the orders in. The rows represent floors, while the colums represent order type.
*/

unsigned int Q_MATRIX[HARDWARE_NUMBER_OF_FLOORS][3];

/**
* @brief Updates the @c Q_MATRIX by iterating through all order buttons and checking if they are being pushed. The value of the specified button is set to 1 if it is being pushed. Else it will do nothing.
*/

void update_queue(); 

/**
* @brief Empties the entire @c Q_MATRIX. Every number in the matrix is set to zero to indicate that there are no more orders.
*/

void reset_queue();

/**
* @brief checks to see if there are any orders in the Q_MATRIX. 
* @returns 1 if there are only 0 in the Q_MATRIX. If there are any 1 values in the Q_MATRIX, the function will return false. 
*/

bool check_empty_queue();

/**
* @brief Deletes an entire row of orders in the @c Q_MATRIX by setting them to 0. 
* @param[in] floor 	The floor that indicates which row in the matrix that is to be deleted.
*/

void delete_orders(int floor);

/**
* @brief Checks if there are any orders at the current floor.
* @return Returns true if the statement above is true. Else it returs false.
*/

bool order_at_current_floor();

/**
* @brief Checks if there are any orders below the current floor.
* @return Returns true if the statement above is true. Else it returs false.
*/

bool orders_below_floor();

/**
* @brief Checks if there are any orders above the current floor.
* @return Returns true if the statement above is true. Else it returs false.
*/

bool orders_above_floor();


   #include "motor_control.h"

void set_moving_state(){
    //works for in between floors as well

    if(prev_direction == UP){ //if also in between floors, the previous floor can't be 3(fourth floor)
        if(orders_above_floor()){
            state = MOVING_UP;
        }else{
            state = MOVING_DOWN;
        }
    }else{ // prev_direction is down
        if(orders_below_floor()){
            state = MOVING_DOWN;
        }else{
            state = MOVING_UP;
        }
    }
}


void set_destination_up(){

    //first priority is the nearest floor with an up or inside button pushed. 
    for (int floor = prev_floor; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_INSIDE; ++button){
            if (Q_MATRIX[floor][button]==1){
                destination = floor;
                return;
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = HARDWARE_NUMBER_OF_FLOORS; floor >= prev_floor; --floor){
        if (Q_MATRIX[floor][HARDWARE_ORDER_DOWN]==1){
            destination = floor;
            return;
        }
    }

}

void set_destination_down(){

    //first priority is the nearest floor with a down or inside button pushed.
    for (int floor = prev_floor; floor >= 0; --floor){ 
        for (HardwareOrder button = HARDWARE_ORDER_INSIDE; button <= HARDWARE_ORDER_DOWN; ++button){
            if (Q_MATRIX[floor][button]==1){
                destination = floor;
                return;
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = 0; floor <= prev_floor; ++floor){
        if (Q_MATRIX[floor][HARDWARE_ORDER_UP]==1){
            destination = floor;
            return;
        }
    }

}



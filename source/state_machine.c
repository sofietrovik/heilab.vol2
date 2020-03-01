#include "state_machine.h"


void state_machine(){
    switch(g_state){

    case IDLE:
        update_elevator();
        set_elevator_state();
        break;

    case MOVING_UP:

        move_upwards();

        g_state = DOOR_OPEN;
        check_stop();
        break;

    case MOVING_DOWN:

        move_downwards();
              
        g_state = DOOR_OPEN;
        check_stop();
        break;

    case STOP:

        reset_queue();
        update_elevator();

        stop_elevator();

        if(get_floor_number() != -1){ //at a floor
            g_state = DOOR_OPEN; 
            break;
        }

        g_state = IDLE;
        break;

    case DOOR_OPEN:
        update_elevator();

        open_door();

        if(hardware_read_stop_signal()){
        	g_state = STOP;
        	break;
    	}
        g_state = IDLE;
        break;
	}
}




void set_elevator_state(){
    if(check_empty_queue() && !hardware_read_stop_signal()){
        g_state = IDLE;
        return;
    }

    if(order_at_current_floor(g_prev_floor) && !hardware_read_stop_signal() ){
        g_state = DOOR_OPEN;
        return;
    }
    set_moving_state(g_state);
    check_stop();
}



void set_moving_state(){
    //works for in between floors as well

    if(g_prev_direction == UP){ //if also in between floors, the previous floor can't be 3(fourth floor)
        if(orders_above_floor(g_prev_floor)){
            g_state = MOVING_UP;
        }else{
            g_state = MOVING_DOWN;
        }
    }else{ // prev_direction is down
        if(orders_below_floor(g_prev_floor)){
            g_state = MOVING_DOWN;
        }else{
            g_state = MOVING_UP;
        }
    }
}


void check_stop(){
  if(hardware_read_stop_signal()){
    g_state = STOP;
  }
}









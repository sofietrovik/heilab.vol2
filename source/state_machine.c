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
            state = DOOR_OPEN; 
            break;
        }

        g_state = IDLE;
        break;

    case DOOR_OPEN:
        update_elevator();

        open_door();
        delete_orders(destination);

        if(hardware_read_stop_signal()){
        	state = STOP;
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

    if(order_at_current_floor() && !hardware_read_stop_signal() ){
        g_state = DOOR_OPEN;
        return;
    }
    set_moving_state();
    check_stop();
}


void update_elevator(){
	 update_queue();
     set_prev_floor();
     set_lights();
}


void move_downwards(){
    do{
        update_elevator();
        set_destination_down();
             if(get_floor_number() != -1){ //in case of in between floors, it should not update in case of multiple stop-signals
        prev_direction = DOWN;
     }
        if(hardware_read_stop_signal()){
            state = STOP;
            break;
        }
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }while(get_floor_number() != destination && get_floor_number() != 0); //not allowed to move past 1.st floor. 

     set_prev_floor();

     
}


void move_upwards(){
    do{
    	update_elevator();
        set_destination_up();
            if(get_floor_number() != -1){ //in case of in between floors, it should not update in case of multiple stop-signals
        prev_direction = UP;
     }
        if(hardware_read_stop_signal()){
            state = STOP;
            break;
        }
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }while(get_floor_number() != destination && get_floor_number() != (HARDWARE_NUMBER_OF_FLOORS - 1)); //skal ikke bevege seg forbi 4.etasje


    set_prev_floor();



}


void stop_elevator(){
    set_lights();
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);

    while (hardware_read_stop_signal()){
        set_prev_floor();
        if(get_floor_number() != -1){ //åpne døren hvis den er ved en etasje
            hardware_command_door_open(1);
        }
    }
}

void check_stop(){
  if(hardware_read_stop_signal()){
    state = STOP;
  }
}

void open_door(){
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);

  clock_t start_time = clock();
  do {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    update_queue();
    set_lights();
    if(hardware_read_stop_signal()){
        state = STOP;
        break;
    }
    hardware_command_door_open(1);
    if (hardware_read_obstruction_signal() || order_at_current_floor()){
        start_time = clock();
        delete_orders(destination);
    }
    check_stop();


  } while (clock()-start_time < 3*CLOCKS_PER_SEC);
  
  hardware_command_door_open(0);
  }







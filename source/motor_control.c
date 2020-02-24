   #include "motor_control.h"





void initialize(){
   int error = hardware_init();
   if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
  
  while (get_floor_number() != 0){
      hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
  }
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  g_state = IDLE;
  g_prev_floor = 0;
}


void move_downwards(){
    int destination;
    do{
        update_elevator();
        destination = set_destination_down();
        if (destination == -2){
            break;
        }
        if(get_floor_number() != -1){ //in case of in between floors, it should not update in case of multiple stop-signals and changing of directions
            g_prev_direction = DOWN;
     }
        if(hardware_read_stop_signal()){
            g_state = STOP;
            break;
        }
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }while(get_floor_number() != destination && get_floor_number() != 0); //not allowed to move past 1.st floor. 

     set_prev_floor();

     
}


void move_upwards(){
    int destination;
    do{
    	update_elevator();
        destination = set_destination_up();
         if (destination == -2){
            break;
        }
        if(get_floor_number() != -1){ //in case of in between floors, it should not update in case of multiple stop-signals
            g_prev_direction = UP;
     }
        if(hardware_read_stop_signal()){
            g_state = STOP;
            break;
        }
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }while(get_floor_number() != destination && get_floor_number() != (HARDWARE_NUMBER_OF_FLOORS - 1)); //skal ikke bevege seg forbi 4.etasje


    set_prev_floor();



}


void stop_elevator(){
    set_order_lights();
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    

    while (hardware_read_stop_signal()){
        set_prev_floor();
        hardware_command_stop_light(1);
        if(get_floor_number() != -1){ //åpne døren hvis den er ved en etasje
            hardware_command_door_open(1);
        }
    }
    hardware_command_stop_light(0);
}

void open_door(){
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);

  clock_t start_time = clock();
  do {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    update_queue();
    set_order_lights();
    if(hardware_read_stop_signal()){
        g_state = STOP;
        break;
    }
    hardware_command_door_open(1);
    if (hardware_read_obstruction_signal() || order_at_current_floor(g_prev_floor)){
        start_time = clock();
        delete_orders(get_floor_number());
    }


  } while (clock() - start_time < 3*CLOCKS_PER_SEC);
  
  hardware_command_door_open(0);
  }



int set_destination_up(){

    //first priority is the nearest floor with an up or inside button pushed. 
    for (int floor = g_prev_floor; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_INSIDE; ++button){
            if (G_Q_MATRIX[floor][button] == 1){
                return floor; 
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = HARDWARE_NUMBER_OF_FLOORS; floor >= g_prev_floor; --floor){
        if (G_Q_MATRIX[floor][HARDWARE_ORDER_DOWN]==1){
            return floor;
        }
    }

    return -2;

}

int set_destination_down(){

    //first priority is the nearest floor with a down or inside button pushed.
    for (int floor = g_prev_floor; floor >= 0; --floor){ 
        for (HardwareOrder button = HARDWARE_ORDER_INSIDE; button <= HARDWARE_ORDER_DOWN; ++button){
            if (G_Q_MATRIX[floor][button]==1){
                return floor;
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = 0; floor <= g_prev_floor; ++floor){
        if (G_Q_MATRIX[floor][HARDWARE_ORDER_UP]==1){
            return floor;
        }
    }

    return -2;

}


void update_elevator(){
	 update_queue();
     set_prev_floor();
     set_order_lights(g_state);
	hardware_command_floor_indicator_on(g_prev_floor);
}




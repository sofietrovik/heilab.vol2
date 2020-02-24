   #include "motor_control.h"

void set_moving_state(){
    //works for in between floors as well

    if(g_prev_direction == UP){ //if also in between floors, the previous floor can't be 3(fourth floor)
        if(orders_above_floor()){
            g_state = MOVING_UP;
        }else{
            g_state = MOVING_DOWN;
        }
    }else{ // prev_direction is down
        if(orders_below_floor()){
            g_state = MOVING_DOWN;
        }else{
            g_state = MOVING_UP;
        }
    }
}


void set_destination_up(){

    //first priority is the nearest floor with an up or inside button pushed. 
    for (int floor = g_prev_floor; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_INSIDE; ++button){
            if (G_Q_MATRIX[floor][button]==1){
                g_destination = floor;
                return;
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = HARDWARE_NUMBER_OF_FLOORS; floor >= g_prev_floor; --floor){
        if (G_Q_MATRIX[floor][HARDWARE_ORDER_DOWN]==1){
            g_destination = floor;
            return;
        }
    }

}

void set_destination_down(){

    //first priority is the nearest floor with a down or inside button pushed.
    for (int floor = g_prev_floor; floor >= 0; --floor){ 
        for (HardwareOrder button = HARDWARE_ORDER_INSIDE; button <= HARDWARE_ORDER_DOWN; ++button){
            if (G_Q_MATRIX[floor][button]==1){
                g_destination = floor;
                return;
            }
        }
    }

    //second priority is the floor furtherst away from the elevator that has a down button pushed.
    for (int floor = 0; floor <= g_prev_floor; ++floor){
        if (Q_MATRIX[floor][HARDWARE_ORDER_UP]==1){
            g_destination = floor;
            return;
        }
    }

}

int get_floor_number(){
  if (hardware_read_floor_sensor(0))
      return 0;
  else if (hardware_read_floor_sensor(1))
      return 1;
  else if (hardware_read_floor_sensor(2))
      return 2;
  else if (hardware_read_floor_sensor(3))
      return 3;
  else return -1;
}

void set_prev_floor(){
  if (get_floor_number() != -1){
    g_prev_floor = get_floor_number();
  }
}

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





#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator_cart.h"
#include "queue.h"
#include "motor_control.h"
#include "lights.h"



int main(){

    start_elevator();

    while(1){

        switch(state){
            case IDLE:
                update_queue();
                set_prev_floor();
                set_lights();
                if(check_empty_queue() && !hardware_read_stop_signal()){
                    state = IDLE;
                    break;
                }
                if(order_at_current_floor() && !hardware_read_stop_signal() ){
                    state = DOOR_OPEN;
                    break;
                }
                set_moving_state();
                check_stop();
                break;


            case MOVING_UP:
                if (get_floor_number() == 3){
                    state = IDLE;
                    break;
                }

                do{
                    update_queue();
                    set_destination_up();
                    set_prev_floor();
                    set_lights();
                    if(hardware_read_stop_signal()){
                        state = STOP;
                        break;
                    }
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                }while(get_floor_number() != destination || get_floor_number() != 3); //skal ikke bevege seg forbi 4.etasje

                set_prev_floor();
                prev_direction = UP;
                state = DOOR_OPEN;
                check_stop();
                break;

            case MOVING_DOWN:
                if (get_floor_number() == 0){
                    state = IDLE;
                    break;
                }

                do{
                    update_queue();
                    set_destination_down();
                    set_prev_floor();
                    set_lights();
                    if(hardware_read_stop_signal()){
                        state = STOP;
                        break;
                    }
                    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                }while(get_floor_number() != destination || get_floor_number() != 0); //skal ikke bevege seg forbi 1.etasje               
                
                set_prev_floor();
                prev_direction = DOWN;
                state = DOOR_OPEN;
                check_stop();
        
                break;


            case STOP:
                reset_queue();
                set_lights();
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);

                while (hardware_read_stop_signal()){
                    set_prev_floor();
                    if(get_floor_number() != -1){ //åpne døren hvis den er ved en etasje
                        hardware_command_door_open(1);
                    }
                }

                if(get_floor_number() != -1){
                    state = DOOR_OPEN; //gjør at tilstandsiagrammet ikke gjelder lenger
                    break;
                }

                state = IDLE;
                break;


            case DOOR_OPEN:
                check_stop();
                update_queue();
                set_lights();
                set_prev_floor();
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);

                open_door();
                delete_order(destination);
                state = IDLE;
                break;
        }
    }
}

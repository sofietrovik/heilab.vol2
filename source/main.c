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
                check_stop();
                update_queue();
                set_prev_floor();
                set_lights();
                if(check_empty_queue()){
                    state = IDLE;
                    break;
                }
                if(order_at_current_floor()){
                    state = DOOR_OPEN;
                    break;
                }
                set_moving_state();
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
                }while(get_floor_number() != destination);

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
                }while(get_floor_number() != destination);               
                
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

    /*
    for (int floor = 0; HardwareOder floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        printf(" (");
        for (button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){
            //printf("button ");
            //printf("%d", button);
            printf("%d     ", Q_MATRIX[floor][button]);
        }
        printf(")\n");
    }*/
}

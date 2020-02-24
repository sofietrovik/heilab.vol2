#include "lights.h"



//setter lys etter hva som er i køen

void set_lights(){
	set_order_lights();
	set_floor_lights();
	set_stop_light();
}


void set_order_lights(){
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
        	if (floor == get_floor_number() && g_state == DOOR_OPEN){
        		hardware_command_order_light(floor, button, 0);
        	}
        	else{
        		hardware_command_order_light(floor, button, G_Q_MATRIX[floor][button]);
        	 }
       	}
    }
}

void set_floor_lights(){
	hardware_command_floor_indicator_on(g_prev_floor);
}

void set_stop_light(){
	if(g_state == STOP){
		hardware_command_stop_light(1);
	}
	else{
		hardware_command_stop_light(0);
	}
}

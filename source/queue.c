
#include "queue.h"




void update_queue(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
        	if (hardware_read_order(floor, button) == 1){
        		Q_MATRIX[floor][button] = 1;
            }
       	}
    }
}

void reset_queue(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
            Q_MATRIX[floor][button] = 0; 
        }
    }
}

bool check_empty_queue(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
            if (Q_MATRIX[floor][button] == 1){
                return false;
            } 
        }
    }
    return true;
}
 
void delete_order(int floor){
    for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
        Q_MATRIX[floor][button] = 0;
}
}

bool order_at_current_floor(){
    if (get_floor_number() == -1){
        return false;
    }else{
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){ 
            if(Q_MATRIX[prev_floor][button] == 1){
                return true;
            }
        }
    }
    return false;
}


bool orders_below_floor(){
//sjekker om det er bestillinger under etasjen, sjekker IKKE om det er bestillinger i etasjen. 

    // det kan ikke komme ordre under førsteetasje. Fungerer for mellom etasjer fordi prev_dir down alltid er paret med prev_floor 3,2 eller 1
    if(prev_floor == 0){
        return false;
    }

    //strengt tatt ikke nødvendig med en negativ for-løkke
    for (int floor = (prev_floor - 1); floor >= 0; --floor){
            for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){
                if (Q_MATRIX[floor][button]==1){
                    return true;
                }
            }
        }
    return false;
}

bool orders_above_floor(){
//sjekker om det er bestillinger under etasjen, sjekker IKKE om det er bestillinger i etasjen. 

    //det kan ikke komme ordre fra over fjerdeetasje. Fungerer for mellom etasjer fordi prev_dir up alltid er paret med prev_floor 2, 1 eller 0
    if(prev_floor == 3){
        return false;
    }

    for (int floor = (prev_floor + 1); floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
            for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; ++button){
                if (Q_MATRIX[floor][button]==1){
                    return true;
                }
            }
        }
    return false;
}
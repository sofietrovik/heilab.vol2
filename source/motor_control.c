   #include "motor_control.h"


void set_moving_state(){
    //funker søren meg for mellom floors også!! Dobbeltsjekk med Aurora
    if(prev_direction == UP){ //i tilfellet mellom etasjer betyr det at floor ikke er fire
        if(orders_above_floor()){
            state = MOVING_UP;
        }else{
            state = MOVING_DOWN;
        }
    }else{ // prev_direction er ned
        if(orders_below_floor()){
            state = MOVING_DOWN;
        }else{
            state = MOVING_UP;
        }
    }
}


void set_destination_up(){
    //første prioritet er første opp- eller insideknapp trykket. NB! hva hvis ned og i prev_floor?
    for (int floor = prev_floor; floor < HARDWARE_NUMBER_OF_FLOORS; ++floor){
        for (HardwareOrder button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_INSIDE; ++button){
            if (Q_MATRIX[floor][button]==1){
                destination = floor;
                return;
            }
        }
    }
    //andre prioritet er den siste nedknappen trykket.
    for (int floor = HARDWARE_NUMBER_OF_FLOORS; floor >= prev_floor; --floor){
        if (Q_MATRIX[floor][HARDWARE_ORDER_DOWN]==1){
                destination = floor;
                return;
            }
    }
    //hvis den kommer hit er det ingen bestillinger over carten, så hva gjør vi da? Gå til stop state? 
}

void set_destination_down(){

    //første prioritet er første ned- eller insideknapp trykket. NB! hva hvis opp og i prev_floor? Kan løses ved at man kan gå fra IDLE til OPEN_DOOR
    for (int floor = prev_floor; floor >= 0; --floor){ //negativ for fordi første bestilling er første den møter på på vei ned
        for (HardwareOrder button = HARDWARE_ORDER_INSIDE; button <= HARDWARE_ORDER_DOWN; ++button){
            if (Q_MATRIX[floor][button]==1){
                destination = floor;
                return;
            }
        }
    }

    //andre prioritet er siste oppknapp trykket
    for (int floor = 0; floor <= prev_floor; ++floor){
        if (Q_MATRIX[floor][HARDWARE_ORDER_UP]==1){
                destination = floor;
                return;
            }
    }
    //hvis den kommer hit er det ingen bestillinger under carten, så hva gjør vi da? Gå til stop state?
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
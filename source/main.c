#include "state_machine.h"


int main(){

    start_elevator();

    while(1){
        state_machine();
    }
}

#include "elevator_cart.h"


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
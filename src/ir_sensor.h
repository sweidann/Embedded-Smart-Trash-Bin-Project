#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "pico/stdlib.h"

// Function prototypes
void ir_sensor_init(uint pin);
bool ir_sensor_detect(uint pin);

#endif // IR_SENSOR_H

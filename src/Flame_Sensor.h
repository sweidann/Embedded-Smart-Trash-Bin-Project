#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include "pico/stdlib.h"

// Function Prototypes
void flame_sensor_init(uint adc_channel);
float flame_sensor_read_voltage(uint adc_channel);

#endif // FLAME_SENSOR_H

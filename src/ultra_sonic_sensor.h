#ifndef ULTRA_SONIC_SENSOR_H
#define ULTRA_SONIC_SENSOR_H

#include "pico/stdlib.h"

void ultrasonic_sensor_init(uint trig_pin, uint echo_pin);
float ultrasonic_sensor_get_distance(uint trig_pin, uint echo_pin);

#endif // ULTRA_SONIC_SENSOR_H

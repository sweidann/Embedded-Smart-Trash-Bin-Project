#include "ir_sensor.h"

void ir_sensor_init(uint pin)
{
    // Initialize the specified pin as an input
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    // gpio_pull_up(pin); // Use pull-up if needed for the IR sensor
}

bool ir_sensor_detect(uint pin)
{
    // Return true if an obstacle is detected (LOW state)
    return gpio_get(pin);
}

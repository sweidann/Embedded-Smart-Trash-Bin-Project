#include "pico/stdlib.h"

void ultrasonic_sensor_init(uint trig_pin, uint echo_pin) {
    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);
    gpio_put(trig_pin, 0);  // Ensure trigger pin starts LOW

    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);
}

float ultrasonic_sensor_get_distance(uint trig_pin, uint echo_pin) {
    // Send a 10us HIGH pulse to trigger the ultrasonic sensor
    gpio_put(trig_pin, 0);
    sleep_us(2);
    gpio_put(trig_pin, 1);
    sleep_us(10);
    gpio_put(trig_pin, 0);

    uint64_t start_time = 0;
    uint64_t end_time = 0;

    // Wait for the echo pin to go HIGH (start of echo signal)
    uint64_t timeout = time_us_64() + 30000;  // 30ms timeout
    while (gpio_get(echo_pin) == 0) {
        if (time_us_64() > timeout) {
            return -1.0f;  // Timeout waiting for the echo to start
        }
    }
    start_time = time_us_64();

    // Wait for the echo pin to go LOW (end of echo signal)
    timeout = time_us_64() + 30000;  // Reset timeout
    while (gpio_get(echo_pin) == 1) {
        if (time_us_64() > timeout) {
            return -1.0f;  // Timeout waiting for the echo to stop
        }
    }
    end_time = time_us_64();

    // Calculate duration and convert to distance
    uint64_t duration = end_time - start_time;
    float distance = (duration * 0.0343f) / 2.0f;  // Speed of sound = 343 m/s

    // Return calculated distance in centimeters
    return distance;
}

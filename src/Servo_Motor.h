#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

// Pin connected to the PWM signal of the servo motor
// You can choose a different pin if needed

// Function prototypes
// void servo_init(void);
// void servo_set_angle(uint8_t angle); // Set the servo position (0° to 180°)
void setMillis(uint servoPin, float millis);
void setServo(uint servoPin, float startMillis);
void moveServoToPosition(uint servoPin, uint position);

#endif // SERVO_H
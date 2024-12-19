#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Function prototypes
void buzzer_init(uint buzzer_pin);
void buzzer_play_tone(uint buzzer_pin, uint frequency, uint duration_ms);
void buzzer_stop(uint buzzer_pin);

#endif // BUZZER_H

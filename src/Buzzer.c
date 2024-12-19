#include "Buzzer.h"
#include "hardware/pwm.h"
uint slice_num;
void buzzer_init(uint buzzer_pin)
{
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true);
}

void buzzer_stop(uint buzzer_pin)
{
    slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    pwm_set_gpio_level(buzzer_pin, 0); // Set duty cycle to 0 to stop the sound
}

void buzzer_play_tone(uint buzzer_pin, uint frequency, uint duration_ms)
{
    uint16_t top = 125000000 / frequency; // Calculate the top value for the desired frequency
    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(buzzer_pin, top / 2); // 50% duty cycle for the tone
    sleep_ms(duration_ms);
    buzzer_stop(buzzer_pin); // Stop after the duration
}

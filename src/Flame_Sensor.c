#include "flame_sensor.h"
#include "hardware/adc.h"

void flame_sensor_init(uint adc_channel)
{
    // Initialize the ADC system
    adc_init();

    // Enable the GPIO pin associated with the ADC channel
    adc_gpio_init(26 + adc_channel); // ADC0 (GP26), ADC1 (GP27), or ADC2 (GP28)

    // Select the ADC channel for input
    adc_select_input(adc_channel);
}

float flame_sensor_read_voltage(uint adc_channel)
{
    // Ensure the correct ADC channel is selected
    adc_select_input(adc_channel);

    // Read raw ADC value (12-bit resolution, range: 0-4095)
    uint16_t adc_value = adc_read();

    // Convert ADC value to voltage (assuming 3.3V reference)
    float voltage = (adc_value / 4095.0f) * 3.3f;

    return voltage;
}

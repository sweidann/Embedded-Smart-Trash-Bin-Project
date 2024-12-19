#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Buzzer.h"
#include "ir_sensor.h"
#include "Servo_Motor.h"
#include "Flame_Sensor.h"
#include "hardware/pwm.h"
#include "ultra_sonic_sensor.h"

#define BUZZER_PIN 25           // GPIO pin connected to the buzzer
#define IR_PIN 7                // GPIO pin connected to the IR sensor
#define FLAME_PIN 28            // GPIO pin connected to the flame sensor
#define SERVO_PIN 4
#define BASKET_FULL_PIN 15
#define FLAME_ADC_CHANNEL 0
#define TRIG_PIN 6              // GPIO pin for trigger
#define ECHO_PIN 5              // GPIO pin for echo
#define FLAME_EMAIL_PIN 21
#define LED_PIN 20              // GPIO pin for LED

bool isOpen = false;

// Function Prototypes for Tasks
void task_lid_control(void *param);
void task_flame_detection(void *param);
void task_distance_monitoring(void *param);

int main() {
    stdio_init_all();

    // Initialize hardware
    gpio_init(BASKET_FULL_PIN);
    gpio_set_dir(BASKET_FULL_PIN, GPIO_OUT);

    gpio_init(FLAME_EMAIL_PIN);
    gpio_set_dir(FLAME_EMAIL_PIN, GPIO_OUT);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    buzzer_init(BUZZER_PIN);
    flame_sensor_init(FLAME_ADC_CHANNEL);
    ultrasonic_sensor_init(TRIG_PIN, ECHO_PIN);
    setServo(SERVO_PIN, 1000);

    // Create FreeRTOS Tasks
    xTaskCreate(task_lid_control, "Lid Control", 512, NULL, 1, NULL);
    xTaskCreate(task_flame_detection, "Flame Detection", 512, NULL, 2, NULL);
    xTaskCreate(task_distance_monitoring, "Distance Monitor", 512, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    while (1) {
        // Should never reach here
    }
    return 0;
}

// Task for controlling the servo lid based on the IR sensor
void task_lid_control(void *param) {
    while (1) {
        bool obstacle_detected = !ir_sensor_detect(IR_PIN);
        if (obstacle_detected) {
            if(!isOpen){
            isOpen = true;
            moveServoToPosition(SERVO_PIN, 0);  // Open lid
            buzzer_play_tone(BUZZER_PIN, 500, 500);
            vTaskDelay(pdMS_TO_TICKS(2000));   // Wait 2 seconds
            }
         else {
            isOpen = false;
            moveServoToPosition(SERVO_PIN, 135);  // Close lid
            buzzer_stop(BUZZER_PIN);
            vTaskDelay(pdMS_TO_TICKS(2000));   // Wait 2 seconds
        }
    }
    }
}

// Task for detecting flames and triggering buzzer/LED
void task_flame_detection(void *param) {
    while (1) {
        float flame_voltage = flame_sensor_read_voltage(FLAME_ADC_CHANNEL);
        bool flame_detected = (flame_voltage < 1.0f);

        if (flame_detected) {
            buzzer_play_tone(BUZZER_PIN, 1000, 1000); 
            gpio_put(FLAME_EMAIL_PIN, 1);           // Simulated notification trigger
        } else {
            buzzer_stop(BUZZER_PIN);
            gpio_put(FLAME_EMAIL_PIN, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(500));  // Check every 500 ms
    }
}

// Task for monitoring ultrasonic sensor and full-bin status

void task_distance_monitoring(void *param) {
    while (1) {
        if (isOpen) {  // Check only when the lid is closed
            float distance = ultrasonic_sensor_get_distance(TRIG_PIN, ECHO_PIN);

            if (distance < 10.0f) {  // Threshold for "full" bin
                gpio_put(BASKET_FULL_PIN, 1);
                gpio_put(LED_PIN, 1);  // Turn on LED
            } else {
                gpio_put(BASKET_FULL_PIN, 0);
                gpio_put(LED_PIN, 0);  // Turn off LED
            }
        } else {
            // Ensure the LED and full-bin status are off while the lid is open
            gpio_put(BASKET_FULL_PIN, 0);
            gpio_put(LED_PIN, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(500));  // Check every 500 ms
    }
}


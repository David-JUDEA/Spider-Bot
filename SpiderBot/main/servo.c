#include "servo.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "servo";

#define SERVO_MIN_PULSEWIDTH_US 500
#define SERVO_MAX_PULSEWIDTH_US 2500
#define SERVO_MAX_DEGREE        180
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES           LEDC_TIMER_14_BIT
#define LEDC_FREQUENCY          50

static const int servo_gpios[NUM_SERVOS] = {
    1, 2, 4, 6, 8, 10, 13, 14
};

static const int base_angles[NUM_SERVOS] = {
    90, 40, 90, 0, 90, 90, 90, 180
//  R1  R2  L1 L2 R4  R3  L3  L4
};

static int servo_angles[NUM_SERVOS];

static uint32_t angle_to_duty(uint32_t angle) {
    uint32_t pulse_us = SERVO_MIN_PULSEWIDTH_US + (angle * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US)) / SERVO_MAX_DEGREE;
    return (pulse_us * 16384) / 20000;
}

void servo_init(void) {
    ESP_LOGI(TAG, "Init servos");

    ledc_timer_config_t timer_cfg = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_cfg));

    for (int i = 0; i < NUM_SERVOS; i++) {
        ledc_channel_config_t ch_cfg = {
            .speed_mode = LEDC_MODE,
            .channel = (ledc_channel_t)i,
            .timer_sel = LEDC_TIMER_0,
            .intr_type = LEDC_INTR_DISABLE,
            .gpio_num = servo_gpios[i],
            .duty = 0,
            .hpoint = 0,
        };
        ESP_ERROR_CHECK(ledc_channel_config(&ch_cfg));
        servo_angles[i] = base_angles[i];
    }
}

void servo_set(int id, int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    ledc_set_duty(LEDC_MODE, (ledc_channel_t)id, angle_to_duty(angle));
    ledc_update_duty(LEDC_MODE, (ledc_channel_t)id);
    servo_angles[id] = angle;
}

void servo_move_smooth(int id, int target) {
    if (target < 0) target = 0;
    if (target > 180) target = 180;
    int current = servo_angles[id];
    int step = (target > current) ? 1 : -1;
    while (current != target) {
        current += step;
        ledc_set_duty(LEDC_MODE, (ledc_channel_t)id, angle_to_duty(current));
        ledc_update_duty(LEDC_MODE, (ledc_channel_t)id);
        servo_angles[id] = current;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void all_neutral(void) {
    ESP_LOGI(TAG, "Position de base");
    for (int i = 0; i < NUM_SERVOS; i++) {
        servo_set(i, base_angles[i]);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
}

int servo_get_base(int id) {
    return base_angles[id];
}
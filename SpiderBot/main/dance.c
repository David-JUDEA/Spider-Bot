#include "dance.h"
#include "servo.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "dance";

static void wait(int ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void dance_wave(void) {
    ESP_LOGI(TAG, "WAVE");
    servo_move_smooth(1, 10);
    wait(400);
    servo_move_smooth(1, 40);
    wait(300);
    servo_move_smooth(3, 30);
    wait(400);
    servo_move_smooth(3, 0);
    wait(300);
    servo_move_smooth(4, 60);
    wait(400);
    servo_move_smooth(4, 90);
    wait(300);
    servo_move_smooth(7, 150);
    wait(400);
    servo_move_smooth(7, 180);
    wait(300);
}

void dance_twist(void) {
    ESP_LOGI(TAG, "TWIST");
    for (int rep = 0; rep < 4; rep++) {
        servo_move_smooth(0, 75);
        servo_move_smooth(2, 75);
        servo_move_smooth(5, 75);
        servo_move_smooth(6, 75);
        wait(250);
        servo_move_smooth(0, 105);
        servo_move_smooth(2, 105);
        servo_move_smooth(5, 105);
        servo_move_smooth(6, 105);
        wait(250);
    }
    servo_move_smooth(0, 90);
    servo_move_smooth(2, 90);
    servo_move_smooth(5, 90);
    servo_move_smooth(6, 90);
    wait(300);
}

void dance_bounce(void) {
    ESP_LOGI(TAG, "BOUNCE");
    for (int rep = 0; rep < 5; rep++) {
        servo_move_smooth(1, 20);
        servo_move_smooth(3, 20);
        servo_move_smooth(4, 70);
        servo_move_smooth(7, 160);
        wait(200);
        servo_move_smooth(1, 40);
        servo_move_smooth(3, 0);
        servo_move_smooth(4, 90);
        servo_move_smooth(7, 180);
        wait(200);
    }
    wait(300);
}

void dance_pushup(void) {
    ESP_LOGI(TAG, "PUSH-UP");
    for (int rep = 0; rep < 3; rep++) {
        servo_move_smooth(1, 80);
        servo_move_smooth(3, 40);
        servo_move_smooth(4, 130);
        servo_move_smooth(7, 140);
        wait(500);
        servo_move_smooth(1, 40);
        servo_move_smooth(3, 0);
        servo_move_smooth(4, 90);
        servo_move_smooth(7, 180);
        wait(500);
    }
}

void dance_wiggle(void) {
    ESP_LOGI(TAG, "WIGGLE");
    servo_move_smooth(1, 80);
    servo_move_smooth(3, 40);
    servo_move_smooth(4, 130);
    servo_move_smooth(7, 140);
    wait(500);
    for (int rep = 0; rep < 5; rep++) {
        servo_move_smooth(0, 70);
        servo_move_smooth(2, 110);
        servo_move_smooth(5, 70);
        servo_move_smooth(6, 110);
        wait(200);
        servo_move_smooth(0, 110);
        servo_move_smooth(2, 70);
        servo_move_smooth(5, 110);
        servo_move_smooth(6, 70);
        wait(200);
    }
    servo_move_smooth(0, 90);
    servo_move_smooth(2, 90);
    servo_move_smooth(5, 90);
    servo_move_smooth(6, 90);
    wait(200);
    servo_move_smooth(1, 40);
    servo_move_smooth(3, 0);
    servo_move_smooth(4, 90);
    servo_move_smooth(7, 180);
    wait(500);
}

void dance_shimmy(void) {
    ESP_LOGI(TAG, "SHIMMY");
    for (int rep = 0; rep < 6; rep++) {
        servo_move_smooth(1, 25);
        servo_move_smooth(3, 15);
        servo_move_smooth(4, 75);
        servo_move_smooth(7, 165);
        wait(150);
        servo_move_smooth(1, 55);
        servo_move_smooth(3, 0);
        servo_move_smooth(4, 105);
        servo_move_smooth(7, 180);
        wait(150);
    }
    servo_move_smooth(1, 40);
    servo_move_smooth(3, 0);
    servo_move_smooth(4, 90);
    servo_move_smooth(7, 180);
    wait(300);
}

void dance_spin(void) {
    ESP_LOGI(TAG, "SPIN");
    for (int rep = 0; rep < 3; rep++) {
        for (int offset = 0; offset <= 15; offset += 2) {
            servo_set(0, 90 + offset);
            servo_set(2, 90 - offset);
            servo_set(5, 90 + offset);
            servo_set(6, 90 - offset);
            wait(30);
        }
        for (int offset = 15; offset >= 0; offset -= 2) {
            servo_set(0, 90 + offset);
            servo_set(2, 90 - offset);
            servo_set(5, 90 + offset);
            servo_set(6, 90 - offset);
            wait(30);
        }
    }
    servo_move_smooth(0, 90);
    servo_move_smooth(2, 90);
    servo_move_smooth(5, 90);
    servo_move_smooth(6, 90);
    wait(300);
}

void dance_legs_up(void) {
    ESP_LOGI(TAG, "LEGS UP");
    servo_move_smooth(1, 10);
    servo_move_smooth(3, 30);
    servo_move_smooth(4, 60);
    servo_move_smooth(7, 150);
    wait(500);
    servo_move_smooth(0, 75);
    servo_move_smooth(2, 105);
    servo_move_smooth(5, 75);
    servo_move_smooth(6, 105);
    wait(300);
    servo_move_smooth(0, 105);
    servo_move_smooth(2, 75);
    servo_move_smooth(5, 105);
    servo_move_smooth(6, 75);
    wait(300);
    servo_move_smooth(0, 90);
    servo_move_smooth(2, 90);
    servo_move_smooth(5, 90);
    servo_move_smooth(6, 90);
    servo_move_smooth(1, 40);
    servo_move_smooth(3, 0);
    servo_move_smooth(4, 90);
    servo_move_smooth(7, 180);
    wait(500);
}

void dance_mexican_wave(void) {
    ESP_LOGI(TAG, "MEXICAN WAVE");
    for (int rep = 0; rep < 3; rep++) {
        servo_move_smooth(3, 30);
        wait(200);
        servo_move_smooth(7, 150);
        servo_move_smooth(3, 0);
        wait(200);
        servo_move_smooth(4, 60);
        servo_move_smooth(7, 180);
        wait(200);
        servo_move_smooth(1, 10);
        servo_move_smooth(4, 90);
        wait(200);
        servo_move_smooth(1, 40);
        wait(200);
    }
}

void dance_six_seven(void) {
    ESP_LOGI(TAG, "SIX SEVEN");
    for (int rep = 0; rep < 4; rep++) {
        servo_move_smooth(3, 30);
        servo_move_smooth(0, 105);
        servo_move_smooth(2, 105);
        servo_move_smooth(5, 105);
        servo_move_smooth(6, 105);
        wait(200);
        servo_move_smooth(3, 0);
        wait(100);
        servo_move_smooth(1, 10);
        servo_move_smooth(0, 75);
        servo_move_smooth(2, 75);
        servo_move_smooth(5, 75);
        servo_move_smooth(6, 75);
        wait(200);
        servo_move_smooth(1, 40);
        wait(100);
        servo_move_smooth(0, 90);
        servo_move_smooth(2, 90);
        servo_move_smooth(5, 90);
        servo_move_smooth(6, 90);
        servo_move_smooth(7, 150);
        servo_move_smooth(4, 60);
        wait(150);
        servo_move_smooth(7, 180);
        servo_move_smooth(4, 90);
        wait(150);
    }
    all_neutral();
}
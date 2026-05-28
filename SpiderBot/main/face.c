// =============================================================
//  face.c — Deux yeux fixes, centrés, style RoboEyes
//  Ecran : 0.96" SSD1306 I2C OLED 128x64 (bicolore)
//
//  Zone jaune : lignes  0 - 15  (16px)
//  Zone bleue : lignes 16 - 63  (48px)  ← yeux ici
//
//  Disposition :
//    Ecran : 128px large
//    Oeil  : 45px large, 40px haut, rayon coins 10
//    Gap entre les yeux : 10px
//    Marge gauche/droite : (128 - 45 - 10 - 45) / 2 = 14px
//    Centre vertical zone bleue : 16 + 48/2 = 40
//    Y oeil : 40 - 40/2 = 20
// =============================================================

#include "face.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

static const char *TAG = "face";

// --- Broches ---
#define SDA_GPIO   33
#define SCL_GPIO   35
#define I2C_PORT   I2C_NUM_0

// --- Dimensions écran ---
#define OLED_W     128
#define OLED_H     64

// --- Paramètres des yeux ---
#define EYE_W      45    // largeur d'un oeil
#define EYE_H      40    // hauteur d'un oeil
#define EYE_R      10    // rayon des coins arrondis
#define EYE_GAP    10    // espace entre les deux yeux
#define EYE_Y      20    // Y de départ (centré dans zone bleue)
#define EYE_L_X    14    // X oeil gauche
#define EYE_R_X    69    // X oeil droit  (14 + 45 + 10)

static ssd1306_handle_t oled = NULL;

// =============================================================
//  Pixel sécurisé — jamais de coordonnée négative passée à la lib
// =============================================================
static inline void px(int x, int y, int on) {
    if (x >= 0 && x < OLED_W && y >= 0 && y < OLED_H)
        ssd1306_fill_point(oled, (uint8_t)x, (uint8_t)y, on);
}

// =============================================================
//  Rectangle plein
// =============================================================
static void rect(int x0, int y0, int w, int h, int on) {
    for (int y = y0; y < y0 + h; y++)
        for (int x = x0; x < x0 + w; x++)
            px(x, y, on);
}

// =============================================================
//  Rectangle arrondi plein
// =============================================================
static void rounded_rect(int x0, int y0, int w, int h, int r, int on) {
    // Sécurité : r ne dépasse pas la moitié de w ou h
    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;

    // Corps central
    rect(x0 + r, y0,           w - 2*r, h,       on);  // milieu
    rect(x0,     y0 + r,       r,        h - 2*r, on);  // bord gauche
    rect(x0 + w - r, y0 + r,   r,        h - 2*r, on);  // bord droit

    // Quatre coins arrondis (quart de cercle rempli)
    for (int cy = 0; cy <= r; cy++)
        for (int cx = 0; cx <= r; cx++)
            if (cx*cx + cy*cy <= r*r) {
                px(x0 + r - cx,           y0 + r - cy,           on); // haut-gauche
                px(x0 + w - r - 1 + cx,   y0 + r - cy,           on); // haut-droit
                px(x0 + r - cx,           y0 + h - r - 1 + cy,   on); // bas-gauche
                px(x0 + w - r - 1 + cx,   y0 + h - r - 1 + cy,   on); // bas-droit
            }
}

// =============================================================
//  Init
// =============================================================
void face_init(void) {
    ESP_LOGI(TAG, "Init OLED SSD1306 128x64");

    i2c_config_t cfg = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = SDA_GPIO,
        .scl_io_num       = SCL_GPIO,
        .sda_pullup_en    = GPIO_PULLUP_ENABLE,
        .scl_pullup_en    = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &cfg));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0));

    oled = ssd1306_create(I2C_PORT, 0x3C);
    ssd1306_clear_screen(oled, 0x00);
    ssd1306_refresh_gram(oled);

    face_normal();
}

// =============================================================
//  face_normal — deux yeux fixes, centrés
// =============================================================
void face_normal(void) {
    ssd1306_clear_screen(oled, 0x00);

    rounded_rect(EYE_L_X, EYE_Y, EYE_W, EYE_H, EYE_R, 1);
    rounded_rect(EYE_R_X, EYE_Y, EYE_W, EYE_H, EYE_R, 1);

    ssd1306_refresh_gram(oled);
}

// =============================================================
//  Stubs vides — à implémenter plus tard si besoin
// =============================================================
void face_blink(void)                    { face_normal(); }
void face_look(face_direction_t dir)     { face_normal(); }
void face_happy(void)                    { face_normal(); }
void face_annoyed(void)                  { face_normal(); }
void face_surprised(void)                { face_normal(); }
void face_sleep(void)                    { face_normal(); }

// =============================================================
//  Tâche FreeRTOS — affiche les yeux fixes en permanence
// =============================================================
void face_task(void *pvParameters) {
    face_normal();   // affiche une fois
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5000));  // rien à faire, yeux déjà affichés
    }
}
#pragma once

// =============================================================
//  face.h — Interface publique des yeux animés
//  Ecran : SSD1306 128x64 bicolore (jaune 0-15, bleu 16-63)
// =============================================================

typedef enum {
    FACE_LOOK_CENTER = 0,
    FACE_LOOK_LEFT,
    FACE_LOOK_RIGHT,
    FACE_LOOK_UP,
    FACE_LOOK_DOWN,
} face_direction_t;

void face_init(void);
void face_normal(void);
void face_happy(void);
void face_annoyed(void);
void face_surprised(void);
void face_sleep(void);
void face_blink(void);
void face_look(face_direction_t dir);

// À lancer dans une tâche FreeRTOS séparée
void face_task(void *pvParameters);
#ifndef SERVO_H
#define SERVO_H

#define NUM_SERVOS 8

void servo_init(void);
void servo_set(int id, int angle);
void servo_move_smooth(int id, int target);
void all_neutral(void);
int servo_get_base(int id);

#endif
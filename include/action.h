#ifndef ACTION_H_
#define ACTION_H_

#include <stdio.h>

struct Action
{
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
	int increase_light;
	int decrease_light;
};

struct {
	int mouse_x;
	int mouse_y;
} mouse_position;

void mouse_handler(int button, int state, int x, int y);

void motion_handler(int x, int y);

void key_up_handler(unsigned char key, int x, int y);

void key_handler(unsigned char key, int x, int y);

#endif
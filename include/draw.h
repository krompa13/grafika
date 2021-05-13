#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif

// Draw the content.
void draw_content(World* world);

// Draws the ground.
void draw_ground(Corridor corridor);

// Draws the ceiling.
void draw_ceiling(Corridor corridor);

// Draws the room.
void draw_walls(Corridor corridor);

// Draws the sky.
void draw_sky(Corridor corridor);

// Draws the wall where the window is.
void draw_window_wall(Corridor corridor);

// Draws the help menu
void draw_help(int texture);

// Draws the doors
void draw_doors(int moveX, int moveZ,int degree);

// Draws the ceiling fan
void draw_cfan(int moveX, int moveZ,int degree);

// Draws the chairs
void draw_chairs(int n);

// Draws the tables
void draw_tables(int n);

// Draws the window
void draw_window(int moveX, int moveZ,int degree);

#endif /* INCLUDE_DRAW_H_ */

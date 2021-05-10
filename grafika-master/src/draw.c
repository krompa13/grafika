#include "draw.h"
#include "model.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

double corridorWidth = 200;
double corridorLength = 2000;
double corridorHeight = 200;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_teapot_for_light(){
    glPushMatrix();
        glTranslatef(120, 15, 120);
        glScalef(12, 12, 12);
        glutSolidTeapot(1.0);
    glPopMatrix();
}

void draw_content(World* world)
{
	Corridor roomToDraw = world -> corridor;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(roomToDraw);
		draw_window_wall(roomToDraw);
		draw_ground(roomToDraw);
		draw_ceiling(roomToDraw);
		draw_sky(roomToDraw);
	glPopMatrix();

	draw_doors(200, +28, 0);
	draw_doors(700, +28, 0);
	draw_doors(1200, +28, 0);
	draw_doors(1700, +28, 0);
	draw_doors(200, -368, 180);
	draw_doors(700, -368, 180);
	draw_doors(1200, -368, 180);
	draw_doors(1700, -368, 180);

	glPushMatrix();
		glTranslatef(world->chairs[0].position.x, world->chairs[0].position.y, world->chairs[0].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->chairs[0].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->chairs[0].texture);
		glScalef(1.5f, 1.5f, 1.5f);
		glRotatef(world->chairs[0].rotation, 0, 1, 0);

		draw_model(&world->chairs[0].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->chairs[1].position.x, world->chairs[1].position.y, world->chairs[1].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->chairs[1].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->chairs[1].texture);
		glScalef(1.5f, 1.5f, 1.5f);
		glRotatef(world->chairs[1].rotation, 0, 1, 0);

		draw_model(&world->chairs[1].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->chairs[2].position.x, world->chairs[2].position.y, world->chairs[2].position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->chairs[2].material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->chairs[2].texture);
		glScalef(1.5f, 1.5f, 1.5f);
		glRotatef(world->chairs[2].rotation, 0, 1, 0);

		draw_model(&world->chairs[2].model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->table1.position.x, world->table1.position.y, world->table1.position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->table1.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->table1.texture);
		glScalef(0.3f, 0.3f, 0.3f);

		draw_model(&world->table1.model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->table2.position.x, world->table2.position.y, world->table2.position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->table2.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->table2.texture);
		glScalef(0.3f, 0.3f, 0.3f);

		draw_model(&world->table2.model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->window.position.x, world->window.position.y, world->window.position.z);
		glRotatef(180, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->window.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->window.texture);
		glScalef(15.0f, 15.0f, 15.0f);

		draw_model(&world->window.model);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(world->cfan.position.x, world->cfan.position.y, world->cfan.position.z);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world->cfan.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world->cfan.texture);
		glScalef(0.9f, 0.9f, 0.9f);

		draw_model(&world->cfan.model);
		
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_default);

	if (move_chair_id != -1)
	{
		world->chairs[move_chair_id].position.x = camera.position.x;
		world->chairs[move_chair_id].position.z = camera.position.z;
	}
}

void draw_doors(int moveX, int moveZ,int degree) {
	glPushMatrix();
		glTranslatef(world.door.position.x+moveX, world.door.position.y, world.door.position.z+moveZ);
		glRotatef(degree, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world.door.material_ambient);

		glBindTexture(GL_TEXTURE_2D, world.door.texture);
		glScalef(10.0f, 10.0f, 10.0f);

		draw_model(&world.door.model);
    glPopMatrix();
}

void draw_ground(Corridor corridor) {
	glBindTexture(GL_TEXTURE_2D, corridor.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -200; x < corridorLength; x += 50) {
		for (z = -200; z < corridorWidth; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}

void draw_ceiling(Corridor corridor) {
	glBindTexture(GL_TEXTURE_2D, corridor.ceiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -200; x < corridorLength; x += 50) {
		for (z = -200; z < corridorWidth; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, 200, 0);
			glVertex3f(x, 200, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, 200, 0);
			glVertex3f(x + 50, 200, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, 200, 0);
			glVertex3f(x + 50, 200, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, 200, 0);
			glVertex3f(x, 200, z + 50);
		}
	}
	glEnd();
}

void draw_window_wall(Corridor corridor) {
	//right
	glBindTexture(GL_TEXTURE_2D, corridor.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 0, 200);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, 200);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, 28);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(corridorLength, 0, 28);
	glEnd();

	// left
	glBindTexture(GL_TEXTURE_2D, corridor.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 0, -200);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, -200);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, -34);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(corridorLength, 0, -34);
	glEnd();

	// up
	glBindTexture(GL_TEXTURE_2D, corridor.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 157, -200);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, -200);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, 200);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(corridorLength, 157, 200);
	glEnd();

	// down
	glBindTexture(GL_TEXTURE_2D, corridor.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 0, -200);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, 49, -200);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(corridorLength, 49, 200);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(corridorLength, 0, 200);
	glEnd();

	
}

void draw_sky(Corridor corridor) {
	glBindTexture(GL_TEXTURE_2D, corridor.sky);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength+600, -corridorWidth*5, corridorHeight*5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength+600, corridorWidth*5, corridorHeight*5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(corridorLength+600, corridorWidth*5, -corridorHeight*5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(corridorLength+600, -corridorWidth*5, -corridorHeight*5);
	glEnd();
}

void draw_walls(Corridor corridor) {
	glBindTexture(GL_TEXTURE_2D, corridor.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-corridorWidth, 0, -corridorWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-corridorWidth, corridorWidth, -corridorWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-corridorWidth, corridorWidth, corridorWidth);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-corridorWidth, 0, corridorWidth);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, corridor.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-corridorWidth, 0, -corridorWidth);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 0, -corridorWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, -corridorWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-corridorWidth, corridorWidth, -corridorWidth);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, corridor.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(corridorLength, 0, corridorWidth);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(corridorLength, corridorWidth, corridorWidth);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-corridorWidth, corridorWidth, corridorWidth);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-corridorWidth, 0, corridorWidth);
	glEnd();
}

void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
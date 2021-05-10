#include "model.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include <obj/load.h>
#include <obj/draw.h>

void init_object(Object* object, int x, int z, int y)
{
	object->position.x = x;
	object->position.y = y;
	object->position.z = z;

	object->material_ambient[0] = 0.75;
	object->material_ambient[1] = 0.75;
	object->material_ambient[2] = 0.75;
	object->material_ambient[3] = 0.5;
}

// Loads the texture file with SOIL
GLuint load_texture(const char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture_name);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGBA,GL_UNSIGNED_BYTE,(Pixel*)image);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// SOIL_free_image_data(image);

	return texture_name;
}

void init_entities(World* world) {
	move_chair_id = -1;

	// Chair
	load_model(&world->chairs[0].model, "assets/models/modernchair.obj");
	world->chairs[0].texture = load_texture("assets/textures/chair.jpg");
	init_object(&world->chairs[0], -120, -100, 0);
	world->chairs[0].rotation = -270.0f;

	// Chair
	world->chairs[1].model = world->chairs[0].model;
	world->chairs[1].texture = world->chairs[0].texture;
	init_object(&world->chairs[1], -120, 80, 0);
	world->chairs[1].rotation = 180.0f;

	// Chair
	world->chairs[2].model = world->chairs[0].model;
	world->chairs[2].texture = world->chairs[0].texture;
	init_object(&world->chairs[2], 1890, 50, 0);
	world->chairs[2].rotation = 180.0f;

	// Table
	load_model(&world->table1.model, "assets/models/desk.obj");
	world->table1.texture = load_texture("assets/textures//desk.jpg");
	world->table1.texture = load_texture("assets/textures//desk2.jpg");
	world->table1.texture = load_texture("assets/textures//desk3.jpg");
	init_object(&world->table1, -110, 5, 55);

	// Table
	world->table2.model = world->table1.model;
	world->table2.texture = world->table1.texture;
	init_object(&world->table2, 1890, 5, 55);

	// Window
	load_model(&world->window.model, "assets/models/window.obj");
	world->window.texture =  world->chairs[0].texture;
	init_object(&world->window, 1975, 40, 60);

	// Door
	load_model(&world->door.model, "assets/models/sdoor.obj");
	world->door.texture = load_texture("assets/textures//door_texture.png");
	init_object(&world->door, -120, 170, 2);

	// Corridor
	world->corridor.sky = load_texture("assets/textures//nyc.jpg");
	world->corridor.ground = load_texture("assets/textures/ground.jpg");
    world->corridor.ceiling = load_texture("assets/textures/celin.png");
	world->corridor.back = load_texture("assets/textures//blue.png");
	world->corridor.front = world->corridor.back;
	world->corridor.left = world->corridor.back;
	world->corridor.right = world->corridor.back;

	//Ceiling fan
	load_model(&world->cfan.model,"assets/models/cfan.obj");
	world->cfan.texture = load_texture("assets/textures//cfan.jpg");
	init_object(&world->cfan, 1750,20,130);
	

	// Help
	world->helpTexture = load_texture("assets/textures//help2.png");
}

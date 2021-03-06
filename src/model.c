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

	//chairs
	for(int i=0; i<CHAIR_LENGTH; i++){
		load_model(&world->chairs[i].model, "data/models/modernchair.obj");
		world->chairs[i].texture = load_texture("data/textures/chair.jpg");
		if(i==0){
			init_object(&world->chairs[i], -120, -100, 0);
			world->chairs[i].rotation = -270.0f;
		}
		if(i==1){
			init_object(&world->chairs[i], -120, 80, 0);
			world->chairs[i].rotation = 180.0f;
		}
		if(i==2){
			init_object(&world->chairs[i], 1890, 50, 0);
			world->chairs[i].rotation = 180.0f;
		}
	}


	//tables
	for(int i=0; i<TABLE_LENGTH; i++){
		load_model(&world->tables[i].model, "data/models/desk.obj");
		world->tables[i].texture = load_texture("data/textures//desk.jpg");
		world->tables[i].texture = load_texture("data/textures//desk2.jpg");
		world->tables[i].texture = load_texture("data/textures//desk3.jpg");
		if(i==0){
			init_object(&world->tables[i], -110, 5, 55);
		}
		if(i==1){
			init_object(&world->tables[i], 1890, 5, 55);
		}
	}

	// Window
	load_model(&world->window.model, "data/models/window.obj");
	world->window.texture =  world->chairs[0].texture;
	init_object(&world->window, 1975, 40, 60);

	// Door
	load_model(&world->door.model, "data/models/sdoor.obj");
	world->door.texture = load_texture("data/textures//door_texture.png");
	init_object(&world->door, -120, 170, 2);

	// Corridor
	world->corridor.sky = load_texture("data/textures//nyc.jpg");
	world->corridor.ground = load_texture("data/textures/ground.jpg");
    world->corridor.ceiling = load_texture("data/textures/celin.png");
	world->corridor.back = load_texture("data/textures//blue.png");
	world->corridor.front = world->corridor.back;
	world->corridor.left = world->corridor.back;
	world->corridor.right = world->corridor.back;

	//Ceiling fan
	load_model(&world->cfan.model,"data/models/cfan.obj");
	world->cfan.texture = load_texture("data/textures//cfan.jpg");
	init_object(&world->cfan, 1750,20,130);
	

	// Help
	world->helpTexture = load_texture("data/textures//help2.png");
}

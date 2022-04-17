#pragma once
#include <iostream>
#include "GoreEngine.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

struct Point {
	int x;
	int y;
};


struct Entity {
	float x;
	float y;
	int w;
	int h;
	int health;
};
struct Bullet : Entity {
	float trajx;
	float trajy;
	double trajtimer;
	double timermax;
	int type;
};
struct Enemy : Entity {
	float movetimer;
	float timermax;
	float shootimer;
	float shootmax;
	float animtimer;
	float animmax;
	int type;
	spxp sprites;
	spxp start;
	//Pointer to start of array I will aloc on enemy creation
	int *p;
	int size;
	//Could do a an array but would have to memalloc it to size of sprite image
	std::vector<Point> destroyed;
};



class Game {
public:
	float trajX(float deg);
	float trajY(float deg);
	Bullet createBullet(float x, float y, int w, int h, float deg, float speed, int type);
	bool isColliding(Entity b, Entity e) {
		if (b.x < e.x + e.w && b.x + b.w > e.x && b.y < e.y + e.h && b.y + b.h > e.y) {
			return true;
		}
		return false;
	}


};
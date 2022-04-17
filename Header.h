#pragma once
#include <iostream>
#include "GoreEngine.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>



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
	//Real
	std::vector<std::vector<bool>> points;
	SDL_Surface* surf;
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
	SDL_Texture* loadBackground(int level, SDL_Renderer* rend);
	void updateBackground(SDL_Renderer* rend, SDL_Texture* ctex, Entity* back, double delta);
};
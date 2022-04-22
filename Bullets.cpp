#include "Header.h"


float Game::trajX(float deg) {
	deg = cos(deg * M_PI / 180);
	deg = deg;
	return deg;
}

float Game::trajY(float deg) {
	deg = sin(deg * M_PI / 180);
	deg = deg;
	return deg;
}


Bullet Game::createBullet(float x, float y, int w, int h, float deg, float speed, int type, SDL_Texture* tex) {
	Bullet b;
	b.trajtimer = 0;
	b.timermax = speed;
	b.trajx = trajX(deg);
	b.trajy = trajY(deg);
	b.type = type;
	b.h = h;
	b.w = w;
	b.x = x;
	b.y = y;
	b.tex = tex;
	return b;
}
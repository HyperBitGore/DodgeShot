#include "Header.h"



void Game::createEnemy(spxp& enemhead, texp& enemtex, std::vector<Enemy>& enemies, int x, int y, int type, float degree, SDL_Renderer* rend) {
	Gore gore;
	Enemy temp;
	temp.x = x;
	temp.y = y;
	temp.sprites = enemhead;
	temp.texs = enemtex;
	temp.tstart = temp.texs;
	temp.change = true;
	temp.movetimer = 0;
	temp.shootimer = 0;
	temp.animtimer = 0;
	temp.trajx = trajX(degree);
	temp.trajy = trajY(degree);
	temp.offscreen = 3;
	if (x < 0) {
		temp.offscreen = 0;
		temp.x = -50;
		temp.tgx = -x;
	}
	else if (x > 800) {
		temp.offscreen = 1;
		temp.x = 850;
		temp.tgx = x - 800;
	}
	else if (y < 20) {
		temp.offscreen = 2;
	}
	switch (type) {
	case 1:
		//enemy will pause in place and then shoot a couple bursts at you
		temp.pause = true;
		temp.shootmax = 0.5;
		temp.timermax = 0.03;
		temp.animmax = 0.3;
		break;
	default:
		temp.pause = false;
		temp.health = 10;
		temp.shootmax = 0.8;
		temp.timermax = 0.05;
		temp.animmax = 0.3;
		temp.destroycheck = { {13, 30}, {14, 30}, {15, 30}, {16, 30}, {13, 31}, {14, 31}, {15, 31}, {16, 31}, {14, 32}, {15, 32} };
		temp.destn = 5;
		temp.w = 30;
		temp.h = 50;
		break;
	}
	temp.type = type;
	temp.start = temp.sprites;
	temp.surf = SDL_CreateRGBSurfaceWithFormat(0, temp.w, temp.h, 32, SDL_PIXELFORMAT_RGBA8888);
	temp.tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 30, 50);
	for (int i = 0; i < temp.h; i++) {
		std::vector<bool> c;
		for (int j = 0; j < temp.w; j++) {
			Uint32 col = gore.GetPixelSurface(temp.sprites->current, &i, &j);
			if (col > 255) {
				c.push_back(false);
			}
			else {
				c.push_back(true);
			}
		}
		temp.points.push_back(c);
	}
	enemies.push_back(temp);
}
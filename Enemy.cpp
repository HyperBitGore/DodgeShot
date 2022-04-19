#include "Header.h"



void Game::createEnemy(spxp& enemhead, std::vector<Enemy>& enemies, int x, int y, int w, int h, int type, SDL_Renderer* rend) {
	Gore gore;
	Enemy temp;
	temp.x = x;
	temp.y = y;
	temp.w = w;
	temp.h = h;
	temp.sprites = enemhead;
	temp.change = true;
	temp.movetimer = 0;
	temp.shootimer = 0;
	temp.animtimer = 0;
	switch (type) {
	case 1:
		break;
	default:
		temp.health = 10;
		temp.shootmax = 0.8;
		temp.timermax = 0.1;
		temp.animmax = 0.3;
		temp.destroycheck = { {13, 30}, {14, 30}, {15, 30}, {16, 30}, {13, 31}, {14, 31}, {15, 31}, {16, 31}, {14, 32}, {15, 32} };
		temp.destn = 10;
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
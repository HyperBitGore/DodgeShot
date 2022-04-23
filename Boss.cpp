#include "Header.h"


void Game::bossUpdate(Boss* b, SDL_Renderer* rend, double delta) {
	b->shtime += delta;
	b->movetime += delta;
	if (b->shtime > b->shmax) {
		switch (b->pattern) {
		case 0:
			switch (b->type) {
			case 1:
				
				break;
			case 2:

				break;
			}
			break;
		case 1:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 2:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 3:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 4:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 5:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		}
		switch (b->phase) {
		case 0:
			
			break;
		case 1:

			break;
		}
		b->shtime = 0;
	}
	if (b->y < 0) {
		b->y += 250 * delta;
	}
	else {
		if (b->movetime > b->maxmove) {
		b->x += b->trajx;
		b->y += b->trajy;
		b->movetime = 0;
		}
	}

	//visual shit

}

void Game::loadBoss(Boss* boss, int level, SDL_Renderer* rend) {
	Gore gore;
	(*boss).type = level;
	(*boss).x = 400;
	(*boss).y = -100;
	(*boss).phase = 0;
	(*boss).movetime = 0;
	(*boss).pattern = 0;
	(*boss).shtime = 0;
	(*boss).surf = SDL_CreateRGBSurfaceWithFormat(0, (*boss).w, (*boss).h, 32, SDL_PIXELFORMAT_RGBA8888);
	(*boss).tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, (*boss).w, (*boss).h);
	switch (level) {
	case 1:
		(*boss).h = 200;
		(*boss).w = 200;
		(*boss).health = 100;
		(*boss).maxmove = 0.3;
		(*boss).shmax = 0.8;
		(*boss).trajx = trajX(90);
		(*boss).trajy = trajY(90);
		break;
	case 2:

		break;
	}
}
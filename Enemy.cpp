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
	temp.ptime = 0;
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
	case 2:
		temp.pause = false;
		temp.health = 10;
		temp.shootmax = 0.6;
		temp.timermax = 0.08;
		temp.animmax = 0.1;
		temp.pmax = 5;
		temp.pburst = 0;
		temp.pattern = 0;
		temp.destroycheck = { {43, 34}, {44, 34} ,{45, 34}, {46, 34}, {47, 34}, {48, 34}, {49, 34}, {50, 34}, {51, 34},{52, 34},{53, 34},{54, 34},{55, 34},{56, 34}
		,{43, 35}, {44, 35} ,{45, 35}, {46, 35}, {47, 35}, {48, 35}, {49, 35}, {50, 35}, {51, 35},{52, 35},{53, 35},{54, 35},{55, 35},{56, 35} 
		,{43, 36}, {44, 36} ,{45, 36}, {46, 36}, {47, 36}, {48, 36}, {49, 36}, {50, 36}, {51, 36},{52, 36},{53, 36},{54, 36},{55, 36},{56, 36} 
		,{43, 37}, {44, 37} ,{45, 37}, {46, 37}, {47, 37}, {48, 37}, {49, 37}, {50, 37}, {51, 37},{52, 37},{53, 37},{54, 37},{55, 37},{56, 37} 
		, {44, 38} ,{45, 38}, {46, 38}, {47, 38}, {48, 38}, {49, 38}, {50, 38}, {51, 38},{52, 38},{53, 38},{54, 38},{55, 38}
		, {44, 39} ,{45, 39}, {46, 39}, {47, 39}, {48, 39}, {49, 39}, {50, 39}, {51, 39},{52, 39},{53, 39},{54, 39},{55, 39}
		, {44, 40} ,{45, 40}, {46, 40}, {47, 40}, {48, 40}, {49, 40}, {50, 40}, {51, 40},{52, 40},{53, 40},{54, 40},{55, 40}
		, {44, 41} ,{45, 41}, {46, 41}, {47, 41}, {48, 41}, {49, 41}, {50, 41}, {51, 41},{52, 41},{53, 41},{54, 41},{55, 41}
		};
		temp.destn = temp.destroycheck.size()/2;
		temp.w = 100;
		temp.h = 100;
		temp.points = e3points;
		break;
	case 1:
		//enemy will pause in place and then shoot a couple bursts at you
		temp.pause = true;
		temp.pattern = 1;
		temp.maxp = 5.0;
		temp.burstspeed = 0.6;
		temp.origshotspeed = 1.0;
		temp.pburst = 0;
		temp.pmax = 8;
		temp.shootmax = 1.0;
		temp.timermax = 0.03;
		temp.animmax = 0.2;
		temp.destroycheck = { {23, 46},  {24, 46},  {25, 46},  {26, 46}, {23, 47},  {24, 47},  {25, 47},  {26, 47}, 
			{23, 48},  {24, 48},  {25, 48},  {26, 48},  {23, 49},  {24, 49},  {25, 49},  {26, 49},  {23, 50},  {24, 50},  {25, 50},  {26, 50}, };
		temp.destn = 20;
		temp.w = 50;
		temp.h = 60;
		temp.points = e2points;
		break;
	default:
		temp.pause = false;
		temp.health = 10;
		temp.shootmax = 1.5;
		temp.timermax = 0.05;
		temp.animmax = 0.3;
		temp.destroycheck = { {13, 30}, {14, 30}, {15, 30}, {16, 30}, {13, 31}, {14, 31}, {15, 31}, {16, 31}, {14, 32}, {15, 32} };
		temp.destn = 5;
		temp.w = 30;
		temp.h = 50;
		temp.points = e1points;
		break;
	}
	temp.type = type;
	temp.start = temp.sprites;
	temp.surf = SDL_CreateRGBSurfaceWithFormat(0, temp.w, temp.h, 32, SDL_PIXELFORMAT_RGBA8888);
	temp.tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, temp.w, temp.h);
	SDL_SetTextureBlendMode(temp.tex, SDL_BLENDMODE_BLEND);
	std::vector<Point> pointss;
	std::vector<Uint32> colors;
	for (int i = 0; i < temp.h; i++) {
		//std::vector<bool> c;
		for (int j = 0; j < temp.w; j++) {
			Uint32 col = gore.GetPixelSurface(temp.sprites->current, &i, &j);
			colors.push_back(col);
			pointss.push_back({ j, i });
			//if (col > 255) {
				//gore.SetPixelTexture(temp.tex, &i, &j, &col, &temp.surf->pitch);
				//c.push_back(false);
			//}
			//else {
				//col = 0;
				//c.push_back(true);
			//}
		}
		//temp.points.push_back(c);
	}
	MassTextureSet(temp.tex, pointss, colors, &temp.surf->pitch);
	enemies.push_back(temp);
}


void Game::generateDestroyChecks(std::vector<Point>& dest, int sx, int sy, int endx, int endy) {
	for (int i = sy; i < endy; i++) {
		for (int j = sx; j < endx; j++) {
			dest.push_back({ j, i });
		}
	}
	
}
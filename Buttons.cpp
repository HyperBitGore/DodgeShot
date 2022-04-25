#include "Header.h"



void Game::updateMenuButtons(std::vector<Button>& buttons, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, std::vector<Particle>& particles, SDL_Renderer* rend, bool* menu, bool* exitf, Entity* player, Boss* boss, int* lives, bool *hardcore, bool* bossmode) {
	int n = 0;
	for (auto& i : buttons) {
		SDL_SetRenderDrawColor(rend, 195, 50, 120, 0);
		SDL_Rect rect = { i.x, i.y, i.w, i.h };
		SDL_RenderFillRect(rend, &rect);
	}
	int mx, my;
	if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		for (auto& i : buttons) {
			Entity tem = { mx, my, 1, 1 };
			if (isColliding(i, tem)) {
				switch (i.type) {
				case 0:
					*menu = false;
					player->health = 3;
					*lives = 5;
					*hardcore = false;
					endlessmode = false;
					death(player, boss, lives, hardcore, bossmode, enemies, bullets, particles, rend);
					break;
				case 1:
					*menu = false;
					*hardcore = true;
					endlessmode = false;
					player->health = 1;
					*lives = 0;
					death(player, boss, lives, hardcore, bossmode, enemies, bullets, particles, rend);
					break;
				case 2:
					endlessmode = true;
					*menu = false;
					*hardcore = false;
					player->health = 3;
					*lives = 3;
					death(player, boss, lives, hardcore, bossmode, enemies, bullets, particles, rend);
					break;
				case 3:
					*exitf = true;
					break;
				}
			}
		}
	}

}
void Game::updatePauseButtons(std::vector<Button>& buttons, bool* menu) {
	
}

void Game::createButtons(std::vector<Button>& mbuttons, std::vector<Button>& pbuttons) {
	Button b;
	//Main menu buttons
	b.x = 300;
	b.y = 250;
	b.w = 176;
	b.h = 20;
	b.type = 0;
	b.health = 100;
	mbuttons.push_back(b);
	b.x = 300;
	b.y = 300;
	b.w = 208;
	b.h = 20;
	b.type = 1;
	b.health = 100;
	mbuttons.push_back(b);
	b.x = 300;
	b.y = 350;
	b.w = 112;
	b.h = 20;
	b.type = 2;
	b.health = 100;
	mbuttons.push_back(b);
	b.x = 300;
	b.y = 400;
	b.w = 64;
	b.h = 20;
	b.type = 3;
	b.health = 100;
	mbuttons.push_back(b);
	//Pause menu buttons


}

void Game::death(Entity* player, Boss* boss, int* lives, bool* hardcore, bool* bossmode, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, std::vector<Particle>& particles, SDL_Renderer* rend) {
	player->x = 400;
	player->y = 400;
	loadBoss(boss, level, rend);
	if (*hardcore) {
		*lives = 0;
		player->health = 1;
	}
	else {
		*lives = 5;
		player->health = 3;
	}
	enemies.clear();
	bullets.clear();
	particles.clear();
	gaptime.resetTime();
	trantime.resetTime();
	etime.resetTime();
	if (!endlessmode) {
		switch (level) {
		case 1:
			loadLevel(etypes, nload, spawnloc, transforms, "level1.lvl");
			break;
		}
		popgap = 2000;
	}
	else {
		popgap = 4000;
	}
	Gore gore;
	gore.clearTexture(walls, &wallpitch, 800, 800);
	MassTextureSet(walls, 0, 0, 10, 800, &wallcolor, &wallpitch);
	MassTextureSet(walls, 0, 0, 800, 10, &wallcolor, &wallpitch);
	MassTextureSet(walls, 0, 790, 800, 800, &wallcolor, &wallpitch);
	MassTextureSet(walls, 790, 0, 800, 800, &wallcolor, &wallpitch);
	endlesspopcount = 0;
	vertinc = 20;
	horinc = 20;
	vertstarts[0] = 40;
	vertstarts[1] = 760;
	horizontalstarts[0] = 80;
	horizontalstarts[1] = 760;
	score = 0;
	curnload = 0;
	curetype = 0;
	prog = 0;
	*bossmode = false;
}
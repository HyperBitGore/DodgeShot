#include "Header.h"
#undef main
Gore gore;
Game game;




//Background system
//Destroy certain part of enemy to kill them
//Fast bullets, less bullets
//Grazing system
//Enemies on bottom 4th of screen won't shoot
//Level loading system
//6 basic enemies(less if deem to much time)
//5 levels(5 bosses) like classic STG shmups
//Enemy that grows pixels back
//Basic cannon fodder flier
//Enemy that moves back and forth top of screen
//Enemy that fires wide fast spread
//Enemy that strafes you and tries to dodge bullets(could break this up into two different)
//Bosses
//First boss classic big guy that gives fast spreads
//Second: A guy that moves around outer edge of screen, like a centipede kind've
//Third: Small guy like you and dodges your attacks and sounds out hard to dodge patterns or tracking ones
//Fourth: Tentacles from giant mass on top of screen(maybe stage is boss fight like R type level or mushi level)
//Fifth: Two bosses at once
int main() {
	bool exitf = false;
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "Failure" << std::endl;
	}
	if (!TTF_Init()) {
		std::cout << "Font failure" << std::endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Mix failure" << std::endl;
	}
	SDL_Window* wind = SDL_CreateWindow("Dodge Shot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, 0);
	SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, 800, 800, 32, SDL_PIXELFORMAT_RGBA8888);
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;

	spxp enem1head = gore.loadSpriteList({ "enem1_3.png", "enem1_2.png", "enem1_1.png" }, { 30, 30, 30 }, {50, 50, 50},
	SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	Entity player = { 400, 400, 30, 30 };
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	double delta;
	double uptimer = 0;
	double downtimer = 0;
	double upmax = 0.005;
	double downmax = 0.005;
	double togtimer = 0;
	double shootimer = 0;

	bool run = false;

	Enemy temp;
	temp.x = 300;
	temp.y = 100;
	temp.w = 30;
	temp.h = 50;
	temp.sprites = enem1head;
	temp.movetimer = 0;
	temp.shootimer = 0;
	temp.health = 10;
	temp.shootmax = 0.8;
	temp.timermax = 0.1;
	temp.animmax = 0.3;
	temp.animtimer = 0;
	temp.type = 0;
	temp.start = temp.sprites;
	temp.surf = SDL_CreateRGBSurfaceWithFormat(0, temp.w, temp.h, 32, SDL_PIXELFORMAT_RGBA8888);
	/*temp.size = (temp.w * temp.h) * 3;
	temp.p = (int*)std::malloc(((temp.w * temp.h) * 4) * 3);
	int cb = 0;
	int x = 0;
	int y = 0;
	int* cp = temp.p;
	for (int i = 0; i <= temp.size; i++) {
		switch (cb) {
		case 0:
			*cp = x;
			std::cout << "X:" << * cp << std::endl;
			break;
		case 1:
			*cp = y;
			std::cout << "Y:" << *cp << std::endl;
			break;
		case 2:
			*cp = 0;
			std::cout << "D:" << *cp << std::endl;
			x++;
			break;
		}
		if (x > temp.w) {
			x = 0;
			y++;
		}
		cb++;
		if (cb > 2) {
			cb = 0;
		}
		cp++;
	}*/
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
	std::cout << gore.ConvertColorToUint32({ 0, 0, 0, 255 }, surf->format) << std::endl;
	while (!exitf) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		delta = gore.getDelta();
		uptimer += delta;
		downtimer += delta;
		togtimer += delta;
		shootimer += delta;

		upmax = 0.005;
		downmax = 0.005;
		int fps = 1 / delta;
		std::string fp = "Dodge Shot - FPS: " + std::to_string(fps);
		SDL_SetWindowTitle(wind, fp.c_str());
		if (togtimer > 0.2) {
			if (keys[SDL_SCANCODE_LSHIFT] || keys[SDL_SCANCODE_RSHIFT]) {
				run = !run;
				togtimer = 0;
			}
		}
		if (run) {
			upmax = 0.002;
			downmax = 0.002;
		}
		if (uptimer > upmax) {
			if (keys[SDL_SCANCODE_UP]) {
				player.y -= 1;
				uptimer = 0;
			}
			else if (keys[SDL_SCANCODE_DOWN]) {
				player.y += 1;
				uptimer = 0;
			}
		}
		if (downtimer > downmax) {
			if (keys[SDL_SCANCODE_LEFT]) {
				player.x -= 1;
				downtimer = 0;
			}
			else if (keys[SDL_SCANCODE_RIGHT]) {
				player.x += 1;
				downtimer = 0;
			}
		}
		if (shootimer > 0.1) {
			if (keys[SDL_SCANCODE_Z]) {
				bullets.push_back(game.createBullet(player.x + 15, player.y + 15, 5, 5, 270, 0.001 , 1));
				shootimer = 0;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		for (auto& i : enemies) {
			gore.clearSurface(i.surf);
			i.shootimer += delta;
			i.movetimer += delta;
			i.animtimer += delta;
			if (i.shootimer > i.shootmax) {
				bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 90, 0.002, 0));
				i.shootimer = 0;
			}
			if (i.animtimer > i.animmax) {
				i.sprites = i.sprites->next;
				if (i.sprites == NULL) {
					i.sprites = i.start;
				}
				i.animtimer = 0;
			}
			for (int h = 0; h < i.h; h++) {
				for (int w = 0; w < i.w; w++) {
						if (!i.points[h][w]) {
							Uint32 col = gore.GetPixelSurface(i.sprites->current, &h, &w);
							gore.SetPixelSurface(i.surf, &h, &w, &col);
						}
				}
			}
			SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, i.surf);
			SDL_Rect rect = { i.x, i.y, i.w, i.h };
			SDL_RenderCopy(rend, tex, NULL, &rect);
			SDL_DestroyTexture(tex);
		}
		int n = 0;
		for (auto& i : bullets) {
			i.trajtimer += delta;
			if (i.trajtimer > i.timermax) {
				i.x += i.trajx;
				i.y += i.trajy;
				i.trajtimer = 0;
			}
			switch (i.type) {
			case 0:
				if (game.isColliding(i, player)) {
					player.health--;
					i.x = -30;
				}
				break;
			case 1:
				//Check collision with enemy and delete pixel it's colliding with
				for (auto& j : enemies) {
					if (game.isColliding(i, j)) {
						int cx = 0;
						int cy = 0;
						if (i.x > j.x) { cx = i.x - j.x; }
						else { cx = j.x - i.x; }
						if (i.y > j.y) { cy = i.y - j.y; }
						else { cy = j.y - i.y; }
						if (!j.points[cy][cx]) {
							j.points[cy][cx] = true;
							i.x = -30;
						}
					}
				}
				break;
			}
			SDL_SetRenderDrawColor(rend, 100, 100, 255, 0);
			SDL_Rect rect = { i.x, i.y, i.w, i.h };
			SDL_RenderFillRect(rend, &rect);
			if (i.x < 0 || i.x > 800 || i.y < 0 || i.y > 800) {
				bullets.erase(bullets.begin() + n);
			}
			else {
				n++;
			}
		}


		SDL_SetRenderDrawColor(rend, 100, 255, 0, 0);
		SDL_Rect prect = { player.x, player.y, player.w, player.h };
		SDL_RenderFillRect(rend, &prect);

		SDL_RenderPresent(rend);
	}

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
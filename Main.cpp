#include "Header.h"
#undef main
Gore gore;
Game game;
int level = 1;
int score = 0;



//Level that will move and change around you
//Level loading system
//Enemy destruction particle system
//6 basic enemies(less if deem to much time)
//5 levels(5 bosses) like classic STG shmups
//Enemy that grows pixels back
//Basic cannon fodder flier
//Enemy that moves back and forth top of screen
//Enemy that fires wide fast spread
//Enemy that strafes you and tries to dodge bullets(could break this up into two different)
//Bosses; Body parts of giant monster you're in; Confined - confined in giant monsters body cause it swallowed you
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
	TTF_Font* font16 = TTF_OpenFont("DelaGothicOne-Regular.ttf", 16);
	SDL_Window* wind = SDL_CreateWindow("Dodge Shot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, 0);
	SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, 800, 800, 32, SDL_PIXELFORMAT_RGBA8888);
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	texp text16 = NULL;
	game.constructAlphabet(rend, font16, { 198, 150, 40 }, text16);


	spxp enem1head = gore.loadSpriteList({ "enem1_3.png", "enem1_2.png", "enem1_1.png" }, { 30, 30, 30 }, {50, 50, 50},
	SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	texp gr = gore.loadTextureList({ "graze4.png", "graze3.png", "graze2.png", "graze1.png" }, { 60, 60, 60, 60 }, { 60, 60, 60, 60 }
	, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	texp gbeg = gr;
	SDL_Texture* backtex = game.loadBackground(level, rend);

	Mix_Chunk* grazesound = Mix_LoadWAV("Sprites/graze.wav");

	Entity player = { 400, 400, 15, 20 };
	Entity graze = { 400, 400, 50, 50 };
	Entity back = { 0, -200, 800, 800 };
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	double delta;
	double uptimer = 0;
	double downtimer = 0;
	double upmax = 0.005;
	double downmax = 0.005;
	double togtimer = 0;
	double shootimer = 0;
	double grtimer = 0;
	double grstimer = 0;

	bool run = false;
	bool cgr = false;

	game.createEnemy(enem1head, enemies, 300, 100, 30, 50, 0, rend);
	game.createEnemy(enem1head, enemies, 200, 100, 30, 50, 0, rend);
	game.createEnemy(enem1head, enemies, 250, 100, 30, 50, 0, rend);
	game.createEnemy(enem1head, enemies, 350, 100, 30, 50, 0, rend);
	game.createEnemy(enem1head, enemies, 400, 100, 30, 50, 0, rend);
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

		upmax = 0.004;
		downmax = 0.004;
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
				bullets.push_back(game.createBullet(player.x + 16, player.y + 15, 5, 5, 270, 0.001, 1));
				bullets.push_back(game.createBullet(player.x + 14, player.y + 15, 5, 5, 270, 0.001, 1));
				shootimer = 0;
			}
		}
		graze.x = player.x - 25;
		graze.y = player.y - 25;
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		//game.updateBackground(rend, backtex, &back, delta);
		bool rebuiltal = false;
		int cn = 0;
		for (auto& i : enemies) {
			bool er = false;
			i.shootimer += delta;
			i.movetimer += delta;
			i.animtimer += delta;
			if (i.shootimer > i.shootmax && i.y < 670) {
				bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 90, 0.002, 0));
				i.shootimer = 0;
			}
			if (i.animtimer > i.animmax) {
				i.sprites = i.sprites->next;
				if (i.sprites == NULL) {
					i.sprites = i.start;
				}
				i.change = true;
				i.animtimer = 0;
			}
			if (i.change && !rebuiltal) {
				bool dest = false;
				int n = 1;
				for (auto& j : i.destroycheck) {
					if (i.points[j.y][j.x]) {
						n++;
					}
				}
				if (n >= i.destn) {
					dest = true;
				}
				if (!dest) {
					gore.clearSurface(i.surf);
					SDL_DestroyTexture(i.tex);
					for (int h = 0; h < i.h; h++) {
						for (int w = 0; w < i.w; w++) {
							if (!i.points[h][w]) {
								Uint32 col = gore.GetPixelSurface(i.sprites->current, &h, &w);
								gore.SetPixelSurface(i.surf, &h, &w, &col);
							}
						}
					}
					i.tex = SDL_CreateTextureFromSurface(rend, i.surf);
					i.change = false;
					rebuiltal = true;
				}
				else {
					er = true;
				}
			}
			SDL_Rect rect = { i.x, i.y, i.w, i.h };
			SDL_RenderCopy(rend, i.tex , NULL, &rect);
			if (er) {
				//Add particles flying off in random directions here
				switch (i.type) {
				case 0:
					score += 1000;
					break;
				}
				SDL_FreeSurface(i.surf);
				SDL_DestroyTexture(i.tex);
				enemies.erase(enemies.begin() + cn);
			}
			else {
				cn++;
			}
		}
		int n = 0;
		cgr = false;
		for (auto& i : bullets) {
			i.trajtimer += delta;
			if (i.trajtimer > i.timermax) {
				i.x += i.trajx;
				i.y += i.trajy;
				i.trajtimer = 0;
			}
			switch (i.type) {
			case 0:
				if (game.isColliding(i, graze)) {
					if (game.isColliding(i, player)) {
						player.health--;
						i.x = -30;
					}
					else {
						score += 5;
						cgr = true;
						//bx = i.x;
						//bang = std::atan2f((player.y - i.y), (i.x - player.x));
					}
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
							j.change = true;
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

		SDL_SetRenderDrawColor(rend, 200, 0, 0, 0);
		SDL_Rect prect = { player.x, player.y, player.w, player.h };
		SDL_RenderFillRect(rend, &prect);
		if (cgr) {
			grtimer += delta;
			grstimer += delta;
			if (grtimer > 0.1) {
				gr = gr->next;
				if (gr == NULL) {
					gr = gbeg;
				}
				grtimer = 0;
			}
			if (grstimer > 0.06) {
				Mix_PlayChannel(-1, grazesound, 0);
				grstimer = 0;
			}
			SDL_Rect rect = { player.x - 20, player.y - 20, 60, 60 };
			SDL_RenderCopy(rend, gr->current, NULL, &rect);
			//SDL_RenderCopyEx(rend, gr->current, NULL, &rect, bang, NULL, flip);
		}


		std::string temp = "Score: " + std::to_string(score);
		gore.drawText(rend, text16, temp, 10, 10, 16, 16);
		SDL_RenderPresent(rend);
	}

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
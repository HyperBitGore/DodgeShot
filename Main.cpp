#include "Header.h"
#undef main
Gore gore;
Game game;
int level = 1;
int score = 0;
int curnload = 0;
int curetype = 0;
int prog = 0;
spxp enem1head;
texp enem1tex;
spxp enem2head;
texp enem2tex;
spxp enem3head;
texp enem3tex;

//Level one done(background, all enemies in it, transforms, and boss)
//6 basic enemies(less if deem too much time)
//5 levels(5 bosses) like classic STG shmups
//Enemy that grows pixels back
//Enemy that moves back and forth top of screen
//Enemy that strafes you and tries to dodge bullets(could break this up into two different)
//Bosses; Body parts of giant monster you're in; Confined - confined in giant monsters body cause it swallowed you
//First boss classic big guy that gives fast spreads
//Second: A guy that moves around outer edge of screen, like a centipede kind've
//Third: Small guy like you and dodges your attacks and sounds out hard to dodge patterns or tracking ones
//Fourth: Tentacles from giant mass on top of screen(maybe stage is boss fight like R type level or mushi level)
//Fifth: Two bosses at once
//If i really need you to be able to deform level, maybe have list of possible deforms that frame and do a mass check

//For having enemies with different angles just make new enemy type for loading and on load just change them to one useable
//https://www.pinpng.com/picture/hhmbowh_bullet-hell-sprite-sheet-hd-png-download/, good reference for bullet sprites
std::vector<int> etypes = { 1, 0, 0, 2, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0 };
std::vector<int> nload = { 8, 8};
std::vector<Point> spawnloc = { {-100, 100}, {40, 10}, {60, 10}, {400, 10}, {120, 10}, {500 + 800, 200}, {300, 10}, {400, 10},
								{20, 10}, {40, 10}, {60, 10}, {80, 10}, {120, 10}, {150, 10}, {300, 10}, {400, 10}};


int main() {
	srand(time(NULL));
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

	Uint32 wallcolor = gore.ConvertColorToUint32({ 85, 200, 150, 0 }, surf->format);

	std::vector<Transform> transforms;
	Transform trans;
	trans.activate = 4000;
	trans.sx = 10;
	trans.sy = 100;
	trans.speed = 0.05;
	trans.endx = 790;
	trans.endy = 100;
	trans.cx = 10;
	trans.cy = 100;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 8000;
	trans.sx = 10;
	trans.sy = 99;
	trans.speed = 0.03;
	trans.endx = 790;
	trans.endy = 99;
	trans.cx = 10;
	trans.cy = 99;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 50000;
	trans.sx = 790;
	trans.sy = 99;
	trans.speed = 0.03;
	trans.endx = 10;
	trans.endy = 99;
	trans.cx = 790;
	trans.cy = 99;
	trans.ct = 0;
	trans.col = gore.ConvertColorToUint32({ 0, 0, 0, 0 }, surf->format);
	transforms.push_back(trans);
	game.convertToLvl(etypes, nload, spawnloc, transforms, "level.lvl");
	game.loadLevel(etypes, nload, spawnloc, transforms, "level.lvl");

	enem1head = gore.loadSpriteList({ "enem1_3.png", "enem1_2.png", "enem1_1.png" }, { 30, 30, 30 }, {50, 50, 50},
	SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	enem1tex = gore.loadTextureList({ "enem1_3.png", "enem1_2.png", "enem1_1.png" }, { 30, 30, 30 }, { 50, 50, 50 },
		SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	enem2head = gore.loadSpriteList({ "enem2_3.png", "enem2_2.png", "enem2_1.png" }, { 50, 50, 50 }, { 60, 60, 60 },
		SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	enem2tex = gore.loadTextureList({ "enem2_3.png", "enem2_2.png", "enem2_1.png" }, { 50, 50, 50 }, { 60, 60, 60 },
		SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	enem3head = gore.loadSpriteList({ "enem3_2.png", "enem3_1.png" }, { 100, 100, 100 }, { 100, 100, 100 },
		SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	enem3tex = gore.loadTextureList({ "enem3_2.png", "enem3_1.png" }, { 100, 100, 100 }, { 100, 100, 100 },
		SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");

	texp gr = gore.loadTextureList({ "graze4.png", "graze3.png", "graze2.png", "graze1.png" }, { 60, 60, 60, 60 }, { 60, 60, 60, 60 }
	, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	texp gbeg = gr;
	SDL_Texture* backtex = game.loadBackground(level, rend);
	SDL_Surface* pbsurf = gore.loadPNG("Sprites/pbullet1.png", SDL_PIXELFORMAT_RGBA8888, 5, 5);
	SDL_Texture* pbullet = SDL_CreateTextureFromSurface(rend, pbsurf);
	SDL_FreeSurface(pbsurf);
	SDL_Surface* ebullet1 = gore.loadPNG("Sprites/e1bullet.png", SDL_PIXELFORMAT_RGBA8888, 10, 10);
	SDL_Texture* ebullet1tex = SDL_CreateTextureFromSurface(rend, ebullet1);
	SDL_FreeSurface(ebullet1);

	//blood texture generation
	SDL_Surface* bloodsurf = SDL_CreateRGBSurfaceWithFormat(0, 30, 30, 32, SDL_PIXELFORMAT_RGBA8888);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			SDL_Color col = { rand() % 255 + 180, 50, 30, 255 };
			gore.SetPixelSurfaceColor(bloodsurf, &i, &j, &col);
		}
	}
	SDL_Texture* bloodtex = SDL_CreateTextureFromSurface(rend, bloodsurf);
	SDL_FreeSurface(bloodsurf);
	std::cout << gore.ConvertColorToUint32({ 255, 50, 30, 0 }, surf->format) << std::endl;

	SDL_Texture* particletex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);

	
	//use surf
	SDL_Rect wallrect = { 0,0,800,800 };
	SDL_Texture* walls = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);
	int ty = 100;
	int tx = 400;
	int wallpitch = surf->pitch;
	int realpitch = wallpitch / sizeof(unsigned int);
	//Uint32 tcolor = gore.ConvertColorToUint32({ 255, 255, 255, 0 }, surf->format);
	
	game.MassTextureSet(walls, surf, 0, 0, 10, 800, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, surf, 0, 0, 800, 10, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, surf, 0, 790, 800, 800, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, surf, 790, 0, 800, 800, &wallcolor, &wallpitch);
	//gore.SetPixelTexture(walls, &ty, &tx, &wallcolor, &wallpitch);

	Mix_Chunk* grazesound = Mix_LoadWAV("Sprites/graze.wav");

	Entity player = { 400, 400, 15, 20 };
	player.health = 50;
	Entity graze = { 400, 400, 50, 50 };
	Entity back = { 0, -200, 800, 800 };
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	std::vector<Particle> particles;

	double delta;
	double uptimer = 0;
	double downtimer = 0;
	double upmax = 0.005;
	double downmax = 0.005;
	double togtimer = 0;
	double shootimer = 0;
	double grtimer = 0;
	double grstimer = 0;
	double spawntimer = 0;

	bool run = false;
	bool cgr = false;
	bool spawning = false;
	
	//int framespawn = 0;
	//int spawngap = 500;

	std::cout << gore.ConvertColorToUint32({ 0, 0, 0, 255 }, surf->format) << std::endl;

	Timer etime;
	etime.startTime();
	Timer trantime;
	trantime.startTime();
	Timer gaptime;
	gaptime.startTime();
	double ctime = 0;
	double lvltime = 0;
	while (!exitf) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		lvltime = trantime.getTime();
		delta = gore.getDelta();
		uptimer += delta;
		downtimer += delta;
		togtimer += delta;
		shootimer += delta;
		int fps = 1 / delta;
		if (spawning) {
			double dv = gaptime.getTime();
			if (dv >= 200) {
				game.levelHandler(etypes, nload, spawnloc, enemies, rend, &spawning);
				gaptime.resetTime();
			}
		}
		else {
			ctime = etime.getTime();
		}

		if (ctime > 2000) {
			spawning = true;
			//spawngap = fps / 2;
			game.levelHandler(etypes, nload, spawnloc, enemies, rend, &spawning);
			etime.resetTime();
			ctime = 0;
		}
		upmax = 0.005;
		downmax = 0.007;
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
		int chy = player.y;
		int chx = player.x + 8;
		int chy2 = player.y + player.h;
		int chx2 = player.x + 8;
		if (gore.GetPixelTexture(walls, &chy, &chx, &wallpitch) != 0) {
			player.y++;
		}
		else if (gore.GetPixelTexture(walls, &chy2, &chx2, &wallpitch) != 0) {
			player.y--;
		}
		chx = player.x - 1;
		chx2 = player.x + 15;
		if (gore.GetPixelTexture(walls, &chy, &chx, &wallpitch) != 0) {
			player.x++;
		}
		else if (gore.GetPixelTexture(walls, &chy, &chx2, &wallpitch) != 0) {
			player.x--;
		}
		if (shootimer > 0.1) {
			if (keys[SDL_SCANCODE_Z]) {
				bullets.push_back(game.createBullet(player.x + 8, player.y + 10, 5, 5, 270, 0.001 , 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 9, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 7, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 6, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 10, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 8, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 9, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 7, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 6, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 10, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 1, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 2, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 3, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 4, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 5, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 1, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 2, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 3, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 4, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 5, player.y + 5, 5, 5, 270, 0.001, 1, pbullet));

				bullets.push_back(game.createBullet(player.x + 8, player.y + 5, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 9, player.y + 5, 5, 5, 290, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 7, player.y + 5, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 6, player.y + 5, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 10, player.y + 5, 5, 5, 290, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 8, player.y + 6, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 9, player.y + 6, 5, 5, 290, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 7, player.y + 6, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 6, player.y + 6, 5, 5, 250, 0.001, 1, pbullet));
				bullets.push_back(game.createBullet(player.x + 10, player.y + 6, 5, 5, 290, 0.001, 1, pbullet));
				shootimer = 0;
			}
		}
		graze.x = player.x - 25;
		graze.y = player.y - 25;
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		int n = 0;
		//To do more realistic growth effect just have multiple transforms activate at once and grow at different rates but right next to each other on the y axis(make them one pixel tall)
		for (auto& i : transforms) {
			if (lvltime > i.activate) {
				i.ct += delta;
				bool er = false;
				if (i.ct > i.speed) {
					gore.SetPixelTexture(walls, &i.cy, &i.cx, &i.col, &wallpitch);
					if (i.cx > i.endx) {
						i.cx--;
						if (i.cx <= i.endx) {
							if (i.cy >= i.endy) {
								er = true;
							}
							else {
								i.cy++;
								i.cx = i.sx;
							}
						}
					}
					else {
						i.cx++;
						if (i.cx >= i.endx) {
							if (i.cy >= i.endy) {
								er = true;
							}
							else {
								i.cy++;
								i.cx = i.sx;
							}
						}
					}
					i.ct = 0;
				}
				if (er) {
					transforms.erase(transforms.begin() + n);
				}
				else {
					n++;
				}
			}
		}
		SDL_RenderCopy(rend, walls, NULL, &wallrect);
		//game.updateBackground(rend, backtex, &back, delta);
		n = 0;
		for (int i = 0; i < particles.size();) {
			particles[i].trajtimer += delta;
			if (particles[i].trajtimer > particles[i].timermax) {
				particles[i].x += particles[i].trajx;
				particles[i].y += particles[i].trajy;
				particles[i].rect.x = particles[i].x;
				particles[i].rect.y = particles[i].y;
				particles[i].trajtimer = 0;
				if (particles[i].x < 0 || particles[i].y < 0 || particles[i].x > 800 || particles[i].y > 800) {
					particles[i].er = true;
				}
				if (particles[i].type == 1) {
					if (game.isColliding(particles[i], player)) {
						particles[i].er = true;
						player.health++;
						score += 800;
					}
				}
			}

			//Instead of making new texture grab pixel data from the enemies texture
			SDL_RenderCopy(rend, particles[i].tex, &particles[i].pd, &particles[i].rect);
			if (particles[i].er) {
				particles.erase(particles.begin() + i);
			}
			else {
				i++;
			}
		}

		if (player.health > 100) {
			player.health = 100;
		}
		SDL_SetRenderDrawColor(rend, 255, 50, 50, 0);
		SDL_Rect hrect = { 750, 680, 50, player.health };
		SDL_RenderFillRect(rend, &hrect);

		bool rebuiltal = false;
		int cn = 0;
		for (auto& i : enemies) {
			bool er = false;
			bool skipmove = false;
			i.shootimer += delta;
			i.movetimer += delta;
			i.animtimer += delta;
			i.ptime += delta;
			if (i.pause) {
				if (i.ptime > i.maxp && i.y < 670) {
					i.shootmax = i.burstspeed;
					skipmove = true;
				}
			}
			if (i.movetimer > i.timermax) {
				if (i.offscreen < 3) {
					switch (i.offscreen) {
					case 0:
						if (i.x < i.tgx) {
							i.x += 250 * delta;
						}
						else {
							i.offscreen = 3;
						}
						break;
					case 1:
						if (i.x > i.tgx) {
							i.x -= 250 * delta;
						}
						else {
							i.offscreen = 3;
						}
						break;
					case 2:
						if (i.y < 20) {
							i.y += 250 * delta;
						}
						else {
							i.offscreen = 3;
						}
						break;
					}
					
				}
				else {
					if (!skipmove) {
						i.x += i.trajx;
						i.y += i.trajy;
					}
					i.movetimer = 0;
				}
			}

			if (i.shootimer > i.shootmax && i.y < 670) {
				float angle;
				switch (i.type) {
				case 0:
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 90, 0.006, 0, ebullet1tex));
					break;
				case 1:
					angle = std::atan2f((player.y - 15) - i.y, (player.x - 15) - i.x) * 180.0/M_PI;
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, angle, 0.004, 0, ebullet1tex));
					angle = std::atan2f((player.y - 15) - i.y, (player.x - 10) - i.x) * 180.0 / M_PI;
					bullets.push_back(game.createBullet((i.x + (i.w >> 1) + 5), i.y + (i.h >> 1), 10, 10, angle, 0.004, 0, ebullet1tex));
					angle = std::atan2f((player.y - 10) - i.y, (player.x - 10) - i.x) * 180.0 / M_PI;
					bullets.push_back(game.createBullet((i.x + (i.w >> 1)), i.y + 5 + (i.h >> 1), 10, 10, angle, 0.004, 0, ebullet1tex));
					angle = std::atan2f((player.y - 5) - i.y, (player.x - 10) - i.x) * 180.0 / M_PI;
					bullets.push_back(game.createBullet((i.x + (i.w >> 1)), i.y + 5 + (i.h >> 1), 10, 10, angle, 0.004, 0, ebullet1tex));
					angle = std::atan2f((player.y - 10) - i.y, (player.x - 5) - i.x) * 180.0 / M_PI;
					bullets.push_back(game.createBullet((i.x + (i.w >> 1)), i.y + 5 + (i.h >> 1), 10, 10, angle, 0.004, 0, ebullet1tex));
					i.pburst++;
					if (i.pburst > i.pmax) {
						i.ptime = 0;
						i.pburst = 0;
						i.shootmax = i.origshotspeed;
					}
					break;
				case 2:
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 75, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 70, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 105, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 100, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 95, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 85, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1), 10, 10, 90, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1) - 10, 10, 10, 90, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1) - 20, 10, 10, 90, 0.003, 0, ebullet1tex));
					bullets.push_back(game.createBullet(i.x + (i.w >> 1), i.y + (i.h >> 1) - 30, 10, 10, 90, 0.003, 0, ebullet1tex));
					break;
				}
				i.shootimer = 0;
			}
			if (i.animtimer > i.animmax) {
				i.sprites = i.sprites->next;
				i.texs = i.texs->next;
				if (i.sprites == NULL) {
					i.sprites = i.start;
					i.texs = i.tstart;
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
			if (i.y > 800) {
				SDL_FreeSurface(i.surf);
				SDL_DestroyTexture(i.tex);
				enemies.erase(enemies.begin() + cn);
			}
			if (er) {
				switch (i.type) {
				case 0:
					score += 1000;
					break;
				}
				//explosion particle creation
				for (int h = 0; h < i.h; h++) {
					for (int w = 0; w < i.w; w++) {
						if (!i.points[h][w]) {
							Particle p;
							p.x = i.x + w + 1;
							p.y = i.y + h + 1;
							p.rect = { (int)p.x, (int)p.y, 1, 1 };
							p.pd = { w, h, 1, 1 };
							p.trajtimer = 0;
							p.timermax = 0.007;
							p.tex = i.texs->current;
							//p.col = gore.GetPixelSurface(i.sprites->current, &h, &w);
							p.trajx = game.trajX(rand() % 358);
							p.trajy = game.trajY(rand() % 358);
							p.type = 0;
							p.w = 1;
							p.h = 1;
							p.er = false;
							particles.push_back(p);
							int roll = rand() % 100;
							if (roll > 90) {
								Particle b;
								b.x = i.x + w + 1;
								b.y = i.y + h + 1;
								int pw = rand() % 10 + 5;
								int ph = rand() % 10 + 3;
								b.rect = { (int)b.x, (int)b.y, pw, ph };
								b.pd = { 0, 0, pw, ph};
								b.trajtimer = 0;
								int max = rand() % 8 + 3;
								float tmax = (float)max * 0.001;
								b.timermax = tmax;
								b.tex = bloodtex;
								//b.col = 4281474815;
								//maybe change this to have range to give more dynamic feel
								b.trajx = game.trajX(90);
								b.trajy = game.trajY(90);
								b.type = 1;
								b.w = pw;
								b.h = ph;
								b.er = false;
								particles.push_back(b);
							}
						}
					}
				}
				SDL_FreeSurface(i.surf);
				SDL_DestroyTexture(i.tex);
				enemies.erase(enemies.begin() + cn);
			}
			else {
				cn++;
			}
		}
		n = 0;
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
						score++;
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
			SDL_Rect rect = { i.x, i.y, i.w, i.h };
			SDL_RenderCopy(rend, i.tex, NULL, &rect);
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
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

spxp boss1head;

SDL_Texture* ebullet1tex;


std::vector<std::vector<bool>> e1points;
std::vector<std::vector<bool>> e2points;
std::vector<std::vector<bool>> e3points;

Uint32 wallcolor;
SDL_Texture* walls;
int wallpitch;

Timer etime;
Timer trantime;
Timer gaptime;

//Optimize particles
//Invis time when you lose a life
//Endless mode with box that slowly gets smaller
//3 levels(3 bosses) like classic STG shmups
//Enemy that grows pixels back
//Enemy that moves back and forth top of screen
//Enemy that strafes you and tries to dodge bullets(could break this up into two different)
//Bosses; Body parts of giant monster you're in; Confined - confined in giant monsters body cause it swallowed you
//Second: A guy that moves around outer edge of screen, like a centipede kind've
//Third: Small guy like you and dodges your attacks and sounds out hard to dodge patterns or tracking ones


//For having enemies with different angles just make new enemy type for loading and on load just change them to one useable
//https://www.pinpng.com/picture/hhmbowh_bullet-hell-sprite-sheet-hd-png-download/, good reference for bullet sprites


//Dont use 92 or 124
std::vector<int> etypes = {};
std::vector<int> nload = { };
std::vector<Point> spawnloc = { };
std::vector<Transform> transforms;

int main() {
	srand(time(NULL));
	bool exitf = false;
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "Failure" << std::endl;
	}
	if (!TTF_Init()) {
		std::cout << "Font failure" << std::endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) < 0) {
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
	Uint32 black = gore.ConvertColorToUint32({ 0, 0, 0, 0 }, surf->format);
	wallcolor = gore.ConvertColorToUint32({ 85, 200, 150, 0 }, surf->format);

	//std::vector<Transform> transforms;
	/*Transform trans;
	trans.activate = 8000;
	trans.sx = 10;
	trans.sy = 400;
	trans.speed = 0.04;
	trans.endx = 790;
	trans.endy = 400;
	trans.cx = 10;
	trans.cy = 400;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);*/


	std::cout << spawnloc.size() << " : " << etypes.size() << std::endl;
	std::cout << nload.size() << std::endl;
	//game.convertToLvl(etypes, nload, spawnloc, transforms, "level.lvl");
	//game.loadLevel(etypes, nload, spawnloc, transforms, "level.lvl");

	enem1head = gore.loadSpriteList({ "enem1_3.png", "enem1_2.png", "enem1_1.png" }, { 30, 30, 30 }, { 50, 50, 50 },
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

	boss1head = gore.loadSpriteList({ "boss1.png" }, { 200 }, { 200 }, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");

	game.createEnemyPoints();

	texp playertex = gore.loadTextureList({ "player1.png", "player2.png" }, { 20, 20 }, { 25, 25 }, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	spxp playersprites = gore.loadSpriteList({ "player1.png", "player2.png" }, { 20, 20 }, { 25, 25 }, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");

	texp gr = gore.loadTextureList({ "graze4.png", "graze3.png", "graze2.png", "graze1.png" }, { 60, 60, 60, 60 }, { 60, 60, 60, 60 }
	, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	texp gbeg = gr;
	SDL_Texture* backtex;
	SDL_Surface* pbsurf = gore.loadPNG("Sprites/pbullet1.png", SDL_PIXELFORMAT_RGBA8888, 5, 5);
	SDL_Texture* pbullet = SDL_CreateTextureFromSurface(rend, pbsurf);
	SDL_FreeSurface(pbsurf);
	SDL_Surface* ebullet1 = gore.loadPNG("Sprites/e1bullet.png", SDL_PIXELFORMAT_RGBA8888, 10, 10);
	ebullet1tex = SDL_CreateTextureFromSurface(rend, ebullet1);
	SDL_FreeSurface(ebullet1);
	SDL_Surface* life1surf = gore.loadPNG("Sprites/life1.png", SDL_PIXELFORMAT_RGBA8888, 25, 25);
	SDL_Texture* lifetex = SDL_CreateTextureFromSurface(rend, life1surf);
	SDL_FreeSurface(life1surf);
	SDL_Surface* back1surf = gore.loadPNG("Sprites/back1.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);
	SDL_Surface* back2surf = gore.loadPNG("Sprites/back2.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);
	SDL_Surface* back3surf = gore.loadPNG("Sprites/back3.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);
	SDL_Surface* back4surf = gore.loadPNG("Sprites/back4.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);
	SDL_Surface* back5surf = gore.loadPNG("Sprites/back5.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);
	SDL_Surface* back6surf = gore.loadPNG("Sprites/back6.png", SDL_PIXELFORMAT_RGBA8888, 800, 800);

	SDL_Texture* back1tex = SDL_CreateTextureFromSurface(rend, back1surf);
	SDL_Texture* back2tex = SDL_CreateTextureFromSurface(rend, back2surf);
	SDL_Texture* back3tex = SDL_CreateTextureFromSurface(rend, back3surf);
	SDL_Texture* back4tex = SDL_CreateTextureFromSurface(rend, back4surf);
	SDL_Texture* back5tex = SDL_CreateTextureFromSurface(rend, back5surf);
	SDL_Texture* back6tex = SDL_CreateTextureFromSurface(rend, back6surf);
	backtex = back1tex;
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
	SDL_SetTextureBlendMode(particletex, SDL_BLENDMODE_BLEND);

	//use surf
	SDL_Rect wallrect = { 0,0,800,800 };
	walls = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);
	SDL_SetTextureBlendMode(walls, SDL_BLENDMODE_BLEND);
	int ty = 100;
	int tx = 400;
	wallpitch = surf->pitch;
	int realpitch = wallpitch / sizeof(unsigned int);
	//Uint32 tcolor = gore.ConvertColorToUint32({ 255, 255, 255, 0 }, surf->format);
	
	//game.MassTextureSet(walls, 0, 0, 10, 800, &wallcolor, &wallpitch);
	//game.MassTextureSet(walls, 0, 0, 800, 10, &wallcolor, &wallpitch);
	//game.MassTextureSet(walls, 0, 790, 800, 800, &wallcolor, &wallpitch);
	//game.MassTextureSet(walls, 790, 0, 800, 800, &wallcolor, &wallpitch);
	//gore.SetPixelTexture(walls, &ty, &tx, &wallcolor, &wallpitch);

	Mix_Chunk* grazesound = Mix_LoadWAV("Sprites/graze.wav");
	Mix_Chunk* ehitsound = Mix_LoadWAV("Sprites/ehit.wav");
	Mix_Chunk* edeathsound = Mix_LoadWAV("Sprites/edeath.wav");
	Mix_Chunk* phitsound = Mix_LoadWAV("Sprites/pdamage.wav");
	Mix_Chunk* pdeathsound = Mix_LoadWAV("Sprites/pdeath.wav");
	Mix_Chunk* pickupsound = Mix_LoadWAV("Sprites/pickup.wav");
	Mix_Chunk* shootsound = Mix_LoadWAV("Sprites/shoot.wav");

	int lives = 5;
	int backframes = 0;
	Entity player = { 400, 400, 1, 1 };
	player.health = 3;
	texp pbegin = playertex;
	Entity graze = { 400, 400, 50, 50 };
	Entity pdraw = { 400, 400, 20, 25 };
	Entity back = { 0, 0, 800, 800 };
	Boss boss;
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	std::vector<Particle> particles;
	std::vector<Button> menubuttons;
	std::vector<Button> pausebuttons;

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
	double panimetime = 0;
	double banim = 0;

	bool run = false;
	bool cgr = false;
	bool spawning = false;
	bool bossmode = false;
	bool hardcore = false;
	bool win = false;
	bool menu = true;
	bool backanim = false;

	//int framespawn = 0;
	//int spawngap = 500;

	std::cout << gore.ConvertColorToUint32({ 0, 0, 0, 255 }, surf->format) << std::endl;

	etime.startTime();
	trantime.startTime();
	gaptime.startTime();
	double ctime = 0;
	double lvltime = 0;
	game.loadBoss(&boss, level, rend);
	game.createButtons(menubuttons, pausebuttons);
	level = 1;
	bossmode = false;
	std::vector<Point> transpoints;
	std::vector<Uint32> transcolors;
	while (!exitf) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		delta = gore.getDelta();
		if (!menu) {
			lvltime = trantime.getTime();
			uptimer += delta;
			downtimer += delta;
			togtimer += delta;
			shootimer += delta;
			banim += delta;
			int fps = 1 / delta;
			if (spawning) {
				double dv = gaptime.getTime();
				if (dv >= 200) {
					game.levelHandler(etypes, nload, spawnloc, enemies, rend, &spawning, &bossmode);
					gaptime.resetTime();
				}
			}
			else {
				ctime = etime.getTime();
			}

			if (ctime > 2000) {
				spawning = true;
				//spawngap = fps / 2;
				game.levelHandler(etypes, nload, spawnloc, enemies, rend, &spawning, &bossmode);
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
			int chy = pdraw.y;
			int chx = pdraw.x + 8;
			int chy2 = pdraw.y + pdraw.h;
			int chx2 = pdraw.x + 8;
			if (gore.GetPixelTexture(walls, &chy, &chx, &wallpitch) != 0) {
				player.y++;
			}
			else if (gore.GetPixelTexture(walls, &chy2, &chx2, &wallpitch) != 0) {
				player.y--;
			}
			if (!game.MassTextureCheck(walls, pdraw.y, pdraw.x, pdraw.x, pdraw.y + pdraw.h, &wallcolor, &wallpitch)) {
				player.x++;
			}
			if (!game.MassTextureCheck(walls, pdraw.y, pdraw.x + pdraw.w, pdraw.x + pdraw.w, pdraw.y + pdraw.h, &wallcolor, &wallpitch)) {
				player.x--;
			}
			if (shootimer > 0.1) {
				if (keys[SDL_SCANCODE_Z]) {
					bullets.push_back(game.createBullet(player.x + 8, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 9, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 7, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 6, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 10, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 8, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 9, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 7, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 6, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 10, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 1, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 2, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 3, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 4, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 5, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 1, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 2, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 3, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 4, player.y, 5, 5, 270, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 5, player.y, 5, 5, 270, 0.001, 1, pbullet));

					bullets.push_back(game.createBullet(player.x + 8, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 9, player.y, 5, 5, 290, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 7, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 6, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 10, player.y, 5, 5, 290, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 8, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 9, player.y, 5, 5, 290, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 7, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 6, player.y, 5, 5, 250, 0.001, 1, pbullet));
					bullets.push_back(game.createBullet(player.x + 10, player.y, 5, 5, 290, 0.001, 1, pbullet));
					Mix_PlayChannel(0, shootsound, 0);
					shootimer = 0;
				}
			}
			graze.x = player.x - 25;
			graze.y = player.y - 25;
			pdraw.x = player.x - 9;
			pdraw.y = player.y - 12;
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
			SDL_RenderClear(rend);
			if (banim > 0.25) {
				switch (backframes) {
				case 0:
					backtex = back1tex;
					backanim = false;
					break;
				case 1:
					backtex = back2tex;
					break;
				case 2:
					backtex = back3tex;
					break;
				case 3:
					backtex = back4tex;
					break;
				case 4:
					backtex = back5tex;
					break;
				case 5:
					backtex = back6tex;
					backanim = true;
					break;
				}
				banim = 0;
				if (backanim) {
					backframes--;
				}
				else {
					backframes++;
				}
			}
			game.updateBackground(rend, backtex, &back, banim);
			int n = 0;
			//To do more realistic growth effect just have multiple transforms activate at once and grow at different rates but right next to each other on the y axis(make them one pixel tall)
			transpoints.clear();
			transcolors.clear();
			bool transactive = false;
			for (auto& i : transforms) {
				if (lvltime > i.activate) {
					i.ct += delta;
					bool er = false;
					if (i.ct > i.speed) {
						//gore.SetPixelTexture(walls, &i.cy, &i.cx, &i.col, &wallpitch);
						transpoints.push_back({ i.cx, i.cy });
						transcolors.push_back(i.col);
						transactive = true;
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
			if (transactive) {
				game.MassTextureSet(walls, transpoints, transcolors, &wallpitch);
			}
			SDL_RenderCopy(rend, walls, NULL, &wallrect);
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
						if (game.isColliding(particles[i], pdraw)) {
							particles[i].er = true;
							score += 100;
							Mix_PlayChannel(3, pickupsound, 0);
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
			if (!hardcore && player.health > 3) {
				player.health = 3;
			}
			else if (hardcore && player.health > 1) {
				player.health = 1;
			}
			SDL_SetRenderDrawColor(rend, 255, 50, 50, 0);
			SDL_Rect hrect = { 750, 680, 50, player.health * 25 };
			SDL_RenderFillRect(rend, &hrect);

			bool rebuiltal = false;
			bool pchange = false;
			int cn = 0;
			for (int i = 0; i < enemies.size();) {
				bool er = false;
				bool skipmove = false;
				bool skipscore = false;
				enemies[i].shootimer += delta;
				enemies[i].movetimer += delta;
				enemies[i].animtimer += delta;
				enemies[i].ptime += delta;
				if (enemies[i].pause) {
					if (enemies[i].ptime > enemies[i].maxp && enemies[i].y < 670) {
						enemies[i].shootmax = enemies[i].burstspeed;
						skipmove = true;
					}
				}
				if (enemies[i].movetimer > enemies[i].timermax) {
					if (enemies[i].offscreen < 3) {
						switch (enemies[i].offscreen) {
						case 0:
							if (enemies[i].x < enemies[i].tgx) {
								enemies[i].x += 250 * delta;
							}
							else {
								enemies[i].offscreen = 3;
							}
							break;
						case 1:
							if (enemies[i].x > enemies[i].tgx) {
								enemies[i].x -= 250 * delta;
							}
							else {
								enemies[i].offscreen = 3;
							}
							break;
						case 2:
							if (enemies[i].y < 20) {
								enemies[i].y += 250 * delta;
							}
							else {
								enemies[i].offscreen = 3;
							}
							break;
						}

					}
					else {
						if (!skipmove) {
							enemies[i].x += enemies[i].trajx;
							enemies[i].y += enemies[i].trajy;
						}
						enemies[i].movetimer = 0;
					}
				}

				if (enemies[i].shootimer > enemies[i].shootmax && enemies[i].y < 670) {
					float angle;
					switch (enemies[i].type) {
					case 0:
						angle = std::atan2f((player.y - 5) - enemies[i].y, (player.x - 6) - enemies[i].x) * 180.0 / M_PI;
						bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, angle, 0.008, 0, ebullet1tex));
						break;
					case 1:
						switch (enemies[i].pattern) {
						case 1:
							angle = std::atan2f((player.y - 15) - enemies[i].y, (player.x - 15) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, angle, 0.006, 0, ebullet1tex));
							angle = std::atan2f((player.y - 15) - enemies[i].y, (player.x - 10) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet((enemies[i].x + (enemies[i].w >> 1) + 5), enemies[i].y + (enemies[i].h >> 1), 10, 10, angle, 0.006, 0, ebullet1tex));
							angle = std::atan2f((player.y - 10) - enemies[i].y, (player.x - 10) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet((enemies[i].x + (enemies[i].w >> 1)), enemies[i].y + 5 + (enemies[i].h >> 1), 10, 10, angle, 0.006, 0, ebullet1tex));
							angle = std::atan2f((player.y - 5) - enemies[i].y, (player.x - 10) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet((enemies[i].x + (enemies[i].w >> 1)), enemies[i].y + 5 + (enemies[i].h >> 1), 10, 10, angle, 0.006, 0, ebullet1tex));
							angle = std::atan2f((player.y - 10) - enemies[i].y, (player.x - 5) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet((enemies[i].x + (enemies[i].w >> 1)), enemies[i].y + 5 + (enemies[i].h >> 1), 10, 10, angle, 0.006, 0, ebullet1tex));
							break;
						case 2:
							angle = std::atan2f((player.y - 15) - enemies[i].y, (player.x - 15) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, angle, 0.005, 0, ebullet1tex));
							angle = std::atan2f((player.y - 15) - enemies[i].y, (player.x - 10) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 10, 10, 10, angle, 0.005, 0, ebullet1tex));
							angle = std::atan2f((player.y - 10) - enemies[i].y, (player.x - 15) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 20, 10, 10, angle, 0.005, 0, ebullet1tex));
							angle = std::atan2f((player.y - 10) - enemies[i].y, (player.x - 5) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 30, 10, 10, angle, 0.005, 0, ebullet1tex));
							break;
						}
						enemies[i].pburst++;
						if (enemies[i].pburst > enemies[i].pmax) {
							enemies[i].ptime = 0;
							enemies[i].pburst = 0;
							if (enemies[i].pattern == 1) {
								enemies[i].pattern = 2;
							}
							else {
								enemies[i].pattern = 1;
							}
							enemies[i].shootmax = enemies[i].origshotspeed;
						}
						break;
					case 2:
						switch (enemies[i].pattern) {
						case 0:
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 75, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 70, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 105, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 100, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 95, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 85, 0.005, 0, ebullet1tex));
							angle = std::atan2f((player.y - 15) - enemies[i].y, (player.x - 15) - enemies[i].x) * 180.0 / M_PI;
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, angle, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 10, 10, 10, angle, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 20, 10, 10, angle, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1) - 30, 10, 10, angle, 0.005, 0, ebullet1tex));
							break;
						case 1:
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 0, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 15, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 30, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 45, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 60, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 75, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 90, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 105, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 120, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 135, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 150, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 165, 0.005, 0, ebullet1tex));
							bullets.push_back(game.createBullet(enemies[i].x + (enemies[i].w >> 1), enemies[i].y + (enemies[i].h >> 1), 10, 10, 180, 0.005, 0, ebullet1tex));
							break;
						}
						enemies[i].pburst++;
						if (enemies[i].pburst > enemies[i].pmax) {
							enemies[i].pattern++;
							if (enemies[i].pattern > 1) {
								enemies[i].pattern = 0;
							}
							enemies[i].pburst = 0;
						}
						break;
					}
					enemies[i].shootimer = 0;
				}
				if (enemies[i].animtimer > enemies[i].animmax) {
					enemies[i].sprites = enemies[i].sprites->next;
					enemies[i].texs = enemies[i].texs->next;
					if (enemies[i].sprites == NULL) {
						enemies[i].sprites = enemies[i].start;
						enemies[i].texs = enemies[i].tstart;
					}
					else {
						std::vector<Point> ps;
						std::vector<Uint32> colors;
						gore.clearTexture(enemies[i].tex, &enemies[i].surf->pitch, enemies[i].w, enemies[i].h);
						for (int h = 0; h < enemies[i].h; h++) {
							for (int w = 0; w < enemies[i].w; w++) {
								if (!enemies[i].points[h][w]) {
									Uint32 col = gore.GetPixelSurface(enemies[i].sprites->current, &h, &w);
									colors.push_back(col);
									ps.push_back({ w, h });
									//gore.SetPixelTexture(enemies[i].tex, &h, &w, &col, &enemies[i].surf->pitch);
								}
							}
						}
						game.MassTextureSet(enemies[i].tex, ps, colors, &enemies[i].surf->pitch);
					}
					enemies[i].change = true;
					enemies[i].animtimer = 0;
				}
				if (enemies[i].change && !rebuiltal) {
					bool dest = false;
					int n = 1;
					for (auto& j : enemies[i].destroycheck) {
						if (enemies[i].points[j.y][j.x]) {
							n++;
						}
					}
					if (n >= enemies[i].destn) {
						dest = true;
					}
					if (!dest) {
						//gore.clearSurface(enemies[i].surf);
						//SDL_DestroyTexture(enemies[i].tex);
						/*for (int h = 0; h < enemies[i].h; h++) {
							for (int w = 0; w < enemies[i].w; w++) {
								if (!enemies[i].points[h][w]) {
									Uint32 col = gore.GetPixelSurface(enemies[i].sprites->current, &h, &w);
									gore.SetPixelSurface(enemies[i].surf, &h, &w, &col);
								}
							}
						}*/
						//enemies[i].tex = SDL_CreateTextureFromSurface(rend, enemies[i].surf);
						for (int j = 0; j < enemies[i].destroyed.size(); j++) {
							if (enemies[i].points[enemies[i].destroyed[j].y][enemies[i].destroyed[j].x]) {
								Uint32 col = 0;
								gore.SetPixelTexture(enemies[i].tex, &enemies[i].destroyed[j].y, &enemies[i].destroyed[j].x, &col, &wallpitch);
							}

						}
						enemies[i].destroyed.clear();
						enemies[i].change = false;
						rebuiltal = true;
					}
					else {
						er = true;
					}
				}
				SDL_Rect rect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
				SDL_RenderCopy(rend, enemies[i].tex, NULL, &rect);
				if (enemies[i].y > 800) {
					er = true;
					skipscore = true;
				}
				if (er) {
					if (!skipscore) {
						switch (enemies[i].type) {
						case 0:
							score += 1000;
							break;
						case 1:
							score += 5000;
							break;
						case 2:
							score += 20000;
							break;
						}
						//explosion particle creation
						for (int h = 0; h < enemies[i].h; h++) {
							for (int w = 0; w < enemies[i].w; w++) {
								if (!enemies[i].points[h][w]) {
									Particle p;
									p.x = enemies[i].x + w + 1;
									p.y = enemies[i].y + h + 1;
									p.rect = { (int)p.x, (int)p.y, 1, 1 };
									p.pd = { w, h, 1, 1 };
									p.trajtimer = 0;
									p.timermax = 0.007;
									p.tex = enemies[i].texs->current;
									p.col = gore.GetPixelSurface(enemies[i].sprites->current, &h, &w);
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
										b.x = enemies[i].x + w + 1;
										b.y = enemies[i].y + h + 1;
										int pw = rand() % 10 + 5;
										int ph = rand() % 10 + 3;
										b.rect = { (int)b.x, (int)b.y, pw, ph };
										b.pd = { 0, 0, pw, ph };
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
						Mix_PlayChannel(1, edeathsound, 0);
					}
					SDL_FreeSurface(enemies[i].surf);
					SDL_DestroyTexture(enemies[i].tex);
					enemies.erase(enemies.begin() + i);
				}
				else {
					i++;
				}
			}
			if (bossmode) {
				SDL_SetRenderDrawColor(rend, 180, 50, 150, 0);
				SDL_Rect herect = { 10, 770, boss.health * 2, 20 };
				SDL_RenderFillRect(rend, &herect);
				game.bossUpdate(&boss, rend, delta, bullets, &player, transforms, &bossmode, &win, &menu);
			}
			cgr = false;
			for (int i = 0; i < bullets.size();) {
				bullets[i].trajtimer += delta;
				if (bullets[i].trajtimer > bullets[i].timermax) {
					bullets[i].x += bullets[i].trajx;
					bullets[i].y += bullets[i].trajy;
					bullets[i].trajtimer = 0;
				}
				int by = 0;
				int bx = 0;
				bool skip = false;
				switch (bullets[i].type) {
				case 0:
					if (game.isColliding(bullets[i], graze)) {
						if (game.isColliding(bullets[i], player)) {
							player.health--;
							bullets[i].x = -30;
							Mix_PlayChannel(3, phitsound, 0);
						}
						else {
							cgr = true;
						}
					}
					break;
				case 1:
					by = (int)bullets[i].y;
					bx = (int)bullets[i].x;
					//Check collision with enemy and delete pixel it's colliding with
					if (gore.GetPixelTexture(walls, &by, &bx, &wallpitch) != 0) {
						bullets[i].x = -30;
						skip = true;
					}
					if (!skip) {
						if (game.isColliding(bullets[i], boss)) {
							int cx = 0;
							int cy = 0;
							if (bullets[i].x > boss.x) { cx = bullets[i].x - boss.x; }
							else { cx = boss.x - bullets[i].x; }
							if (bullets[i].y > boss.y) { cy = bullets[i].y - boss.y; }
							else { cy = boss.y - bullets[i].y; }
							if (gore.GetPixelTexture(boss.tex, &cy, &cx, &boss.surf->pitch) != 0) {
								if (!boss.points[cy][cx]) {
									boss.points[cy][cx] = true;
									boss.destroyed.push_back({ cx, cy });
									Mix_PlayChannel(0, ehitsound, 0);
									score += 2;
									bullets[i].x = -30;
								}
							}
						}
						for (auto& j : enemies) {
							if (game.isColliding(bullets[i], j)) {
								int cx = 0;
								int cy = 0;
								if (bullets[i].x > j.x) { cx = bullets[i].x - j.x; }
								else { cx = j.x - bullets[i].x; }
								if (bullets[i].y > j.y) { cy = bullets[i].y - j.y; }
								else { cy = j.y - bullets[i].y; }
								if (gore.GetPixelTexture(j.tex, &cy, &cx, &j.surf->pitch) != 0) {
									if (!j.points[cy][cx]) {
										j.points[cy][cx] = true;
										j.destroyed.push_back({ cx, cy });
										j.change = true;
										Mix_PlayChannel(0, ehitsound, 0);
										score += 2;
										bullets[i].x = -30;
									}
								}
							}
						}
					}
					break;
				}
				SDL_Rect rect = { bullets[i].x, bullets[i].y, bullets[i].w, bullets[i].h };
				SDL_RenderCopy(rend, bullets[i].tex, NULL, &rect);
				if (bullets[i].x < 0 || bullets[i].x > 800 || bullets[i].y < 0 || bullets[i].y > 800) {
					bullets.erase(bullets.begin() + i);
				}
				else {
					i++;
				}
			}
			panimetime += delta;
			if (panimetime > 0.2) {
				playertex = playertex->next;
				if (playertex == NULL) {
					playertex = pbegin;
				}
				panimetime = 0;
				pchange = true;
			}
			SDL_Rect prect = { pdraw.x, pdraw.y, pdraw.w, pdraw.h };
			//SDL_RenderFillRect(rend, &prect);
			SDL_RenderCopy(rend, playertex->current, NULL, &prect);
			SDL_SetRenderDrawColor(rend, 200, 255, 0, 0);
			SDL_Rect drect = { player.x, player.y, player.w, player.h };
			SDL_RenderFillRect(rend, &drect);
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
					Mix_PlayChannel(2, grazesound, 0);
					score += 10;
					grstimer = 0;
				}
				SDL_Rect rect = { player.x - 20, player.y - 20, 60, 60 };
				SDL_RenderCopy(rend, gr->current, NULL, &rect);
				//SDL_RenderCopyEx(rend, gr->current, NULL, &rect, bang, NULL, flip);
			}
			if (player.health <= 0) {
				player.health = 3;
				Mix_PlayChannel(3, pdeathsound, 0);
				if (hardcore) {
					player.health = 1;
				}
				//Do animation of player going back old spot
				lives--;
				if (lives < 0) {
					menu = true;
					game.death(&player, &boss, &lives, &hardcore, &bossmode, enemies, bullets, particles, rend);
				}
			}
			std::string temp = "Score: " + std::to_string(score);
			gore.drawText(rend, text16, temp, 10, 10, 16, 16);
			int sx = 10;
			for (int i = 0; i < lives; i++, sx += 25) {
				SDL_Rect rect = { sx, 25, 25, 25 };
				SDL_RenderCopy(rend, lifetex, NULL, &rect);
			}
		}
		else if (win) {
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		gore.drawText(rend, text16, "YOU ESCAPED!", 300, 200, 16, 16);
		gore.drawText(rend, text16, "You killed the great beast and fled its body", 150, 250, 16, 16);
		gore.drawText(rend, text16, "Press escape to return to the main menu", 150, 350, 16, 16);

		if (keys[SDL_SCANCODE_ESCAPE]) {
				menu = true;
				win = false;
				game.death(&player, &boss, &lives, &hardcore, &bossmode, enemies, bullets, particles, rend);
		}
		
		}
		else {
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		game.updateMenuButtons(menubuttons, enemies, bullets, particles, rend, &menu, &exitf, &player, &boss, &lives, &hardcore, &bossmode);

		gore.drawText(rend, text16, "Play Normal", 300, 250, 16, 16);
		gore.drawText(rend, text16, "Play Hardcore", 300, 300, 16, 16);
		gore.drawText(rend, text16, "Options", 300, 350, 16, 16);
		gore.drawText(rend, text16, "Exit", 300, 400, 16, 16);
		}
		SDL_RenderPresent(rend);
	}
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
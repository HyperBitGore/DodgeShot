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

//Level one done prereqs(background, boss(will slowly box you in with smaller and smaller boxes))
//Level one actually built out and tested
//Effect and sound for when taking damage
//Death condition
//Make enemy point maps on startup and just copy them when a new enemy is made
//6 basic enemies(less if deem too much time)
//3 levels(3 bosses) like classic STG shmups
//Enemy that grows pixels back
//Enemy that moves back and forth top of screen
//Enemy that strafes you and tries to dodge bullets(could break this up into two different)
//Bosses; Body parts of giant monster you're in; Confined - confined in giant monsters body cause it swallowed you
//First boss classic big guy that gives fast spreads
//Second: A guy that moves around outer edge of screen, like a centipede kind've
//Third: Small guy like you and dodges your attacks and sounds out hard to dodge patterns or tracking ones


//For having enemies with different angles just make new enemy type for loading and on load just change them to one useable
//https://www.pinpng.com/picture/hhmbowh_bullet-hell-sprite-sheet-hd-png-download/, good reference for bullet sprites


//Dont use 92 or 124
std::vector<int> etypes = { 0, 0, 0,
							0, 0, 0, 0, 0, 
							-1,
							-1,
							-1,
							0,
							0, 0,
							0,
							0,
							0,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							0, 0, 0, 0
							-1,
							-1,
							-1,
							0, 1, 0,
							0,
							-1,
							-1,
							-1,
							1, 0,
							-1,
							-1,
							-1,
							-1,
							0, 0, 0, 0,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							1,
							-1,
							0, 0, 0,
							-1,
							-1,
							0, 0,
							-1,
							-1,
							1,
							-1,
							-1,
							0, 0, 0, 0
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							2,
							-1,
							-1,	
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							1, 1,
							0, 0, 0,
							-1,
							-1,
							-1,
							-1,
							-1,
							0, 0,
							-1
							,-1,};
std::vector<int> nload = { 3, 5, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,1,1,1,4,1,1,1,3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
	2,1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 2, 1, 1};
std::vector<Point> spawnloc = { {-100, 100}, {300, 10}, {500, 10}, 
								{910, 60}, {60, 10}, {-200, 200}, {200, 10}, {450, 10},
								{450, 10},
								{450, 10},
								{450, 10},
								{450, 10},
								{920, 10} , {-300, 10}, 
								{250, -10}, 
								{550, 0}, 
								{50, 0},
								{50, 0}, 
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{-500, 200}, {405, 0}, {1200, 300}, {200, 0},
								{50, 0}, 
								{50, 0}, 
								{50, 0}, 
								{-400, 100}, {550, 0}, {1200, 100}, 
								{50, 0}, 
								{50, 0}, 
								{50, 0}, 
								{-300, 150}, {1100, 200}, 
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{-100, 50},{400, 0},{300, 0},{1000, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{350, 0},
								{50, 0},
								{119, 0}, {-305, 138}, {298, 0},
								{50, 0},
								{50, 0},
								{150, 0}, {450, 0},
								{50, 0},
								{50, 0},
								{365, 0}, 
								{50, 0},
								{50, 0},
								{150, 0},{205, 0},{385, 0},{480, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{300, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0}, 
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{250, -10},{450, -10},
								{-250, 150},{1100, 100},{-400, 100},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{50, 0},
								{300, 0},{505, 0},
								{50, 0},
								{50, 0}, };


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
	Uint32 wallcolor = gore.ConvertColorToUint32({ 85, 200, 150, 0 }, surf->format);

	std::vector<Transform> transforms;
	Transform trans;
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
	transforms.push_back(trans);
	trans.activate = 8000;
	trans.sx = 10;
	trans.sy = 399;
	trans.speed = 0.03;
	trans.endx = 790;
	trans.endy = 399;
	trans.cx = 10;
	trans.cy = 399;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 8000;
	trans.sx = 10;
	trans.sy = 401;
	trans.speed = 0.01;
	trans.endx = 790;
	trans.endy = 401;
	trans.cx = 10;
	trans.cy = 401;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 50000;
	trans.sx = 789;
	trans.sy = 400;
	trans.speed = 0.03;
	trans.endx = 10;
	trans.endy = 400;
	trans.cx = 789;
	trans.cy = 400;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 50000;
	trans.sx = 789;
	trans.sy = 401;
	trans.speed = 0.05;
	trans.endx = 10;
	trans.endy = 401;
	trans.cx = 789;
	trans.cy = 401;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 50000;
	trans.sx = 789;
	trans.sy = 399;
	trans.speed = 0.01;
	trans.endx = 10;
	trans.endy = 399;
	trans.cx = 789;
	trans.cy = 399;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 62000;
	trans.sx = 10;
	trans.sy = 600;
	trans.speed = 0.01;
	trans.endx = 790;
	trans.endy = 600;
	trans.cx = 10;
	trans.cy = 600;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 62000;
	trans.sx = 10;
	trans.sy = 601;
	trans.speed = 0.02;
	trans.endx = 790;
	trans.endy = 601;
	trans.cx = 10;
	trans.cy = 601;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 62000;
	trans.sx = 10;
	trans.sy = 599;
	trans.speed = 0.04;
	trans.endx = 790;
	trans.endy = 599;
	trans.cx = 10;
	trans.cy = 599;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 70000;
	trans.sx = 50;
	trans.sy = 10;
	trans.speed = 0.01;
	trans.endx = 50;
	trans.endy = 780;
	trans.cx = 50;
	trans.cy = 20;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 70000;
	trans.sx = 600;
	trans.sy = 20;
	trans.speed = 0.01;
	trans.endx = 600;
	trans.endy = 780;
	trans.cx = 600;
	trans.cy = 20;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 90000;
	trans.sx = 400;
	trans.sy = 10;
	trans.speed = 0.01;
	trans.endx = 400;
	trans.endy = 780;
	trans.cx = 400;
	trans.cy = 20;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 110000;
	trans.sx = 400;
	trans.sy = 100;
	trans.speed = 0.01;
	trans.endx = 400;
	trans.endy = 500;
	trans.cx = 400;
	trans.cy = 100;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 125000;
	trans.sx = 20;
	trans.sy = 285;
	trans.speed = 0.01;
	trans.endx = 600;
	trans.endy = 285;
	trans.cx = 20;
	trans.cy = 285;
	trans.ct = 0;
	trans.col = wallcolor;
	transforms.push_back(trans);
	trans.activate = 150000;
	trans.sx = 600;
	trans.sy = 285;
	trans.speed = 0.01;
	trans.endx = 20;
	trans.endy = 285;
	trans.cx = 600;
	trans.cy = 285;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 150000;
	trans.sx = 400;
	trans.sy = 10;
	trans.speed = 0.01;
	trans.endx = 400;
	trans.endy = 780;
	trans.cx = 400;
	trans.cy = 10;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 155000;
	trans.sx = 50;
	trans.sy = 10;
	trans.speed = 0.01;
	trans.endx = 50;
	trans.endy = 780;
	trans.cx = 50;
	trans.cy = 10;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 155000;
	trans.sx = 600;
	trans.sy = 10;
	trans.speed = 0.01;
	trans.endx = 600;
	trans.endy = 780;
	trans.cx = 600;
	trans.cy = 10;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 160000;
	trans.sx = 21;
	trans.sy = 600;
	trans.speed = 0.01;
	trans.endx = 780;
	trans.endy = 600;
	trans.cx = 21;
	trans.cy = 600;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 160000;
	trans.sx = 21;
	trans.sy = 601;
	trans.speed = 0.01;
	trans.endx = 780;
	trans.endy = 601;
	trans.cx = 21;
	trans.cy = 601;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	trans.activate = 160000;
	trans.sx = 21;
	trans.sy = 599;
	trans.speed = 0.01;
	trans.endx = 780;
	trans.endy = 599;
	trans.cx = 21;
	trans.cy = 599;
	trans.ct = 0;
	trans.col = 0;
	transforms.push_back(trans);
	std::cout << spawnloc.size() << " : " << etypes.size() << std::endl;
	std::cout << nload.size() << std::endl;
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

	texp playertex = gore.loadTextureList({ "player1.png", "player2.png" }, { 20, 20 }, { 25, 25 }, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");
	spxp playersprites = gore.loadSpriteList({ "player1.png", "player2.png" }, { 20, 20 }, { 25, 25 }, SDL_PIXELFORMAT_RGBA8888, rend, "Sprites/");

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
	SDL_SetTextureBlendMode(particletex, SDL_BLENDMODE_BLEND);

	//use surf
	SDL_Rect wallrect = { 0,0,800,800 };
	SDL_Texture* walls = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);
	int ty = 100;
	int tx = 400;
	int wallpitch = surf->pitch;
	int realpitch = wallpitch / sizeof(unsigned int);
	//Uint32 tcolor = gore.ConvertColorToUint32({ 255, 255, 255, 0 }, surf->format);
	
	game.MassTextureSet(walls, 0, 0, 10, 800, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, 0, 0, 800, 10, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, 0, 790, 800, 800, &wallcolor, &wallpitch);
	game.MassTextureSet(walls, 790, 0, 800, 800, &wallcolor, &wallpitch);
	//gore.SetPixelTexture(walls, &ty, &tx, &wallcolor, &wallpitch);

	Mix_Chunk* grazesound = Mix_LoadWAV("Sprites/graze.wav");
	Mix_Chunk* ehitsound = Mix_LoadWAV("Sprites/ehit.wav");
	Mix_Chunk* edeathsound = Mix_LoadWAV("Sprites/edeath.wav");

	Entity player = { 400, 400, 5, 5 };
	player.health = 50;
	texp pbegin = playertex;
	Entity graze = { 400, 400, 50, 50 };
	Entity pdraw = { 400, 400, 20, 25 };
	Entity back = { 0, -200, 800, 800 };
	Boss boss;
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
	double panimetime = 0;

	bool run = false;
	bool cgr = false;
	bool spawning = false;
	bool bossmode = false;

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
	game.loadBoss(&boss, level, rend);
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
				bullets.push_back(game.createBullet(player.x + 8, player.y + 10, 5, 5, 270, 0.001, 1, pbullet));
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
		pdraw.x = player.x - 7;
		pdraw.y = player.y - 10;
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
					if (game.isColliding(particles[i], pdraw)) {
						particles[i].er = true;
						player.health++;
						score += 50;
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

			std::string temp = "Score: " + std::to_string(score);
			gore.drawText(rend, text16, temp, 10, 10, 16, 16);
			SDL_RenderPresent(rend);
	}
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
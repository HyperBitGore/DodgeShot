#pragma once
#include <iostream>
#include "GoreEngine.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <chrono>

extern int curnload;
extern int curetype;
extern int prog;
extern spxp enem1head;
extern texp enem1tex;
struct Point {
	int x;
	int y;
};

struct Entity {
	float x;
	float y;
	int w;
	int h;
	int health;
};
struct Bullet : Entity {
	float trajx;
	float trajy;
	double trajtimer;
	double timermax;
	int type;
};
struct Enemy : Entity {
	float movetimer;
	float timermax;
	float shootimer;
	float shootmax;
	float animtimer;
	float animmax;
	int type;
	spxp sprites;
	spxp start;
	texp texs;
	texp tstart;
	//Real
	std::vector<std::vector<bool>> points;
	SDL_Surface* surf;
	SDL_Texture* tex;
	bool change;
	std::vector<Point> destroycheck;
	int destn;
	float trajx;
	float trajy;
	//0 - neg x; 1 - pos x; 2 - neg y;
	int offscreen;
	float tgx;
	bool pause;
};
struct Particle : Bullet {
	SDL_Rect pd;
	SDL_Rect rect;
	SDL_Texture* tex;
	//Uint32 col;
	bool er;
};

struct Transform {
	int sx;
	int sy;
	int endx;
	int endy;
	int cx;
	int cy;
	double activate;
	double speed;
	float ct;
	Uint32 col;
};


class Game {
public:
	float trajX(float deg);
	float trajY(float deg);
	Bullet createBullet(float x, float y, int w, int h, float deg, float speed, int type);
	bool isColliding(Entity b, Entity e) {
		if (b.x < e.x + e.w && b.x + b.w > e.x && b.y < e.y + e.h && b.y + b.h > e.y) {
			return true;
		}
		return false;
	}
	void constructAlphabet(SDL_Renderer* rend, TTF_Font* font, SDL_Color color, texp& head) {
		Gore gore;
		for (int i = 33; i < 123; i++) {
			char c = i;
			std::string co;
			co.push_back(c);
			SDL_Surface* surf = TTF_RenderText_Solid(font, co.c_str(), color);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
			SDL_FreeSurface(surf);
			gore.insertTex(head, tex, co);
			//std::cout << co << std::endl;
		}
	}

	SDL_Texture* loadBackground(int level, SDL_Renderer* rend);
	void updateBackground(SDL_Renderer* rend, SDL_Texture* ctex, Entity* back, double delta);
	
	void createEnemy(spxp& enemhead, texp& enemtex, std::vector<Enemy>& enemies, int x, int y, int type, float degree, SDL_Renderer* rend);

	void convertToLvl(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Transform>& transforms, const char* file);
	void loadLevel(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Transform>& transforms, const char* file);
	void levelHandler(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Enemy>& enemies, SDL_Renderer* rend, bool* spawning);
	void MassTextureSet(SDL_Texture* tex, SDL_Surface* surf, int sy, int sx, int endx, int endy, Uint32* pixel, int* pitch);
};

class Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
public:
	void startTime() {
		start = std::chrono::steady_clock::now();
	}
	double getTime() {
		end = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	void resetTime() {
		start = std::chrono::steady_clock::now();
		end = std::chrono::steady_clock::now();
	}
};

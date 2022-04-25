#include "Header.h"




void Game::endlessPopulate(std::vector<Enemy>& enemies, SDL_Renderer* rend) {
	//enemy populating
	int n = rand() % 4;
	endlesspopcount++;
	for (int i = 0; i < n; i++) {
		spxp sp = NULL;
		texp tp = NULL;
		int roll = rand() % 100 + 1;
		int type = 0;
		if (roll > 70) {
			type = rand() % 2;
		}
		else if (roll > 98) {
			type = rand() % 3;
		}
		else {
			type = 0;
		}
		switch (type) {
		case 0:
			sp = enem1head;
			tp = enem1tex;
			break;
		case 1:
			sp = enem2head;
			tp = enem2tex;
			break;
		case 2:
			sp = enem3head;
			tp = enem3tex;
			break;
		}
		int sx = rand() % 780;
		int sy = -10;
		createEnemy(sp, tp, enemies, sx, sy, type, 90, rend);
	}
	//transform populating
	if (endlesspopcount >= 10) {
		Transform trans;
		//vertical lines
		trans.activate = 0;
		trans.sx = vertstarts[0];
		trans.sy = 20;
		trans.speed = 0.01;
		trans.endx = vertstarts[0];
		trans.endy = 780;
		trans.cx = trans.sx;
		trans.cy = trans.sy;
		trans.ct = 0;
		trans.col = wallcolor;
		transforms.push_back(trans);
		vertstarts[0] += vertinc;
		trans.activate = 0;
		trans.sx = vertstarts[1];
		trans.sy = 20;
		trans.speed = 0.01;
		trans.endx = vertstarts[1];
		trans.endy = 780;
		trans.cx = trans.sx;
		trans.cy = trans.sy;
		trans.ct = 0;
		trans.col = wallcolor;
		transforms.push_back(trans);
		vertstarts[1] -= vertinc;
		//horizontal lines
		trans.activate = 0;
		trans.sx = 20;
		trans.sy = horizontalstarts[0];
		trans.speed = 0.01;
		trans.endx = 780;
		trans.endy = horizontalstarts[0];
		trans.cx = trans.sx;
		trans.cy = trans.sy;
		trans.ct = 0;
		trans.col = wallcolor;
		transforms.push_back(trans);
		horizontalstarts[0] += horinc;
		trans.activate = 0;
		trans.sx = 20;
		trans.sy = horizontalstarts[1];
		trans.speed = 0.01;
		trans.endx = 780;
		trans.endy = horizontalstarts[1];
		trans.cx = trans.sx;
		trans.cy = trans.sy;
		trans.ct = 0;
		trans.col = wallcolor;
		transforms.push_back(trans);
		horizontalstarts[1] -= horinc;
		endlesspopcount = 0;
	}
}
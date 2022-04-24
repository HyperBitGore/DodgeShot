#include "Header.h"


void Game::bossUpdate(Boss* b, SDL_Renderer* rend, double delta, std::vector<Bullet>& bullets, Entity* p, std::vector<Transform>& transforms) {
	Gore gore;
	b->shtime += delta;
	b->movetime += delta;
	if (b->shtime > b->shmax) {
		int n = 0, gap = 0, deginc = 0;
		switch (b->pattern) {
		case 0:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 0, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 15, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 30, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 45, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 60, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 75, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 90, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 105, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 120, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 135, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 150, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 165, 0.0035, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 180, 0.0035, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 1:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 10, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 25, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 40, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 55, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 70, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 85, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 100, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 115, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 130, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 145, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 160, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 175, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 190, 0.003, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 2:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 20, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 30, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 40, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 50, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.0025, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 3:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet((b->x + b->w / 2), (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 20) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				bullets.push_back(createBullet((b->x + b->w / 2) - 10, (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 40) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				bullets.push_back(createBullet((b->x + b->w / 2) - 20, (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 60) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				bullets.push_back(createBullet((b->x + b->w / 2) + 10, (b->y + b->h / 2), 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x + 20) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				bullets.push_back(createBullet((b->x + b->w / 2) + 20, (b->y + b->h / 2), 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x + 40) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				bullets.push_back(createBullet((b->x + b->w / 2) + 30, (b->y + b->h / 2), 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x + 60) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.005, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 4:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 20, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 30, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 40, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 50, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 60, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 70, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 80, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 90, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.003, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 5:
			switch (b->type) {
			case 1:
				for (n = 0, gap = 0; n < 50; n++, gap += 20) {
					float deg = (float)n * 3.6;
					bullets.push_back(createBullet((b->x + b->w / 2) - gap, (b->y + b->h / 2), 10, 10, deg, 0.005, 0, ebullet1tex));
				}
				break;
			case 2:

				break;
			}
			break;
		case 6:
			switch (b->type) {
			case 1:
				for (n = 0, gap = 0; n < 20; n++, gap += 25) {
					float deg = std::atan2f((p->y + gap) - (b->y + b->h / 2), (p->x - gap) - (b->x + b->w / 2)) * 180.0 / M_PI;
					bullets.push_back(createBullet((b->x + b->w / 2), (b->y + b->h / 2), 10, 10, deg, 0.005, 0, ebullet1tex));
				}
				break;
			case 2:

				break;
			}
			break;
		case 7:
			switch (b->type) {
			case 1:
				for (n = 0, gap = 0, deginc = 180; n < 50; n++, gap += 20, deginc -= 3.6) {
					float deg = deginc;
					bullets.push_back(createBullet((b->x + b->w / 2) + gap, (b->y + b->h / 2), 10, 10, deg, 0.005, 0, ebullet1tex));
				}
				break;
			case 2:

				break;
			}
			break;
		}
		b->burst++;
		switch (b->type) {
		case 1:
			switch (b->phase) {
			case 0:
				if (b->burst == 2) {
					b->pattern = 1;
					b->shmax = 0.5;
				}
				else if (b->burst == 4) {
					b->pattern = 2;
					b->shmax = 0.8;
				}
				else if (b->burst == 7) {
					b->pattern = 0;
					b->shmax = 0.5;
					b->burst = 0;
				}
				break;
			case 1:
				//targeting lines with a spread, targeting you
				if (b->burst <= 2) {
					b->pattern = 3;
					b->shmax = 0.4;
				}
				else if (b->burst == 3) {
					b->pattern = 4;
					b->shmax = 0.6;
				}
				else if (b->burst == 6) {
					b->pattern = 3;
					b->shmax = 0.4;
					b->burst = 0;
				}
				break;
			case 2:
				//slow dodging through a large amount of slow bullets
				if (b->burst <= 3) {
					b->pattern = 5;
				}
				else if (b->burst == 4) {
					b->pattern = 7;
				}
				else if (b->burst == 8) {
					b->pattern = 6;
				}
				else if (b->burst > 12) {
					b->pattern = 5;
					b->burst = 0;
				}
				break;
			}
			break;
		case 2:
			switch (b->phase) {
			case 0:

				break;
			}
			break;
		}
		b->shtime = 0;
	}
	if (b->y < 35) {
		b->y += 250 * delta;
	}
	else {
		if (b->movetime > b->maxmove) {
			b->x += b->trajx;
			b->y += b->trajy;
			b->movetime = 0;
		}
	}
	//phase checker
	switch (b->type) {
	case 1:
		if ((float)b->health > (float)b->maxhealth * 0.65) {
			if (b->x < 50) {
				b->opposite = true;
			}
			else if (b->x + b->w > 750) {
				b->opposite = false;
			}
			if (b->opposite) {
				b->trajx = trajX(0);
				b->trajy = trajY(0);
			}
			else {
				b->trajx = trajX(180);
				b->trajy = trajY(180);
			}
			b->phase = 0;
		}
		else if ((float)b->health > (float)b->maxhealth * 0.35) {
			if (b->y + b->h > 350) {
				b->opposite = true;
			}
			else if (b->y < 85) {
				b->opposite = false;
			}
			if (b->x < 50) {
				b->oppositex = true;
			}
			else if (b->x + b->w > 750) {
				b->oppositex = false;
			}
			if (b->opposite) {
				b->trajy = trajY(245);
			}
			else {
				b->trajy = trajY(75);
			}
			if (b->oppositex) {
				b->trajx = trajX(0);
			}
			else {
				b->trajx = trajX(180);
			}
			b->phase = 1;
		}
		else {

			if (b->y > 100) {
				b->opposite = false;
			}
			else if (b->y < 150) {
				b->opposite = true;
			}
			if (b->x < 200) {
				b->oppositex = false;
			}
			else if (b->x > 250) {
				b->oppositex = true;
			}

			if (b->opposite) {
				b->trajy = trajY(90);
			}
			else {
				b->trajy = trajY(270);
			}
			if (b->oppositex) {
				b->trajx = trajX(180);
			}
			else {
				b->trajx = trajX(0);
			}
			//move to middle of box and then move up and down
			b->phase = 2;
		}
		break;
	case 2:

		break;
	}
	//visual editing
	std::vector<Uint32> colors;
	for (int i = 0; i < b->destroyed.size();) {
		if (!b->points[b->destroyed[i].y][b->destroyed[i].x]) {
			b->destroyed.erase(b->destroyed.begin() + i);
		}
		else {
			colors.push_back(0);
			for (auto& j : b->destroychecks) {
				if (b->destroyed[i].x == j.x && b->destroyed[i].y == j.y) {
					b->health--;
				}
			}
			i++;
		}
	}
	MassTextureSet(b->tex, b->destroyed, colors, &b->surf->pitch);
	b->destroyed.clear();
	//Boss transforms, activate based on health
	for (int i = 0; i < b->activates.size();) {
		bool er = false;
		if (b->health < b->activates[i].health) {
			transforms.push_back(b->activates[i].trans);
			er = true;
		}
		if (er) {
			b->activates.erase(b->activates.begin() + i);
		}
		else {
			i++;
		}
	}
	SDL_Rect rect = { b->x, b->y, b->w, b->h };
	SDL_RenderCopy(rend, b->tex, NULL, &rect);
}

void Game::loadBoss(Boss* boss, int level, SDL_Renderer* rend) {
	Gore gore;
	(*boss).type = level;
	(*boss).x = 400;
	(*boss).y = -300;
	(*boss).phase = 0;
	(*boss).movetime = 0;
	(*boss).pattern = 0;
	(*boss).shtime = 0;
	boss->antime = 0;
	(*boss).anmax = 0.2;
	boss->burst = 0;
	boss->opposite = false;
	boss->oppositex = false;
	TRActivate t;
	switch (level) {
	case 1:
		//Put three different spots for destroy checks
		generateDestroyChecks(boss->destroychecks, 180, 135, 189, 141);
		generateDestroyChecks(boss->destroychecks, 8, 101, 16, 105);
		generateDestroyChecks(boss->destroychecks, 87, 48, 115, 55);
		generateDestroyChecks(boss->destroychecks, 39, 82, 45, 87);
		generateDestroyChecks(boss->destroychecks, 54, 20, 61, 24);
		generateDestroyChecks(boss->destroychecks, 117, 18, 125, 21);
		generateDestroyChecks(boss->destroychecks, 143, 70, 151, 79);
		(*boss).h = 200;
		(*boss).w = 200;
		(*boss).health = 100;
		(*boss).maxmove = 0.08;
		(*boss).shmax = 0.5;
		(*boss).trajx = trajX(90);
		(*boss).trajy = trajY(90);
		boss->sprites = boss1head;
		//Transforms 
		//first phase box
		t.health = boss->destroychecks.size();
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 30;
		t.trans.sy = 500;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 780;
		t.trans.endy = 500;
		t.trans.speed = 0.008;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = boss->destroychecks.size();
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 30;
		t.trans.sy = 100;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 780;
		t.trans.endy = 100;
		t.trans.speed = 0.008;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = boss->destroychecks.size();
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 100;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 100;
		t.trans.endy = 780;
		t.trans.speed = 0.008;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = boss->destroychecks.size();
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 600;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 600;
		t.trans.endy = 780;
		t.trans.speed = 0.008;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		//second phase box
		t.health = (int)(boss->destroychecks.size() - 15) * 0.65;
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 130;
		t.trans.sy = 400;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 600;
		t.trans.endy = 400;
		t.trans.speed = 0.02;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = (int)(boss->destroychecks.size() - 15) * 0.65;
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 130;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 130;
		t.trans.endy = 500;
		t.trans.speed = 0.02;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = (int)(boss->destroychecks.size() - 15) * 0.65;
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 500;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 500;
		t.trans.endy = 500;
		t.trans.speed = 0.02;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		//third phase box
		t.health = (int)(boss->destroychecks.size() - 15) * 0.35;
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 160;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 160;
		t.trans.endy = 400;
		t.trans.speed = 0.02;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		t.health = (int)(boss->destroychecks.size() - 15) * 0.35;
		t.trans.activate = 0;
		t.trans.col = wallcolor;
		t.trans.sx = 450;
		t.trans.sy = 20;
		t.trans.cx = t.trans.sx;
		t.trans.cy = t.trans.sy;
		t.trans.endx = 450;
		t.trans.endy = 400;
		t.trans.speed = 0.02;
		t.trans.ct = 0;
		boss->activates.push_back(t);
		break;
	case 2:

		break;
	}
	boss->health = boss->destroychecks.size() - 15;
	boss->maxhealth = boss->health;
	(*boss).surf = SDL_CreateRGBSurfaceWithFormat(0, (*boss).w, (*boss).h, 32, SDL_PIXELFORMAT_RGBA8888);
	(*boss).tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, (*boss).w, (*boss).h);
	SDL_SetTextureBlendMode(boss->tex, SDL_BLENDMODE_BLEND);
	std::vector<Point> points;
	std::vector<Uint32> colors;
	for (int i = 0; i < boss->h; i++) {
		std::vector<bool> c;
		for (int j = 0; j < boss->w; j++) {
			Uint32 col = gore.GetPixelSurface(boss->sprites->current, &i, &j);
			colors.push_back(col);
			points.push_back({ j, i });
			c.push_back(false);
		}
		boss->points.push_back(c);
	}
	MassTextureSet(boss->tex, points, colors, &boss->surf->pitch);
}


void Game::regrow(std::vector<Point> points, SDL_Texture* tex, SDL_Surface* surf, std::vector<std::vector<bool>>& dest) {
	//copy back point colors from surface to texture, and change the dest back to false
	Gore gore;
	for (auto& i : points) {
		dest[i.y][i.x] = false;
		Uint32 col = gore.GetPixelSurface(surf, &i.y, &i.x);
		gore.SetPixelTexture(tex, &i.y, &i.x, &col, &surf->pitch);
	}
}
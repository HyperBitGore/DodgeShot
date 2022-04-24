#include "Header.h"


void Game::bossUpdate(Boss* b, SDL_Renderer* rend, double delta, std::vector<Bullet>& bullets, Entity* p) {
	Gore gore;
	b->shtime += delta;
	b->movetime += delta;
	if (b->shtime > b->shmax) {
		switch (b->pattern) {
		case 0:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 0, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 15, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 30, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 45, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 60, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 75, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 90, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 105, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 120, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 135, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 150, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 165, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 180, 0.002, 0, ebullet1tex));
				break;
			case 2:
					
				break;
			}
			break;
		case 1:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 10, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 25, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 40, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 55, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 70, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 85, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 100, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 115, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 130, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 145, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 160, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 175, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, 190, 0.002, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 2:
			switch (b->type) {
			case 1:
				bullets.push_back(createBullet(b->x + b->w / 2, b->y + b->h / 2, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 10, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 20, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 30, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 40, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				bullets.push_back(createBullet(b->x + b->w / 2, (b->y + b->h / 2) - 50, 10, 10, std::atan2f((p->y) - (b->y + b->h / 2), (p->x - 10) - (b->x + b->w / 2)) * 180.0 / M_PI, 0.002, 0, ebullet1tex));
				break;
			case 2:

				break;
			}
			break;
		case 3:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 4:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		case 5:
			switch (b->type) {
			case 1:

				break;
			case 2:

				break;
			}
			break;
		}
		b->burst++;
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

			break;
		case 2:

			break;
		}

		b->shtime = 0;
	}
	if (b->y < 0) {
		b->y += 250 * delta;
	}
	else {
		if (b->movetime > b->maxmove) {
		b->x += b->trajx;
		b->y += b->trajy;
		b->movetime = 0;
		}
	}
	//visual editing
	std::vector<Uint32> colors;
	for (int i = 0; i < b->destroyed.size();) {
		if (!b->points[b->destroyed[i].y][b->destroyed[i].x]) {
			b->destroyed.erase(b->destroyed.begin() + i);
		}
		else {
			colors.push_back(0);
			i++;
		}
	}
	MassTextureSet(b->tex, b->destroyed, colors, &b->surf->pitch);
	b->destroyed.clear();

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
	switch (level) {
	case 1:
		(*boss).h = 200;
		(*boss).w = 200;
		(*boss).health = 100;
		(*boss).maxmove = 0.3;
		(*boss).shmax = 0.5;
		(*boss).trajx = trajX(90);
		(*boss).trajy = trajY(90);
		boss->sprites = boss1head;
		break;
	case 2:

		break;
	}
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
			//gore.SetPixelTexture(boss->tex, &i, &j, &col, &boss->surf->pitch);
			c.push_back(false);
		}
		boss->points.push_back(c);
	}
	MassTextureSet(boss->tex, points, colors, &boss->surf->pitch);
}
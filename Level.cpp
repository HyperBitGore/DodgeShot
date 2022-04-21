#include "Header.h"


void Game::MassTextureSet(SDL_Texture* tex, SDL_Surface* surf, int sy, int sx, int endx, int endy, Uint32* pixel, int* pitch) {
	Uint32* pixels;
	int pixpitch = (*pitch) / sizeof(unsigned int);
	SDL_LockTexture(tex, NULL, (void**)&pixels, pitch);
	for (int h = sy; h <= endy; h++) {
		for (int w = sx; w <= endx; w++) {
			pixels[h * pixpitch + w] = *pixel;
		}
	}
	SDL_UnlockTexture(tex);
}



void Game::levelHandler(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Enemy>& enemies, SDL_Renderer* rend, bool *spawning) {
	if (curnload <= nload.size() - 1) {
		bool oneframe = false;
		for (int i = prog; i < nload[curnload]; i++, curetype++, oneframe = true) {
			if (oneframe) {
				prog = i;
				return;
			}
			spxp sp = NULL;
			texp tp = NULL;
			switch (etypes[curetype]) {
			case 0:
				sp = enem1head;
				tp = enem1tex;
				break;
			case 1:

				break;
			}
			createEnemy(sp, tp, enemies, spawnloc[curetype].x, spawnloc[curetype].y, etypes[curetype], 90, rend);
		}
		curnload++;
		prog = 0;
		*spawning = false;
	}
	else {
		*spawning = false;
	}
}


void Game::convertToLvl(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Transform>& transforms, const char* file) {
	char* write = (char*)std::malloc((etypes.size() * sizeof(int)) + ((nload.size() * sizeof(int)) + nload.size() * sizeof(int)) + ((sizeof(int) * 2) * spawnloc.size()));
	int* t = (int*)write;
	int n = 1;
	int k = 0;
	//data serilization
	for (int i = 0; i < etypes.size(); i++, n++) {
		*t = etypes[i];
		t++;
		*t = spawnloc[i].x;
		t++;
		*t = spawnloc[i].y;
		t++;
		if (n >= nload[k]) {
			*t = '|';
			t++;
			*t = nload[k];
			t++;
			n = 1;
			k++;
			if (k > nload.size() - 1) {
				k = nload.size() - 1;
			}
		}
	}
	//write to file
	std::ofstream f;
	f.open(file);
	int s = (etypes.size() * sizeof(int)) + ((nload.size() * sizeof(int)) + nload.size() * sizeof(int)) + ((sizeof(int) * 2) * spawnloc.size());
	for (int i = 0; i < s; i++) {
		f << write[i];
	}
	char kk[4];
	int* r = (int*)kk;
	*r = -1;
	for (int i = 0; i < 4; i++) {
		f << kk[i];
	}
	for (auto& i : transforms) {
		char kur[4];
		int* tb = (int*)kur;
		*tb = i.sx;
		for (int i = 0; i < 4; i++) {
			f << kur[i];
		}
		*tb = i.sy;
		for (int i = 0; i < 4; i++) {
			f << kur[i];
		}
		*tb = i.endx;
		for (int i = 0; i < 4; i++) {
			f << kur[i];
		}
		*tb = i.endy;
		for (int i = 0; i < 4; i++) {
			f << kur[i];
		}
		Uint32* tl = (Uint32*)kur;
		*tl = i.col;
		for (int i = 0; i < 4; i++) {
			f << kur[i];
		}
		char kl[8];
		double* tk = (double*)kl;
		*tk = i.speed;
		for (int i = 0; i < 8; i++) {
			f << kl[i];
		}
		*tk = i.activate;
		for (int i = 0; i < 8; i++) {
			f << kl[i];
		}
	}
	for (int i = 0; i < 4; i++) {
		f << kk[i];
	}
	f.close();
	std::free(write);
}



void Game::loadLevel(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, std::vector<Transform>& transforms, const char* file) {
	etypes.clear();
	nload.clear();
	spawnloc.clear();
	transforms.clear();
	std::ifstream f;
	f.open(file);
	std::string line;
	size_t size = 0;
	int ln = 0;
	//this isnt right 
	while (getline(f, line)) {
		bool contains = false;
		for (int i = 0; i < line.size(); i++) {
			size++;
			if (line[i] == '|') {
				contains = true;
			}
		}
		if (!contains) {
			size += 2;
		}
		ln++;
	}

	f.close();
	f.open(file);
	char* data = (char*)std::malloc(size);
	char* d = data;
	int cn = 0;
	while (getline(f, line)) {
		for (int i = 0; i < line.size(); i++) {
			*d = line[i];
			d++;
		}
		if (cn < ln) {
			*d = '\n';
			d++;
			cn++;
		}
	}
	f.close();
	f.open(file);
	int n = 0;
	bool writeload = false;
	int* t = (int*)data;
	//-51 'Í'	char
	//allocate more memory
	while (*t != -1) {
		if (writeload) {
			nload.push_back(*t);
			t++;
			writeload = false;
		}
		Point p;
		switch (n) {
		case 0:
			etypes.push_back(*t);
			t++;
			break;
		case 1:
			p.x = *t;
			t++;
			break;
		case 2:
			p.y = *t;
			t++;
			break;
		}
		n++;
		if (n > 2) {
			spawnloc.push_back(p);
			n = 0;
			if (*t == 124) {
				writeload = true;
				t++;
			}
		}
	}
	t++;
	//Read transform data
	while (*t != -1) {
		Transform i;
		i.sx = *t;
		t++;
		i.sy = *t;
		t++;
		i.endx = *t;
		t++;
		i.endy = *t;
		t++;
		Uint32* tm = (Uint32*)t;
		i.col = *tm;
		t++;
		double* tk = (double*)t;
		i.speed = *tk;
		tk++;
		i.activate = *tk;
		tk++;
		t += 4;
		i.ct = 0;
		i.cx = i.sx;
		i.cy = i.sy;
		transforms.push_back(i);
	}

	f.close();
	std::free(data);
}
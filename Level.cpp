#include "Header.h"


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
			createEnemy(sp, tp, enemies, spawnloc[curetype].x, spawnloc[curetype].y, etypes[curetype], rend);
		}
		curnload++;
		prog = 0;
		*spawning = false;
	}
	else {
		*spawning = false;
	}
}


void Game::convertToLvl(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, const char* file) {
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
	f.close();
	std::free(write);
}



void Game::loadLevel(std::vector<int>& etypes, std::vector<int>& nload, std::vector<Point>& spawnloc, const char* file) {
	etypes.clear();
	nload.clear();
	spawnloc.clear();
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
	f.close();
	std::free(data);
}
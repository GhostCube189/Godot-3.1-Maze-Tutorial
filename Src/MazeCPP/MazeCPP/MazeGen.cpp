#include "MazeGen.h"

MazeGen::MazeGen(int w, int h, uint32_t seed) {
	InitializeRandom32(seed);
	mazeWidth = w;
	mazeHeight = h;
	mazeData = new bool*[w];
	for (int x = 0; x < w; x++) {
		mazeData[x] = new bool[h];
		for (int y = 0; y < h; y++) {
			if ((x % 2 == 0) && (y % 2 == 0)) {
				mazeData[x][y] = false;
			} else {
				mazeData[x][y] = true;
			}
		}
	}
}

MazeGen::~MazeGen() {
	if (mazeData) {
		for (int x = 0; x < mazeWidth; x++) {
			delete mazeData[x];
		}
	}
	delete mazeData; mazeData = nullptr;
}

void MazeGen::InitializeRandom32(uint32_t seed) {
	if (seed == 0) {
		std::random_device rd;
		seed = rd();
	}
	rng.seed(seed);
}

bool MazeGen::IsWall(int x, int y) {
	return mazeData[x][y];
}

void MazeGen::GenerateMaze() {
	for (int col = 0; col < mazeWidth; col += 2) {
		for (int row = 0; row < mazeHeight; row += 2) {
			if ((row == mazeHeight - 1) && (col == mazeWidth - 1)) {
				//leave this alone
			} else if (row == mazeHeight - 1) {
				//bottom row, so force col+1 open
				mazeData[col + 1][row] = false;
			} else if (col == mazeWidth - 1) {
				//east col, so force row+1 open
				mazeData[col][row + 1] = false;
			} else {
				if (rng() % 2 == 0) {
					mazeData[col + 1][row] = false;
				} else {
					mazeData[col][row + 1] = false;
				}
			}
		}
	}
}
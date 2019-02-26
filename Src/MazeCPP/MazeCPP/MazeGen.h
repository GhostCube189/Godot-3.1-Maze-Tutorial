#pragma once

#include <random>
#include <stdlib.h>

class MazeGen {
private:
	int mazeWidth, mazeHeight;
	bool** mazeData;
	std::mt19937 rng;
public:
	MazeGen(int width, int height, uint32_t seed = 0);
	~MazeGen();
	void GenerateMaze();
	void InitializeRandom32(uint32_t seed);
	bool IsWall(int column, int row);
};
#pragma once

#include <vector>
#include "NodeTracker.h"

class MazeGen {
private:
	int width, height;
	NodeTracker* pVisited;
	std::vector<std::vector<bool>> wall;
public:
	MazeGen(int width, int height, uint32_t seed = 0);
	~MazeGen();
	void GenerateMaze();
	bool IsWall(int column, int row);
};
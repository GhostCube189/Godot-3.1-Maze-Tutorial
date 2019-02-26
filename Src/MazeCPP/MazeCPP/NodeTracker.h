#pragma once

#include <vector>
#include <random>

class NodeTracker {
private:
	std::vector<std::vector<bool>> visited;
	std::mt19937 rng;
public:
	NodeTracker(int w, int h, uint32_t seed = 0);
	~NodeTracker();

	bool IsVisited(int x, int y);
	void SetVisited(int x, int y);
	unsigned char GetUnvisitedNeighbor(int x, int y);
	void InitializeRandom32(uint32_t seed);
};
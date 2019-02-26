#include "NodeTracker.h"

NodeTracker::NodeTracker(int w, int h, uint32_t seed) {
	InitializeRandom32(seed);
	visited.resize(w + 4, std::vector<bool>(h + 4, false));//pad by 2 each dir

	//padding
	for (int x = 0; x < w + 4; x++) {
		visited[x][0] = visited[x][1] = true;
		visited[x][h + 3] = visited[x][h + 2] = true;
	}
	for (int y = 0; y < h + 4; y++) {
		visited[0][y] = visited[1][y] = true;
		visited[w + 3][y] = visited[w + 2][y] = true;
	}
}

NodeTracker::~NodeTracker() {}

void NodeTracker::InitializeRandom32(uint32_t seed) {
	if (seed == 0) {
		std::random_device rd;
		seed = rd();
	}
	rng.seed(seed);
}

bool NodeTracker::IsVisited(int x, int y) {
	return visited[x + 2][y + 2];//2 for padding
}

void NodeTracker::SetVisited(int x, int y) {
	visited[x + 2][y + 2] = true;//2 for padding
}

unsigned char NodeTracker::GetUnvisitedNeighbor(int x, int y) {
	bool neighbor[4];
	unsigned int unvisited = 0;
	neighbor[0] = IsVisited(x - 2, y);//left
	neighbor[1] = IsVisited(x, y - 2);//up
	neighbor[2] = IsVisited(x + 2, y);//right
	neighbor[3] = IsVisited(x, y + 2);//down
	for (int x = 0; x < 4; x++) {
		if (neighbor[x] == false) {
			unvisited++;
		}
	}
	if (unvisited == 0) return 0;

	unsigned int randomPick = rng() % unvisited;
	unsigned int i = 0;
	unsigned char dir;
	for (dir = 0; dir < 4; dir++) {
		if (neighbor[dir] == false) {
			//unvisited
			if (i == randomPick) break;
			i++;
		}
	}
	return (1 << dir);
}
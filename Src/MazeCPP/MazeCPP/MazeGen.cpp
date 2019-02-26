#include "MazeGen.h"

using namespace std;

MazeGen::MazeGen(int w, int h, uint32_t seed) {
	pVisited = new NodeTracker(w, h, seed);
	width = w;
	height = h;
	wall.resize(width, vector<bool>(height, true));
}

MazeGen::~MazeGen() {
	delete pVisited;
}

bool MazeGen::IsWall(int x, int y) {
	return wall[x][y];
}

void MazeGen::GenerateMaze() {
	vector<pair<int, int>> nodeStack;
	for (int currX = 0; currX < width; currX += 2) {
		for (int currY = 0; currY < height; currY += 2) {
			if (pVisited->IsVisited(currX, currY)) continue;
			pVisited->SetVisited(currX, currY);
			wall[currX][currY] = false;
			//we are at an unvisited node, and have an empty stack here
			//maze algorithm
			//1. pick unvisited neighbor (if none, pop current)
			//2. add current to stack
			//3. remove wall between current and pick
			//4. make pick current, mark visited
			int x = currX;
			int y = currY;
			while (x != -1) {
				unsigned char unvisited = pVisited->GetUnvisitedNeighbor(x, y);
				if (unvisited == 0) {
					if (nodeStack.size() == 0) {
						break;
					} else {
						pair<int, int> p = nodeStack.back();
						nodeStack.pop_back();
						x = p.first;
						y = p.second;
						continue;
					}
				} else {
					nodeStack.push_back(pair<int, int>(x, y));
					if (unvisited == 1) {
						//left
						wall[x - 1][y] = false;
						x -= 2;
					} else if (unvisited == 2) {
						//up
						wall[x][y - 1] = false;
						y -= 2;
					} else if (unvisited == 4) {
						//right
						wall[x + 1][y] = false;
						x += 2;
					} else {
						//down
						wall[x][y + 1] = false;
						y += 2;
					}
					pVisited->SetVisited(x, y);
					wall[x][y] = false;
				}
			}
		}
	}
}
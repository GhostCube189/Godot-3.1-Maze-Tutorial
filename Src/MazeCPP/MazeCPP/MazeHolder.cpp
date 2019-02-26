#include "MazeHolder.h"

using namespace godot;

void MazeHolder::_register_methods() {
	register_method((char*)"_ready", &MazeHolder::_ready);
}

void MazeHolder::_init() {}

MazeHolder::MazeHolder() {
	ResourceLoader *rl = ResourceLoader::get_singleton();
	wallScene = rl->load("res://Wall.tscn");
}

MazeHolder::~MazeHolder() {
	delete pMaze; pMaze = nullptr;
	if (mazeNodes) {
		for (int x = 0; x < mazeWidth; x++) {
			delete mazeNodes[x];
		}
		delete mazeNodes; mazeNodes = nullptr;
	}
}

void MazeHolder::_ready() {
	mazeWidth = (int)Root::mazeDimensions.x - 2;
	mazeHeight = (int)Root::mazeDimensions.y - 2;
	pMaze = new MazeGen(mazeWidth, mazeHeight, 1);//seed 1 for debug
	pMaze->GenerateMaze();
	mazeNodes = new Node2D**[mazeWidth];
	for (int x = 0; x < mazeWidth; x++) {
		mazeNodes[x] = new Node2D*[mazeHeight];
	}

	AddWallsToMaze();
}

void MazeHolder::AddWallsToMaze() {
	for (int x = 0; x < mazeWidth; x++) {
		for (int y = 0; y < mazeHeight; y++) {
			if (pMaze->IsWall(x, y)) {
				char name[256];
				sprintf_s(name, 256, "Wall%d_%d", x, y);
				Node2D* n = mazeNodes[x][y] = (Node2D*)wallScene->instance();
				n->set_name(name);
				n->set_position(Vector2(x * 128.f, y * 128.f));
				add_child(n);
			}
		}
	}
}
#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Resource.hpp>
#include <ResourceLoader.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include "Root.h"
#include "MazeGen.h"

namespace godot {
	class MazeHolder : public Node2D {
		GODOT_CLASS(MazeHolder, Node2D)
	private:
		MazeGen* pMaze;
		Node2D*** mazeNodes;
		godot::Ref<PackedScene> wallScene;
		int mazeWidth, mazeHeight;
	public:
		static void _register_methods();
		void _ready();
		void _init();

		MazeHolder();
		~MazeHolder();

		void AddWallsToMaze();
	};
}
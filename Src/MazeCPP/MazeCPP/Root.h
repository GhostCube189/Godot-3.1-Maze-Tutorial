#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseButton.hpp>
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
#include <GlobalConstants.hpp>

//Debug includes
#ifdef _DEBUG
#include <stdio.h>
#endif

#include "Player.h"

namespace godot {
	class Player;
	class Root : public Node2D {
		GODOT_CLASS(Root, Node2D)
	public:
		static Player* pPlayer;
		static Node2D* pInnerWallContainerNode;
		static Vector2 mazeDimensions;

		Node2D* pExit;
		Node2D* pOuterWalls;

		static void _register_methods();
		void _init();
		void _ready();

		Root();
		~Root();

		void HandleInputEvent(InputEvent* e);
		void ProcessMWheel(InputEventMouseButton* e);

		void SetMazeDimensions(Vector2 v);
		Vector2 GetMazeDimensions();
	};
}
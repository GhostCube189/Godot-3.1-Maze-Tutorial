#pragma once

#include "Root.h"

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <Camera2D.hpp>

namespace godot {
	class Player : public KinematicBody2D {
		GODOT_CLASS(Player, KinematicBody2D)
	private:
		Vector2 motion;
	public:
		Camera2D* pCamera;
		const int SPEED = 300;
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		Player();
		~Player();

		void UpdateMotionFromInput();
	};
}
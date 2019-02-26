#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <TextureRect.hpp>
#include "Root.h"

namespace godot {
	class Exit : public Node2D {
		GODOT_CLASS(Exit, Node2D)
	public:
		Exit();
		~Exit();
		static void _register_methods();
		void _init();
		void _on_Area2D_body_entered(Variant body);
	};
}
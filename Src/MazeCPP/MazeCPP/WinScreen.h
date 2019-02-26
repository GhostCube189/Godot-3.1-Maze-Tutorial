#pragma once

#include <core/Godot.hpp>
#include <TextureRect.hpp>
#include <SceneTree.hpp>
#include <Tree.hpp>
#include "Root.h"

namespace godot {
	class WinScreen : public TextureRect {
		GODOT_CLASS(WinScreen, TextureRect)
	public:
		WinScreen();
		~WinScreen();

		static void _register_methods();
		void _init();

		void _on_RestartButton_pressed(Variant body);
		void _on_QuitButton_pressed(Variant body);
	};
}
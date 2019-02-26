#include "WinScreen.h"

using namespace godot;

void WinScreen::_register_methods() {
	register_method((char*)"_on_RestartButton_pressed", &WinScreen::_on_RestartButton_pressed);
	register_method((char*)"_on_QuitButton_pressed", &WinScreen::_on_QuitButton_pressed);
}

WinScreen::WinScreen() {}
WinScreen::~WinScreen() {}
void WinScreen::_init() {}

void WinScreen::_on_QuitButton_pressed(Variant) {
	SceneTree* t = get_tree();
	t->quit();
}

void WinScreen::_on_RestartButton_pressed(Variant) {
	SceneTree* t = get_tree();
	t->reload_current_scene();
}
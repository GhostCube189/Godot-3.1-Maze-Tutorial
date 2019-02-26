#include "Exit.h"

using namespace godot;

void Exit::_register_methods() {
	register_method((char*)"_on_Area2D_body_entered", &Exit::_on_Area2D_body_entered);
}

void Exit::_init() {}
void Exit::_on_Area2D_body_entered(Variant) {
	TextureRect* t = (TextureRect*)Root::pCanvas->get_child(0);
	t->set_visible(true);
}

Exit::Exit() {}
Exit::~Exit() {}
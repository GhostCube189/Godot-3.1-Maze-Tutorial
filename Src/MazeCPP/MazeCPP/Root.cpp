#include "Root.h"

using namespace godot;

Player* Root::pPlayer;

void Root::_register_methods() {
	register_method((char*)"_input", &Root::HandleInputEvent);
}

void Root::_init() {}
Root::Root() {}
Root::~Root() {}

void Root::HandleInputEvent(InputEvent* e) {
	const godot::String gsIEMB = "InputEventMouseButton";
	godot::String gsClass = e->get_class();
	if (gsClass == gsIEMB) {
		ProcessMWheel((InputEventMouseButton*)e);
	}
	const godot::String gsIEK = "InputEventKey";
	if (gsClass == gsIEK) {
		InputEventKey* k = (InputEventKey*)e;
		if (k->get_scancode() == GlobalConstants::KEY_ESCAPE) {
			get_tree()->quit();
		}
	}
}

void Root::ProcessMWheel(InputEventMouseButton* e) {
	int64_t buttonIndex = e->get_button_index();
	if (e->is_pressed()) {
		if (buttonIndex == GlobalConstants::BUTTON_WHEEL_DOWN) {
			Vector2 v = pPlayer->pCamera->get_zoom();
			v.x = v.y = (v.x * 10.0f / 9.0f);
			if (v.x > 1.25) {
				v.x = v.y = 1.25;
			}
			pPlayer->pCamera->set_zoom(v);
		} else if (buttonIndex == GlobalConstants::BUTTON_WHEEL_UP) {
			Vector2 v = pPlayer->pCamera->get_zoom();
			v.x = v.y = (v.x * 0.9f);
			pPlayer->pCamera->set_zoom(v);
		}
	}
}
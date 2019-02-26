#include "Root.h"

using namespace godot;

Player* Root::pPlayer;
Node2D* Root::pInnerWallContainerNode;
Vector2 Root::mazeDimensions = Vector2(11, 7);
CanvasItem* Root::pCanvas;

void Root::_register_methods() {
	register_method((char*)"_input", &Root::HandleInputEvent);
	register_method((char*)"_ready", &Root::_ready);
	register_property<Root, Vector2>((char*)"MazeDimensions", &Root::SetMazeDimensions, &Root::GetMazeDimensions, mazeDimensions);
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

Vector2 Root::GetMazeDimensions() {
	return mazeDimensions;
}

void Root::SetMazeDimensions(Vector2 v) {
	if (fmod(v.x, 2) < 0.001) v.x--;
	if (fmod(v.y, 2) < 0.001) v.y--;
	mazeDimensions = v;
}

void Root::_ready() {
	const godot::String gsExit = "Exit";
	const godot::String gsOuterWalls = "OuterWalls";
	const godot::String gsCanvas = "CanvasLayer";
	Node* n;
	godot::String gsName;
	godot::Array a = get_children();
	int64_t childCount = get_child_count();
	for (int64_t x = 0; x < childCount; x++) {
		n = get_child(x);
		gsName = n->get_name();
		if (gsExit == gsName) {
			pExit = (Node2D*)n;
		} else if (gsOuterWalls == gsName) {
			pOuterWalls = (Node2D*)n;
		} else if (gsCanvas == gsName) {
			pCanvas = (CanvasItem*)n;
		}
	}

	pExit->set_position(Vector2(128 * (mazeDimensions.x - 3), 128 * (mazeDimensions.y - 3)));

	const godot::String gsNorth = "NorthWall";
	const godot::String gsSouth = "SouthWall";
	const godot::String gsEast = "EastWall";
	const godot::String gsWest = "WestWall";
	a = pOuterWalls->get_children();
	childCount = pOuterWalls->get_child_count();
	for (int64_t x = 0; x < childCount; x++) {
		n = pOuterWalls->get_child(x);
		gsName = n->get_name();
		if (gsNorth == gsName) {
			Node2D* wall = (Node2D*)n;
			wall->set_scale(Vector2(mazeDimensions.x, 1));
		} else if (gsSouth == gsName) {
			Node2D* wall = (Node2D*)n;
			wall->set_scale(Vector2(mazeDimensions.x, 1));
			wall->set_position(Vector2(-128, 128 * (mazeDimensions.y - 2)));
		} else if (gsEast == gsName) {
			Node2D* wall = (Node2D*)n;
			wall->set_scale(Vector2(1, mazeDimensions.y));
			wall->set_position(Vector2(128 * (mazeDimensions.x - 2), -128));
		} else if (gsWest == gsName) {
			Node2D* wall = (Node2D*)n;
			wall->set_scale(Vector2(1, mazeDimensions.y));
		}
	}
}
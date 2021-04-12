#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <tuple>

int CreateDisplay() {
	bool end = false;

	int mouseX = 0;
	int mouseY = 0;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_BITMAP* image = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	if (!al_init()) {
		return -1;
	}
	if (!al_init_image_addon()) {
		return -1;
	}
	if (!al_install_mouse()) {
		return -1;
	}
	if (!al_install_keyboard()) {
		return -1;
	}

	event_queue = al_create_event_queue();

	display = al_create_display(1280, 720);

	//Registers all event sources
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	if (!display) {
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255));

	int yPos = 100;

	UpdateButton update(340, yPos, 600, 100, "UpdateButtonUnclicked.png", "UpdateButtonClicked.png", 600, 100);
	yPos = yPos + 100;

	std::tuple<UpdateButton> allButtons = { update };

	while (!end) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;

			bool found = false;
			int count = 0;

			if (update.IfHit(mouseX, mouseY)) {
				update.WhenHit();
			}

		}
	}

}

int UpdateScreen() {


	return -1;
}
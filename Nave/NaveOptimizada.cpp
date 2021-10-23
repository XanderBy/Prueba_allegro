

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

int algo2() {
	//En esta clase haremos lo mismo que en la de Nave.cpp pero más optimizado y controlando posibles errores.

	//inicializamos allegro
	if (!al_init()) {
		printf("Error al inicializar Allegro");
		return 1;
	}
	//Inicializamos la entrada por teclado
	if (!al_install_keyboard()) {
		printf("Error al inicializar el teclado");
		return 1;
	}
	//creamos el temporizador
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	if (!timer) {
		printf("Error al crear el timer de FPS");
		return 1;
	}

	//creamos la cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	if (!queue) {
		printf("Error al crear la cola de eventos");
		return 1;
	}

	//inicializamos la pantalla
	ALLEGRO_DISPLAY* disp = al_create_display(640,480);
	if (!disp) {
		printf("Error al crear la pantalla");
		return 1;
	}

	//inicializar la fuente que vamos a usar
	ALLEGRO_FONT* font = al_create_builtin_font();
	if (!font) {
		printf("Error al inicializar la fuente");
		return 1;
	}
	

	//registramos los eventos de teclado y pantalla ademas de registrar los fps a los que irá el juego
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event; //creamos una variable para registrar el evento

	al_start_timer(timer);//inicializamos el timer para los FPS
	while (1) {

		al_wait_for_event(queue,&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// game logic goes here.
			redraw = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		default:
			break;
		}

		if (done) {
			break;
		}
		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
			al_flip_display();

			redraw = false;
		}

	}
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}
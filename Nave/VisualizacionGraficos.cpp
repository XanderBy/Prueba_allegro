#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>



int main() {

	//incluimos la inicialización de allegro
	al_init();

	//inicializamos la posible entrada de teclado
	al_install_keyboard();

	//inicializamos el timer
	ALLEGRO_TIMER* timer = al_create_timer(1 / 30);

	//inicializamos la cola de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	//inicializamos la ventana
	ALLEGRO_DISPLAY* disp = al_create_display(640, 480);

	//inicializamos la fuente
	ALLEGRO_FONT* font = al_create_builtin_font();

	//inicializamos la posibilidad de cargar imagenes
	al_init_image_addon();

	//cargo la imagen
	ALLEGRO_BITMAP* mysha = al_load_bitmap("mysha.png");

	//incluimos los eventos a la cola 
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(disp));


	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	//iniciamos el bucle del programa
	while (1) {

		al_wait_for_event(queue,&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		default:
			break;
		}

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

			al_draw_bitmap(mysha, 100, 100, 0);

			al_flip_display();

			redraw = false;
		}

	}

	//destruimos todo lo creado en memoria
	al_destroy_bitmap(mysha);

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
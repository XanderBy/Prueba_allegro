// Nave.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


int algo()
{
    al_init(); //inicializar componentes
    al_install_keyboard(); //habilita la entrada por teclado

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);//pone 1/30 para que en un segundo haya 30 fotogramas
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    //necesitamos las dos variables de arriba para que se ejecute el programa a una velocidad constante
    //habilitando un temporizador y una cola de eventos

    ALLEGRO_DISPLAY* disp = al_create_display(320, 200); //crea una ventana con este tamaño
    ALLEGRO_FONT* font = al_create_builtin_font(); //usa la fuente por defecto

    al_register_event_source(queue, al_get_keyboard_event_source()); //queremos "guardar" las acciones del teclado
    al_register_event_source(queue, al_get_display_event_source(disp)); //queremos que se muestre eventos
    al_register_event_source(queue, al_get_timer_event_source(timer));//con esto marcamos el temporizador del programa


    bool redraw = true;
    ALLEGRO_EVENT event; //creamos la variable para registrar los eventos

    al_start_timer(timer); //iniciamos el temporizador


    //bucle principal del programa: Acepte la entrada del jugador (si se da). Avance la lógica del juego. Renderiza los gráficos.
    while (1)
    {
        al_wait_for_event(queue, &event); //espera el programa hasta que se registra alguna accion antes registrada (teclado o pantalla)

        if (event.type == ALLEGRO_EVENT_TIMER) // 30 veces en un segundo para por aqui 
            redraw = true;
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) 
            //Si le ha dado boton abajo o ha clicado en la pantalla entraría rompiendo el bucle
            break;

        if (redraw && al_is_event_queue_empty(queue)) 
        {
            //esto quiere decir si es hora de pintar y ademas no tenemos ninguna accion pendiente vuelve a re dibujar todo
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_flip_display();

            redraw = false;
        }
    }
    //si el programa se termina limpiamos  todas las variables
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln

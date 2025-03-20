#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define WIDTH 600
#define HEIGHT 400
#define MOVE_STEP 5

int main(void) {
    // Déclarations
    ALLEGRO_DISPLAY* window = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;

    bool end = false;
    int x = WIDTH / 2, y = HEIGHT / 2; // Position de départ

    // Variables pour le mouvement continu
    bool up = false, down = false, left = false, right = false;

    // Initialisations
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_install_mouse());

    assert(al_init_primitives_addon());

    window = al_create_display(WIDTH, HEIGHT);
    assert(window);
    al_set_window_title(window, "Allegro 5");

    fifo = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); // 60 FPS

    al_register_event_source(fifo, al_get_display_event_source(window));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_mouse_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Boucle du jeu
    while (!end) {
        al_wait_for_event(fifo, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                end = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_Z: up = true; break;
                    case ALLEGRO_KEY_S: down = true; break;
                    case ALLEGRO_KEY_Q: left = true; break;
                    case ALLEGRO_KEY_D: right = true; break;
                    case ALLEGRO_KEY_ESCAPE: end = true; break;
                }
                break;

            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_Z: up = false; break;
                    case ALLEGRO_KEY_S: down = false; break;
                    case ALLEGRO_KEY_Q: left = false; break;
                    case ALLEGRO_KEY_D: right = false; break;
                }
                break;

            case ALLEGRO_EVENT_TIMER:
                if (up) y -= MOVE_STEP;
                if (down) y += MOVE_STEP;
                if (left) x -= MOVE_STEP;
                if (right) x += MOVE_STEP;

                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(0, 255, 0));
                al_flip_display();
                break;
        }
    }

    // Libération de la mémoire
    al_destroy_display(window);
    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);

    return 0;
}
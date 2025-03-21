#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define MOVE_STEP 5
#define PLAYER_SIZE 50

int main(void) {
    // Déclarations
    ALLEGRO_DISPLAY* window = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;

    bool end = false;
    int screen_width = 0, screen_height = 0;
    int x, y;

    // Mouvement
    bool up = false, down = false, left = false, right = false;

    // Initialisations
    assert(al_init());
    assert(al_install_keyboard());
    al_init_primitives_addon();

    window = al_create_display(1, 1);
    assert(window);
    al_set_window_title(window, "Allegro 5");

    // Plein écran
    al_set_display_flag(window, ALLEGRO_FULLSCREEN_WINDOW, true);
    screen_width = al_get_display_width(window);
    screen_height = al_get_display_height(window);

    // Position initiale au centre
    x = screen_width / 2;
    y = screen_height / 2;

    fifo = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(fifo, al_get_display_event_source(window));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Boucle principale
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

                // Affichage
                al_clear_to_color(al_map_rgb(255, 255, 255));

                al_draw_rectangle(0, 0, screen_width, screen_height, al_map_rgb(0, 0, 0), 5);
                al_draw_filled_rectangle(x - PLAYER_SIZE / 2, y - PLAYER_SIZE / 2, x + PLAYER_SIZE / 2, y + PLAYER_SIZE / 2, al_map_rgb(0, 0, 255));

                al_flip_display();
                break;
        }
    }

    // Libération mémoire
    al_destroy_display(window);
    al_destroy_event_queue(fifo);
    al_destroy_timer(timer);

    return 0;
}

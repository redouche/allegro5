#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define WIDTH 600
#define HEIGHT 400
#define MOVE_STEP 10

int main(void) {
    // Déclarations
    ALLEGRO_DISPLAY* window = NULL;
    ALLEGRO_EVENT_QUEUE* fifo = NULL;
    ALLEGRO_EVENT event;
    al_init_primitives_addon();
    bool end = false;
    int x = WIDTH / 2, y = HEIGHT / 2; // Position de départ

    // Initialisations
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_install_mouse());

    // Création des éléments nécessaires
    window = al_create_display(WIDTH, HEIGHT);
    assert(window);
    al_set_window_title(window, "Allegro 5");

    fifo = al_create_event_queue();
    al_register_event_source(fifo, al_get_display_event_source(window));
    al_register_event_source(fifo, al_get_keyboard_event_source());
    al_register_event_source(fifo, al_get_mouse_event_source());

    // Première mise à jour de l'écran
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Fond blanc
    al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(0, 255, 0)); // Tête verte au départ
    al_flip_display();

    // Boucle du jeu
    while (!end) {
        al_wait_for_event(fifo, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                printf("Fermeture de la fenetre.\n");
            end = true;
            break;

            case ALLEGRO_EVENT_KEY_DOWN:
                al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(0, 0, 255));

            // Mise à jour de la position
            if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
                y -= MOVE_STEP;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
                x -= MOVE_STEP;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                y += MOVE_STEP;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                x += MOVE_STEP;
            }

            al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(0, 255, 0));

            al_flip_display();
            break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                printf("Event : %d\n", event.mouse.button);
                    al_draw_filled_circle(event.mouse.x, event.mouse.y, 5, al_map_rgb(255, 0, 0));
                    al_flip_display();

                break;
            default:
                break;
        }
    }

    // Libération de la mémoire
    al_destroy_display(window);
    al_destroy_event_queue(fifo);

    return 0;
}

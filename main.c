#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define WIDTH 600
#define HEIGHT 400

int main(void) {
    // Déclarations

    // Initialisations
    assert(al_init());
    ALLEGRO_DISPLAY *ecran = al_create_display(WIDTH, HEIGHT);
    assert(ecran);
    al_set_window_title(ecran, "Titre");

    // Créations
    al_init_primitives_addon();
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Fond blanc
    // Je dessine un R
    al_draw_line(50, 50, 50, 350, al_map_rgb(0, 0, 0), 10.0);
    al_draw_line(50, 50, 150, 50, al_map_rgb(0, 0, 0), 10.0);
    al_draw_line(150, 50, 150, 200, al_map_rgb(0, 0, 0), 10.0);
    al_draw_line(150, 200, 50, 200, al_map_rgb(0, 0, 0), 10.0);
    al_draw_line(50, 200, 150, 350, al_map_rgb(0, 0, 0), 10.0);
    al_flip_display();

    // Fonctionnalités
    al_rest(5);

    // Libérations
    al_destroy_display(ecran);

    return 0;
}

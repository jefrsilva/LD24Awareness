#include "Fadeout.h"
#include "Environment.h"
#include <allegro5/allegro_primitives.h>

Fadeout::Fadeout(ALLEGRO_COLOR color, double duration) {
    this->color = color;
    totalDuration = duration;
    curDuration = 0.0;
}

Fadeout::~Fadeout() {
    
}

void Fadeout::update(double dt) {
    curDuration += dt;
    if (curDuration > totalDuration) {
        curDuration = totalDuration;
    }
}

void Fadeout::render(double edt) {
    double duration = curDuration + edt;
    if (duration > totalDuration) {
        duration = totalDuration;
    }
    
    double t = duration / totalDuration;
    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    ALLEGRO_COLOR fillColor = al_map_rgba(r, g, b, (unsigned char) (t * 255.0));
    al_draw_filled_rectangle(0, 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT, fillColor);
}

bool Fadeout::isFinished() {
    return curDuration == totalDuration;
}

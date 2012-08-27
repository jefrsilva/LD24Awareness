#include "Fadein.h"
#include "Environment.h"
#include <allegro5/allegro_primitives.h>

Fadein::Fadein(ALLEGRO_COLOR color, double duration) {
    this->color = color;
    totalDuration = duration;
    curDuration = 0.0;
}

Fadein::~Fadein() {
    
}

void Fadein::update(double dt) {
    curDuration += dt;
    if (curDuration > totalDuration) {
        curDuration = totalDuration;
    }
}

void Fadein::render(double edt) {
    double duration = curDuration + edt;
    if (duration > totalDuration) {
        duration = totalDuration;
    }
    
    double t = (1.0 - (duration / totalDuration)) * 255.0;
    unsigned char a = (unsigned char) t;
    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    ALLEGRO_COLOR fillColor = al_map_rgba(r, g, b, a);
    al_draw_filled_rectangle(0, 0, Environment::SCREEN_WIDTH, Environment::SCREEN_HEIGHT, fillColor);
}

bool Fadein::isFinished() {
    return curDuration == totalDuration;
}


#include "Wall.h"
#include "Environment.h"

ALLEGRO_BITMAP *Wall::wallShapes = 0;

Wall::Wall() : Object(OBJ_TYPE_WALL) {
    speed = 0.0;
}

Wall::~Wall() {
    
}

void Wall::handleStimulus(Environment *environment, double dt) {
    
}

void Wall::renderFeedback(Environment *environment) {
    
}

void Wall::render(Environment *environment) {
    if (!wallShapes) {
        wallShapes = al_load_bitmap("walls.png");
    }
    
    ALLEGRO_COLOR color = al_map_rgb(128, 128, 128);
    Vector2D objWindowPos = environment->getWindowPos(getPosition());
    al_draw_tinted_scaled_bitmap(wallShapes, color, 0, 0, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
}

#include "Food.h"
#include "Environment.h"
#include "RandomNumberGenerator.h"

#include <cmath>

ALLEGRO_BITMAP *Food::foodShapes = 0;
std::map<std::string, int> Food::foodShapeIndexes;

Food::Food(double amount) : Object(OBJ_TYPE_FOOD) {
    this->amount = amount;
    speed = 0.0;
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    fruitShape = rng->getInt(0, 7);
    
    int compType = rng->getInt(0, 2);
    if (compType == 0) {
        this->composition = "A";        
    }
    if (compType == 1) {
        this->composition = "B";        
    }
    if (compType == 2) {
        this->composition = "C";        
    }
}

Food::Food(std::string composition, double amount) : Object(OBJ_TYPE_FOOD) {
    this->composition = composition;
    this->amount = amount;
    speed = 0.0;
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    fruitShape = rng->getInt(0, 7);
}

Food::~Food() {
    
}

void Food::handleStimulus(Environment *environment, double dt) {
    
}

void Food::renderFeedback(Environment *environment) {
    
}

std::string Food::getComposition() {
    return composition;
}

double Food::digest(double amountToDigest) {
    amountToDigest = std::min(amount, amountToDigest);
    amount -= amountToDigest;
    return amountToDigest;
}

double Food::getAmount() {
    return amount;
}

void Food::render(Environment *environment) {
    if (!foodShapes) {
        foodShapes = al_load_bitmap("foodShapes.png");
        
        std::vector<int> indexes;
        for (int i = 0; i < 8; i++) {
            indexes.push_back(i);
        }
        std::random_shuffle(indexes.begin(), indexes.end());
        
        foodShapeIndexes.insert(std::make_pair("A", 0));
        foodShapeIndexes.insert(std::make_pair("B", 1));
        foodShapeIndexes.insert(std::make_pair("C", 2));        
        foodShapeIndexes.insert(std::make_pair("AB", 3));
        foodShapeIndexes.insert(std::make_pair("AC", 4));
        foodShapeIndexes.insert(std::make_pair("BC", 5));        
    }
    
    if (composition[0] == '1' ||
        composition[0] == '2' ||
        composition[0] == '3' ||
        composition[0] == '4') {
        int prizeShape = composition[0] - '1';
        ALLEGRO_COLOR color = al_map_rgb(255, 255, 128);
        Vector2D objWindowPos = environment->getWindowPos(getPosition());
        al_draw_tinted_scaled_bitmap(foodShapes, color, 48, prizeShape * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
    } else {
        int trunkShape = foodShapeIndexes[composition];
        int r = 0;
        int g = 0;
        int b = 0;
        for (int i = 0; i < composition.size(); i++) {
            if (composition[i] == 'A') {
                r+=255;
            } else if (composition[i] == 'B') {
                g+=255;
            }  else if (composition[i] == 'C') {
                b+=255;
            }
        }
        
        ALLEGRO_COLOR color = al_map_rgb(r, g, b);
        Vector2D objWindowPos = environment->getWindowPos(getPosition());
        al_draw_tinted_scaled_bitmap(foodShapes, color, 24, fruitShape * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
        al_draw_tinted_scaled_bitmap(foodShapes, color, 0, trunkShape * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);
    }
}

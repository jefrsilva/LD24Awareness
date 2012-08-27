#include "Engine.h"
#include "TitleScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "GameCompleteScreen.h"

using namespace Game;
 
int main(int argc, char **argv){
    Engine *engine = new Engine();
    Screen *titleScreen = new TitleScreen();
    Screen *gameScreen = new GameScreen();
    Screen *gameOverScreen = new GameOverScreen();
    Screen *gameCompleteScreen = new GameCompleteScreen();

    engine->addScreen(0, titleScreen);
    engine->addScreen(1, gameScreen);
    engine->addScreen(2, gameOverScreen);
    engine->addScreen(3, gameCompleteScreen);
    engine->run();

    return 0;
}

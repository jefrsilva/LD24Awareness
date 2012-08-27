#ifndef _ENGINE_
#define _ENGINE_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

namespace Game {

    class Screen;  

    class Engine {
          public:
              static const double FPS = 60.0; // Frame per second
			  static const double UPS = 60.0; // Update per second
			  
              static const int SCREEN_WIDTH = 720;
              static const int SCREEN_HEIGHT = 720;

			  static const int SCREEN_SIZE = 30;
              Screen *screen[SCREEN_SIZE];
              int currentScreen;

              double delta_time;
              double draw_old_time;
              double update_old_time;

              bool endGame;
			  
              ALLEGRO_THREAD *thread_update;
              ALLEGRO_MUTEX *mutex;
			  
              ALLEGRO_DISPLAY *display;
              ALLEGRO_EVENT_QUEUE *event_queue;
              ALLEGRO_TIMER *timerUpdate;

              Engine();
              ~Engine();

              void run();
              void loop();
              
              void addScreen(int index, Screen * screen);
              void jumpScreen(int index);
                 
              static void *updateThread(ALLEGRO_THREAD *thr, void *arg);
    };

}


#endif

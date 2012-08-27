#ifndef _DNA_H
#define _DNA_H

#include "Sensor.h"
#include <vector>
#include <map>
#include <string>
#include <allegro5/allegro.h>

const char DNA_BASES[] = {'A', 'B', 'C', 'D'};

class DNA {
    private:
        static const int blindnessQty = 0;
        static const int singleAntennaQty = 10;
        static const int doubleAntennaQty = 10;
        static const int tripleAntennaQty = 10;
        static const int multiSingleAntennaQty = 8;
        static const int multiTripleAntennaQty = 8;
        static const int primitiveEyesQty = 10;
        static const int eyesQty = 8;
        
        static const int digestiveAQty = 16;
        static const int digestiveBQty = 16;
        static const int digestiveCQty = 16;
        static const int digestiveABQty = 4;
        static const int digestiveACQty = 4;
        static const int digestiveBCQty = 4;
        static const int digestiveABCQty = 4;
        
        static const int deafnessQty = 8;
        static const int primitiveEarQty = 14;
        static const int distanceEarQty = 14;
        static const int directionalEarQty = 14;
        static const int multiDirectionalEarQty = 14;        
        
        static const int redColorQty = 16;
        static const int greenColorQty = 16;
        static const int blueColorQty = 16;
        static const int yellowColorQty = 16;
        
        static const int noNervousSystemQty = 0;
        static const int basicNervousSystemQty = 4;
        static const int nervousSystemQty = 36;
        static const int advancedNervousSystemQty = 24;
        
        std::string sequence;
        static std::vector<Sensor *> sightSensorTypes;
        static std::vector<Sensor *> digestiveTypes;        
        static std::vector<Sensor *> hearingSensorTypes;
        static std::vector<Sensor *> nervousSystemTypes;
        static std::vector<ALLEGRO_COLOR> colors;
        
        static std::map<std::string, int> shapeIndexes;
    
    public:
        DNA();
        DNA(std::string sequence);
        ~DNA();
        
        std::string getSequence();
        Sensor *getSightSensor();
        Sensor *getDigestiveSystem();
        Sensor *getHearingSensor();
        Sensor *getNervousSystem();
        std::string crossoverAndMutate(std::string secondSequence);
        int getVoice();
        
        int getAntennaEyesShape();
        int getHeadShape();
        int getEarsShape();
        int getBodyShape();
        ALLEGRO_COLOR getColor();
};

#endif

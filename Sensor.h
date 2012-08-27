#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>

class Object;
class Environment;

class Sensor {
    private:
        std::string id;
    
    public:
        Sensor(std::string id);
        virtual ~Sensor() {};
        
        std::string getId();
        
        virtual void handleStimulus(Object *object, Environment *environment, double dt) = 0;
        virtual void renderFeedback(Object *object, Environment *environment) = 0;
        virtual Sensor *clone() = 0;
};

#endif

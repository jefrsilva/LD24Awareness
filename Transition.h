#ifndef _TRANSITION_H
#define _TRANSITION_H

class Transition {
    public:
        virtual ~Transition() {};
        
        virtual void update(double dt) = 0;
        virtual void render(double edt) = 0;
        virtual bool isFinished() = 0;
};

#endif

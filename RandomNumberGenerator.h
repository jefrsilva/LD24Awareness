#ifndef _RANDOM_NUMBER_GENERATOR_H
#define _RANDOM_NUMBER_GENERATOR_H

class RandomNumberGenerator {
    private:
        RandomNumberGenerator();    
        ~RandomNumberGenerator();
        
    protected:
        static RandomNumberGenerator *instance;
        
    public:
        static RandomNumberGenerator *getInstance();
        int getInt(int min, int max);
};

#endif

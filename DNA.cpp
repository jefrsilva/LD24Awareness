#include "DNA.h"
#include "RandomNumberGenerator.h"
#include "Blindness.h"
#include "SingleAntenna.h"
#include "DoubleAntenna.h"
#include "TripleAntenna.h"
#include "MultiSingleAntenna.h"
#include "MultiTripleAntenna.h"
#include "PrimitiveEyes.h"
#include "Eyes.h"
#include "DigestiveSystem.h"
#include "Deafness.h"
#include "PrimitiveEar.h"
#include "DistanceEar.h"
#include "DirectionalEar.h"
#include "MultiDirectionalEar.h"
#include "NoNervousSystem.h"
#include "BasicNervousSystem.h"
#include "NervousSystem.h"
#include "AdvancedNervousSystem.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>

std::vector<Sensor *> DNA::sightSensorTypes;
std::vector<Sensor *> DNA::digestiveTypes;
std::vector<Sensor *> DNA::hearingSensorTypes;
std::vector<Sensor *> DNA::nervousSystemTypes;
std::vector<ALLEGRO_COLOR> DNA::colors;
std::map<std::string, int> DNA::shapeIndexes;

DNA::DNA() {
    sequence = "ssshhhcccdddnnn";

    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    for (int i = 0; i < sequence.size(); i++) {
        int randomBaseIndex = rng->getInt(0, 3);
        sequence[i] = DNA_BASES[randomBaseIndex];
    }    
}

DNA::DNA(std::string sequence) {
    this->sequence = sequence;
}

DNA::~DNA() {
    
}

std::string DNA::getSequence() {
    return sequence;
}

Sensor *DNA::getSightSensor() {
    if (sightSensorTypes.empty()) {
        std::vector<int> indexes;
        for (int i = 0; i < 16; i++) {
            indexes.push_back(i);
        }
        std::random_shuffle(indexes.begin(), indexes.end());
        
        Blindness *blindness = new Blindness();
        shapeIndexes.insert(std::make_pair(blindness->getId(), indexes[0]));
        SingleAntenna *singleAntenna = new SingleAntenna();
        shapeIndexes.insert(std::make_pair(singleAntenna->getId(), indexes[1]));
        DoubleAntenna *doubleAntenna = new DoubleAntenna();
        shapeIndexes.insert(std::make_pair(doubleAntenna->getId(), indexes[2]));
        TripleAntenna *tripleAntenna = new TripleAntenna();
        shapeIndexes.insert(std::make_pair(tripleAntenna->getId(), indexes[3]));
        MultiSingleAntenna *multiSingleAntenna = new MultiSingleAntenna();
        shapeIndexes.insert(std::make_pair(multiSingleAntenna->getId(), indexes[4]));
        MultiTripleAntenna *multiTripleAntenna = new MultiTripleAntenna();
        shapeIndexes.insert(std::make_pair(multiTripleAntenna->getId(), indexes[5]));
        PrimitiveEyes *primitiveEyes = new PrimitiveEyes();
        shapeIndexes.insert(std::make_pair(primitiveEyes->getId(), indexes[6]));
        Eyes *eyes = new Eyes();
        shapeIndexes.insert(std::make_pair(eyes->getId(), indexes[7]));
        
        for (int i = 0; i < blindnessQty; i++) {
            sightSensorTypes.push_back(blindness);
        }
        for (int i = 0; i < singleAntennaQty; i++) {
            sightSensorTypes.push_back(singleAntenna);
        }
        for (int i = 0; i < doubleAntennaQty; i++) {
            sightSensorTypes.push_back(doubleAntenna);
        }
        for (int i = 0; i < tripleAntennaQty; i++) {
            sightSensorTypes.push_back(tripleAntenna);
        }
        for (int i = 0; i < multiSingleAntennaQty; i++) {
            sightSensorTypes.push_back(multiSingleAntenna);
        }
        for (int i = 0; i < multiTripleAntennaQty; i++) {
            sightSensorTypes.push_back(multiTripleAntenna);
        }
        for (int i = 0; i < primitiveEyesQty; i++) {
            sightSensorTypes.push_back(primitiveEyes);
        }
        for (int i = 0; i < eyesQty; i++) {
            sightSensorTypes.push_back(eyes);
        }
        
        std::random_shuffle(sightSensorTypes.begin(), sightSensorTypes.end());
    }
    
    std::string sightSection = sequence.substr(0, 3);
    int index = 0;
    for (int i = 0; i < sightSection.size(); i++) {
        index += (sightSection[i] - 'A') * ((int) std::pow(4.0, (double) i));
    }
    //std::cout << "Sight index : " << index << std::endl;
    return sightSensorTypes[index]->clone();
}

Sensor *DNA::getDigestiveSystem() {
    if (digestiveTypes.empty()) {
        std::vector<int> indexes;
        for (int i = 0; i < 16; i++) {
            indexes.push_back(i);
        }
        std::random_shuffle(indexes.begin(), indexes.end());
        
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_A", 0));
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_B", 1));
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_C", 2));
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_AB", 3));
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_AC", 4));
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_BC", 5));                        
        shapeIndexes.insert(std::make_pair("SENSOR_DIGESTIVE_SYSTEM_ABC", 6));        
        
        for (int i = 0; i < digestiveAQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("A", 10.0));
        }
        for (int i = 0; i < digestiveBQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("B", 10.0));
        }
        for (int i = 0; i < digestiveCQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("C", 10.0));
        }
        for (int i = 0; i < digestiveABQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("AB", 8.0));
        }
        for (int i = 0; i < digestiveACQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("AC", 8.0));
        }
        for (int i = 0; i < digestiveBCQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("BC", 8.0));
        }
        for (int i = 0; i < digestiveABCQty; i++) {
            digestiveTypes.push_back(new DigestiveSystem("ABC", 5.0));
        }
        
        std::random_shuffle(digestiveTypes.begin(), digestiveTypes.end());
    }

    std::string digestiveSection = sequence.substr(9, 3);
    int index = 0;
    for (int i = 0; i < digestiveSection.size(); i++) {
        index += (digestiveSection[i] - 'A') * ((int) std::pow(4.0, (double) i));
    }
    //std::cout << "Digestive index : " << index << std::endl;
    return digestiveTypes[index]->clone();
}

Sensor *DNA::getHearingSensor() {
    if (hearingSensorTypes.empty()) {
        std::vector<int> indexes;
        for (int i = 0; i < 16; i++) {
            indexes.push_back(i);
        }
        std::random_shuffle(indexes.begin(), indexes.end());
        
        Deafness *deafness = new Deafness();
        shapeIndexes.insert(std::make_pair(deafness->getId(), indexes[0]));
        PrimitiveEar *primitiveEar = new PrimitiveEar();
        shapeIndexes.insert(std::make_pair(primitiveEar->getId(), indexes[1]));
        DistanceEar *distanceEar = new DistanceEar();
        shapeIndexes.insert(std::make_pair(distanceEar->getId(), indexes[2]));
        DirectionalEar *directionalEar = new DirectionalEar();
        shapeIndexes.insert(std::make_pair(directionalEar->getId(), indexes[3]));
        MultiDirectionalEar *multiDirectionalEar = new MultiDirectionalEar();
        shapeIndexes.insert(std::make_pair(multiDirectionalEar->getId(), indexes[4]));
        
        for (int i = 0; i < deafnessQty; i++) {
            hearingSensorTypes.push_back(deafness);
        }
        for (int i = 0; i < primitiveEarQty; i++) {
            hearingSensorTypes.push_back(primitiveEar);
        }
        for (int i = 0; i < distanceEarQty; i++) {
            hearingSensorTypes.push_back(distanceEar);
        }
        for (int i = 0; i < directionalEarQty; i++) {
            hearingSensorTypes.push_back(directionalEar);
        }
        for (int i = 0; i < multiDirectionalEarQty; i++) {
            hearingSensorTypes.push_back(multiDirectionalEar);
        }
        
        std::random_shuffle(hearingSensorTypes.begin(), hearingSensorTypes.end());
    }
    
    std::string hearingSection = sequence.substr(3, 3);
    int index = 0;
    for (int i = 0; i < hearingSection.size(); i++) {
        index += (hearingSection[i] - 'A') * ((int) std::pow(4.0, (double) i));
    }
    //std::cout << "Hearing index : " << index << std::endl;
    return hearingSensorTypes[index]->clone();
}

Sensor *DNA::getNervousSystem() {
    if (nervousSystemTypes.empty()) {
        std::vector<int> indexes;
        for (int i = 0; i < 16; i++) {
            indexes.push_back(i);
        }
        std::random_shuffle(indexes.begin(), indexes.end());
        
        NoNervousSystem *noNervousSystem = new NoNervousSystem();
        shapeIndexes.insert(std::make_pair(noNervousSystem->getId(), indexes[0]));
        BasicNervousSystem *basicNervousSystem = new BasicNervousSystem();
        shapeIndexes.insert(std::make_pair(basicNervousSystem->getId(), indexes[1]));
        NervousSystem *nervousSystem = new NervousSystem();
        shapeIndexes.insert(std::make_pair(nervousSystem->getId(), indexes[2]));
        AdvancedNervousSystem *advancedNervousSystem = new AdvancedNervousSystem();
        shapeIndexes.insert(std::make_pair(advancedNervousSystem->getId(), indexes[3]));
        
        for (int i = 0; i < noNervousSystemQty; i++) {
            nervousSystemTypes.push_back(noNervousSystem);
        }
        for (int i = 0; i < basicNervousSystemQty; i++) {
            nervousSystemTypes.push_back(basicNervousSystem);
        }
        for (int i = 0; i < nervousSystemQty; i++) {
            nervousSystemTypes.push_back(nervousSystem);
        }
        for (int i = 0; i < advancedNervousSystemQty; i++) {
            nervousSystemTypes.push_back(advancedNervousSystem);
        }
        std::random_shuffle(nervousSystemTypes.begin(), nervousSystemTypes.end());
    }
    
    std::string nervousSection = sequence.substr(12, 3);
    int index = 0;
    for (int i = 0; i < nervousSection.size(); i++) {
        index += (nervousSection[i] - 'A') * ((int) std::pow(4.0, (double) i));
    }
    //std::cout << "Nervous index : " << index << std::endl;
    return nervousSystemTypes[index]->clone();
}

std::string DNA::crossoverAndMutate(std::string secondSequence) {
    std::string firstSequence = sequence;
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    int crossOverLength = rng->getInt(3, 8);
    //std::cout << "crossOverLength : " << crossOverLength << std::endl;
    
    int firstSwapIndex = rng->getInt(0, sequence.size() - crossOverLength);
    //std::cout << "firstSwapIndex : " << firstSwapIndex << std::endl;    
    
    for (int i = firstSwapIndex; i < firstSwapIndex + crossOverLength; i++) {
        firstSequence[i] = secondSequence[i];
    }
    
    int mutationIndex = rng->getInt(0, sequence.size() - 1);
    //std::cout << "mutationIndex : " << mutationIndex << std::endl;    
    
    int mutatedBaseIndex = rng->getInt(0, 3);        
    firstSequence[mutationIndex] = DNA_BASES[mutatedBaseIndex];
    
    return firstSequence;
}

int DNA::getVoice() {
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    return rng->getInt(0, 15);
}

int DNA::getAntennaEyesShape() {
    return shapeIndexes[getSightSensor()->getId()];
}

int DNA::getHeadShape() {
    return shapeIndexes[getNervousSystem()->getId()];
}

int DNA::getBodyShape() {
    DigestiveSystem *digestiveSystem = (DigestiveSystem *) getDigestiveSystem();
    std::string digestibles = digestiveSystem->getDigestibles();
    std::string sensorId = "SENSOR_DIGESTIVE_SYSTEM_" + digestibles;
    return shapeIndexes[sensorId];
}

int DNA::getEarsShape() {
    return shapeIndexes[getHearingSensor()->getId()];
}

ALLEGRO_COLOR DNA::getColor() {
    if (colors.empty()) {
        for (int i = 0; i < redColorQty; i++) {
            colors.push_back(al_map_rgb(255, 0, 0));
        }
        for (int i = 0; i < greenColorQty; i++) {
            colors.push_back(al_map_rgb(0, 255, 0));
        }
        for (int i = 0; i < blueColorQty; i++) {
            colors.push_back(al_map_rgb(0, 0, 255));
        }
        for (int i = 0; i < yellowColorQty; i++) {
            colors.push_back(al_map_rgb(255, 255, 0));
        }
        
        std::random_shuffle(colors.begin(), colors.end());
    }
    
    std::string colorSection = sequence.substr(6, 3);
    int index = 0;
    for (int i = 0; i < colorSection.size(); i++) {
        index += (colorSection[i] - 'A') * ((int) std::pow(4.0, (double) i));
    }
    //std::cout << "Color index : " << index << std::endl;
    return colors[index];
}

#include "Sensor.h"

Sensor::Sensor(std::string id) {
    this->id = id;
}

std::string Sensor::getId() {
    return id;
}

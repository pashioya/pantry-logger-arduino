#include <Arduino.h>

#define brightPin 2 // Analog Pin sensor is connected to

int readBright() {
    return analogRead(brightPin);
}

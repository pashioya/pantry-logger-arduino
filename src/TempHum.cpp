#include <dht.h>

#define dht_apin A1 // Analog Pin sensor is connected to
 
dht DHT;

void readPin() {
    DHT.read11(dht_apin);
}

float readTemp() {
    readPin();
    return DHT.temperature;
}

float readHum() {
    readPin();
    return DHT.humidity;
}
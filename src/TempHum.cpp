#include <dht.h>

#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;

void readPin() {
    DHT.read11(dht_apin);
}

float readTemp() {
    return DHT.temperature;
}

float readHum() {
    return DHT.humidity;
}
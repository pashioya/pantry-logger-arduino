#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Util.h>
#include <TempHum.h>
#include <Brightness.h>

/*
 * ESP8266 wifi module Interfacing with Arduino Uno
 * http://www.electronicwings.com
 */ 
#include "ESP8266_AT.h"

/* Define Required fields shown below */
#define DOMAIN          "api.thingspeak.com"
#define PORT            "80"
#define API_WRITE_KEY   "PSR0RKR5AN754B1Z"
#define CHANNEL_ID      "1887657"

#define SSID            "DuckDuck"
#define PASSWORD        "w3rkW3rk"

char _buffer[150];
uint8_t Connect_Status;
uint8_t Sample = 0;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonLeft = 3;
const int buttonRight = 2;
int buttonStateLeft = 0;
int buttonStateRight = 0;

String lastHeader = "";
String Header = "Temperature";

int viewPosition = 0;
int lastViewPosition = -1;
String sensors[3] = { "Temperature", "Humidity", "Brightness" };


void leftButtonISR(){
    viewPosition--;
    if(viewPosition < 0) viewPosition = 2;
    Header = sensors[viewPosition];
}
void rightButtonISR(){
    viewPosition--;
    if(viewPosition < 0) viewPosition = 2;
    Header = sensors[viewPosition];
}

String currentText = "";
void setup() {
    //wifi setup
    Serial.begin(115200);
    while(!ESP8266_Begin());
    ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);	/* 3 = Both (AP and STA) */
    ESP8266_ConnectionMode(SINGLE);     			/* 0 = Single; 1 = Multi */
    ESP8266_ApplicationMode(NORMAL);    			/* 0 = Normal Mode; 1 = Transperant Mode */
    if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)/*Check WIFI connection*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    ESP8266_Start(0, DOMAIN, PORT);	

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("xxx");

    pinMode(buttonRight, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonRight), leftButtonISR, CHANGE);
    pinMode(buttonLeft, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonLeft), rightButtonISR, CHANGE);
}

void loop() {

    int tempReading = readTemp();
    int humReading = readHum();
    int brightReading = readBright();
    //write header
    if(lastHeader != Header) {
        lastHeader = Header;
        lcd.setCursor(0, 0);
        lcd.print(getCharLine(' '));
        lcd.setCursor(0, 0);
        lcd.print(lastHeader);
    }

    lcd.setCursor(5, 1);
    Connect_Status = ESP8266_connected();
    if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)	/*Again check connection to WIFI*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
    ESP8266_Start(0, DOMAIN, PORT);			/*Connect to TCP port*/

    memset(_buffer, 0, 150);
    memset(_buffer, 0, 150);
    sprintf(_buffer, "GET /update?api_key=%s&field1=%d&field2=%d&field3=%d", API_WRITE_KEY, tempReading,  humReading, brightReading); 	/*connect to thingspeak server to post data using your API_WRITE_KEY*/
    ESP8266_Send(_buffer);
    delay(5000); 					/* Thingspeak server delay */
    
    
    lcd.setCursor(0, 1);
    switch (viewPosition) {
        case 0:  
            lcd.print(numToString(tempReading, 4, ' '));
            break;
        case 1:  
            lcd.print(numToString(humReading, 4, ' '));
            break;
        case 2:  
            lcd.print(numToString(brightReading, 4, ' '));
            break;
        default:
            lcd.print("error");
            break;
    }
}



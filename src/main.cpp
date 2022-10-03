#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Util.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonLeft = 7;
const int buttonRight = 6;
int buttonStateLeft = 0;
int buttonStateRight = 0;

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("potentiometer");

    //pinMode(6, INPUT);
    //pinMode(7, INPUT);
}

void loop() {
    //int sensorValue = analogRead(A0);
    lcd.setCursor(0, 1);
    //lcd.print(numToString(sensorValue, 5, ' '));

    //buttonStateLeft = digitalRead(buttonLeft);
    //buttonStateRight = digitalRead(buttonRight);
    /*
    if (buttonStateLeft == HIGH && buttonStateRight != HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("button left");
    } else if(buttonStateLeft != HIGH && buttonStateRight == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("button right");
    }*/
}
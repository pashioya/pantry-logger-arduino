#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Util.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonLeft = 6;
const int buttonRight = 7;
int buttonStateLeft = 0;
int buttonStateRight = 0;

int oldPotentVal = -1;
int newPotentVal = -1;

const String buttonLeftText = "Temperature";
const String buttonRightText = "Humidity";

String currentText = "";
void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("xxx");

    pinMode(6, INPUT);
    pinMode(7, INPUT);
}

void loop() {
    int newPotentVal = analogRead(A0);
    if (newPotentVal != oldPotentVal) {
        oldPotentVal = newPotentVal;
        lcd.setCursor(6, 1);
        lcd.print(numToString(oldPotentVal, 4, ' '));
    }
    
    

    buttonStateLeft = digitalRead(buttonLeft);
    buttonStateRight = digitalRead(buttonRight);
    
    if (buttonStateLeft == HIGH && buttonStateRight != HIGH && currentText != buttonLeftText) {
        changeLine(lcd, 0, ' ');
        lcd.setCursor(0, 0);
        currentText = buttonLeftText;
        lcd.print(currentText);
    } else if(buttonStateLeft != HIGH && buttonStateRight == HIGH && currentText != buttonRightText) {
        changeLine(lcd, 0, ' ');
        lcd.setCursor(0, 0);
        currentText = buttonRightText;
        lcd.print(currentText);
    }
}
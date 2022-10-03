#include <Arduino.h>
#include <LiquidCrystal.h>
/*
    Converts a number to a string of the defined size and replaces the empty
    spots with the defined padChar
    (10, 5, 'x')  ->  "xxx10"
*/
String numToString(int number, int size, char padChar) {
    String s = String(number);
    int num_length = s.length();
    for (int i = num_length; i < size; i++) {
        s = padChar + s;
    }
    return s;
}



String getCharLine(char repeatChar) {
    String out = "";
    for(int i = 0; i < 16; i++) {
        out += repeatChar;
    }
    return out;
}

void changeLine(LiquidCrystal screenObj, int line, char repeatChar) {
    screenObj.setCursor(0, line);
    screenObj.print(getCharLine(repeatChar));
}
#include <Arduino.h>

String numToString(int number, int size, char padChar);

String getCharLine(char repeatChar);

void changeLine(LiquidCrystal screenObj, int line, char repeatChar);
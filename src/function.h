/*

*/

#ifndef function_h
#define function_h
#include <Arduino.h>
#include <OneWire.h>
#include <LiquidCrystal.h>
void lcdInit(void);
void lcdShoTemper(String s);
void sendSerial(String s);
float getTemper(void);

#endif

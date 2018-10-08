/*

*/

#ifndef function_h
#define function_h
#include <Arduino.h>

#include "OneWire/OneWire.h"
#include "LiquidCrystal/LiquidCrystal.h"

void lcdInit(void);                 // Настройка LCD
void lcdLoad(void);                 // отображения загрузки LCD
float getTemper(void);              // Запрос температуры с DS18b20
float fgetResistance(int d1, int d2, int a1, float delR, int cnt);      //Функция замера сопротивления в RAW
float fcalcResistance(long countData, long fullData, int var, float delR);  // Расчет сопротивления
float fECTemp(float k, float ec0, float t);  // Функция термокомпенсации ЕС
String lcdStrTemper(float temper);  // Формирования строки отображения температуры на LCD
String lcdStrTds(float temper);     // Формирования строки отображения TDS на LCD
void lcdShow(String s0, String s1); // Отправка данных первой строки LCD
void sendSerial(float t, float tds); // Отправка данных по UART

#endif

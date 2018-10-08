/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 */
 

 
 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // инициализируем LCD, указывая контакты данных
// задаем переменные
int Count = 0;                  // счетчик обновлений
int tempPin = 0;                // пин куда подключен датчик
float tempc = 0;                // переменная для температуры
float maxi = 0, mini = 30;      // max/min значения температуры

void setup() {
  // красивая "загрузка" программы при старте :)
  lcd.begin(16, 2);
  lcd.print("Loading");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(500);                // ждем 0.5 секунды
  lcd.print(".");
  delay(1000);               // ждем 1 секунду
  lcd.clear();               //очистка экрана
}

void loop() {
  lcd.clear();               //очистка экрана
  // считываем и вычисляем температуру
  tempc = ( 5.0 * analogRead(tempPin) * 100.0) / 1024.0;
  if(tempc > maxi) {
    maxi = tempc;
  } // max температура?

  if(tempc < mini) {
    mini = tempc;
  } // min температура?

  lcd.setCursor(0, 0);     // устанавливаем курсор в 0-ом
  // столбце, 1 строке (начинается с 0)
  lcd.print("t=");
  lcd.print(tempc);        // выводим текущую температуру
  lcd.setCursor(0, 1);     // устанавливаем курсор в 0-ом столбце, 2 строке
  lcd.print("t");        // обозначение минимальной температры
  lcd.print(mini);         // выводим min температуру
  lcd.print(" T");         // обозначение максимальной температуры
  lcd.print(maxi);         // выводим max температуру 
  delay(5*500);   // задержка перед повторением измерений
  Count++;         // инкремент счетчика измерений
}

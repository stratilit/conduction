/*
  LiquidCrystal Library

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver.

 This sketch prints conduction to the LCD
 and shows the time.

 The circuit:
  LCD       Arduin Nano
* RS        pin 2
* Enable    pin 3
* D4        pin 4
* D5        pin 5
* D6        pin 6
* D7        pin 7
* R/W       ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
 Последовательность в LiquidCrystal:
 RS, Enable, D4, D5, D6, D7

 
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // инициализируем LCD, указывая контакты данных
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

/*
  LiquidCrystal Library

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver.
 Arduin Nano.

 This sketch prints
 to the LCD
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
#include <Arduino.h>
#include <OneWire.h>
OneWire ds(8);
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // инициализируем LCD, указывая контакты данных
// переменные

int tempPin = 0;                // пин куда подключен датчик
float tempc = 0;                // переменная для температуры

void setup() {
  // красивая "загрузка" программы при старте :)
  lcd.begin(16, 2);
  lcd.print("Loading");
  for (int i=0; i <= 3; i++){
      delay(500);             // ждем 0.5 секунды
      lcd.print(".");
   }

  lcd.clear();               //очистка экрана
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  byte data[2];               // Место для значения температуры
  ds.reset();                 // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC);             // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство
  ds.write(0x44);             // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  delay(1000);                // Микросхема измеряет температуру, а мы ждем.
  ds.reset();                 // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC);
  ds.write(0xBE);             // Просим передать нам значение регистров со значением температуры
  data[0] = ds.read();        // Читаем младший байт значения температуры
  data[1] = ds.read();        // А теперь старший

  // Формируем итоговое значение:
    //    - сперва "склеиваем" значение,
    //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
  float temper =  ((data[1] << 8) | data[0]) * 0.0625;
  String temperC = String(temper, 1);

  // LCD
  String lcdMaseg = "t=";     // Формирования отображаемых данных
  lcdMaseg += temperC;
  lcd.clear();                //очистка экрана
  lcd.setCursor(0, 0);        // устанавливаем курсор в 0-ом
  lcd.print(lcdMaseg);        // выводим текущую температуру

  // Serial
  String serialMaseg = "Темперетуры с датчика DS18b20=";  // Формирования сообщения
  serialMaseg += temperC;
  Serial.println(serialMaseg);
}

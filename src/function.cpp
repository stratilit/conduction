#include "function.h"

// LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // инициализация LCD, указывая контакты данных
void lcdInit(void) {          // Настройка LCD
  byte customChar[8] = {	0b00111,	0b00101,	0b00111,	0b00000,
                          0b00000,	0b00000,	0b00000,	0b00000 };
  lcd.createChar(1, customChar);
  lcd.begin(16, 2);
}

void lcdLoad(void) {          // отображения загрузки LCD
  lcd.print("Loading");
  for (int i=0; i < 3; i++){
      delay(500);             // ждем 0.5 секунды
      lcd.print(".");
   }
}
void lcdShow(String s0, String s1) {   // Отправка данных первой строки LCD
  lcd.clear();                // Очистка экрана
  lcd.setCursor(0, 0);        // устанавливаем курсор на 1 строку
  lcd.print(s0);              // выводим текст 1 строки
  lcd.setCursor(0, 1);        // устанавливаем курсор на 2 строку
  lcd.print(s1);              // выводим текст 2 строки
}

// UART
void sendSerial(float t, float tds) {    // Отправка данных по UART
  String serialMaseg = "Темперетуры с датчика DS18b20=";
  serialMaseg += String(t, 1);    // Преобразование знечения температуры в текст
  serialMaseg += "; TDS=";
  serialMaseg += String(tds, 2);     // Преобразование знечения TDS в текст
  Serial.println(serialMaseg);
}

// Температура
OneWire ds(8);                 // инициализация датчика температуры DS18b20 интерфейс OneWire
float getTemper(void) {   // Запрос температуры с DS18b20
   byte data[2];               // Место для значения температуры
   ds.reset();                 // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
   ds.write(0xCC);             // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство
   ds.write(0x44);             // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
   ds.reset();                 // Теперь готовимся получить значение измеренной температуры
   ds.write(0xCC);             // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство
   ds.write(0xBE);             // Просим передать нам значение регистров со значением температуры
   data[0] = ds.read();        // Читаем младший байт значения температуры
   data[1] = ds.read();        // А теперь старший
   // Формируем итоговое значение:
     //    "склеиваем" значение,
     //    умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
   float temper =  ((data[1] << 8) | data[0]) * 0.0625;
   return temper;
 }

 String lcdStrTemper(float temper) { // Формирования строки отображения температуры на LCD
   String lcdMaseg = "t=";
   lcdMaseg += String(temper, 1);    // Преобразование знечения температуры в текст
   lcdMaseg += " \1""C";             // Еденицы измерения
   return lcdMaseg;
 }

// TDS
//Функция замера электропроводности в RAW
float fgetResistance(int d1, int d2, int a1, float delR, int cnt) {    //Функция замера сопротивления в RAW
  long fullData = (1023 * (long)cnt);
  unsigned long ap=0;
  unsigned long an=0;
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  int var=1;
  while(var < cnt){
    digitalWrite(d2, HIGH);
    ap = analogRead(a1) + ap;
    digitalWrite(d2, LOW);
    digitalWrite(d1, HIGH);
    an = (1023-analogRead(a1)) + an;
    digitalWrite(d1, LOW);
    var++;
  }
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  float apR = fcalcResistance(ap, fullData, var, delR);   // Сопротивление прямом токе
  float anR = fcalcResistance(an, fullData, var, delR);   // Сопротивление обратном токе
  return (apR + anR)/2;
}

float fcalcResistance(long countData, long fullData, int var, float delR) { // Расчет сопротивления
  float mean = ((float)countData)/var;           // Среднее значение отсчетов
  float mesR = delR/((float)(fullData - countData)/var); // Сопротивление на один отсчет
  return mean * mesR;
}

float fECTemp(float k, float ec0, float t){   // Функция термокомпенсации ЕС
  return ec0/(1+k*(t-25));
}

String lcdStrTds(float temper) {    // Формирования строки отображения TDS на LCD
  String lcdMaseg = "TDS=";
  if (temper < 1000) {
    lcdMaseg += String(temper, 1);    // Преобразование знечения температуры в текст
  }
  else {
    lcdMaseg += String(temper, 0);    // Преобразование знечения температуры в текст
  }
  lcdMaseg += " ppm";             // Еденицы измерения
  return lcdMaseg;
}

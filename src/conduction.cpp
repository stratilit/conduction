#include "function.h"

void setup() {
  lcdInit();                    // красивая "загрузка" программы при старте :)
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // Индикатор
}

void loop() {

  float wireTemper = getTemper();     // Получение температуры с датчика DS18b20
  String temperC = String(wireTemper, 1); // Преобразование знечения температуры в текст

  // LCD
  lcdShoTemper(temperC);

  // Serial
  sendSerial(temperC);

  delay(1000);

}

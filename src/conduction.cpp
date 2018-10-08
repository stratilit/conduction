#include "function.h"
#include <EEPROM.h>

struct kKalib { // Структура коэффицентов
  int ec1;      // 2 байта // Фактическое значение ЕС при нижнем пределе
  int ec2;      // 2 байта // Фактическое значение ЕС при верхнем пределе
  int x1;       // 2 байта // Показания АЦП при нижнем значении ЕС
  int x2;       // 2 байта // Показания АЦП при верхнем значении ЕС
  float tk;     // 4 байта // Коэффициент влияния температуры на проводимость раствора
};

kKalib kwtu;    // Структура для хранения коэффицентов

void setup() {
  //kw = {1011, 10000, 976, 9600, 0.02};
  //EEPROM.put(0, kw);
  EEPROM.get(0, kwtu);
  lcdInit();                    // Настройка LCD
  //lcdLoad();                  // отображения загрузки LCD
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT); // Индикатор

}

void loop() {
  // Температура
  float wireTemper = getTemper();     // Получение температуры с датчика DS18b20

  // TDS
  float tds0 = fgetResistance(9, 10, 0, 4620.0, 5000);    // замер сопротивления

  float tds1 = 1 / tds0 * 1000000;      // Расчет проводимости

  float tds2 = (fECTemp(kwtu.tk, tds1, wireTemper)) * 10;

  float tds3 = map(tds2, kwtu.x1, kwtu.x2, kwtu.ec1, kwtu.ec2);  // Калибровка

  float tds4 = (float)tds3 / 10;

  // LCD
  lcdShow(lcdStrTds(tds4), lcdStrTemper(wireTemper));

  // Serial
  //sendSerial(wireTemper, tds1);



}

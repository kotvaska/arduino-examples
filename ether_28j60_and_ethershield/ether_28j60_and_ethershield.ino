#include "etherShield.h"
#include "ETHER_28J60.h"
 
// Лампочка
int outputPin = 6;
 
// Здесь вводится MAC-адрес устройства. 
// На более современных шилдах он написан
// на самом шилде, но для нашего случая можно
// просто придумать уникальный адрес в нашей подсети.
static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24}; 
 
// Здесь указываем IP-адрес, на котором будет работать Arduino.
// Адрес должен находится в подсети роутера
static uint8_t ip[4] = {192, 168, 1, 20};
 
// Порт для общения. Стандартно 80-ый используется для HTTP.
static uint16_t port = 80;
 
ETHER_28J60 e;
 
void setup() { 
  // настраиваем шилд
  e.setup(mac, ip, port);
  pinMode(outputPin, OUTPUT);
}
 
void loop() {
  char* params;
 
  // проверяем, ввел ли пользователь 
  // в GET-запросе параметры
  if (params = e.serviceRequest())
  {
 
    // строим страницу для удаленного пользователя 
    // по адресу, указанном для шилда
    e.print("<H1>Web Remote</H1>");
 
    // зажигаем лампочку, если пришло ON
    if (strcmp(params, "?cmd=on") == 0)
    {
      e.print("<A HREF='?cmd=off'>Turn off</A>");
      digitalWrite(outputPin, HIGH);
    }
 
    // выключаем лампочку, если пришло OFF
    else if (strcmp(params, "?cmd=off") == 0)
    {
      e.print("<A HREF='?cmd=on'>Turn on</A>");
      digitalWrite(outputPin, LOW);
    }
    e.respond();
  }
}
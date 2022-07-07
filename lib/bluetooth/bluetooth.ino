#include "SoftwareSerial.h"
#include <AFMotor.h>     // подключаем библиотеку для шилда
AF_DCMotor motor1(1); // подключаем мотор к клеммникам M1
AF_DCMotor motor2(2); // подключаем мотор к клеммникам M2


SoftwareSerial BTserial(18, 19); // порт RX, порт TX
 
void setup()
{
  Serial.begin(9600);  
  BTserial.begin(9600); // По умолчанию 9600 бот.


    motor1.setSpeed(5); // задаем максимальную скорость мотора
  motor1.run(RELEASE);   // останавливаем мотор
  motor2.setSpeed(5); // задаем максимальную скорость мотора
  motor2.run(RELEASE);   // останавливаем мотор
}
 
void loop()
{
  if (BTserial.available())
  {
    Serial.write(BTserial.read());
  }
  if (Serial.available())
  {
    BTserial.write(Serial.read());
  }

    motor1.run(FORWARD);  // задаем движение вперед
  motor2.run(FORWARD);  // задаем движение вперед
  motor1.setSpeed(255);   // задаем скорость движения
  motor2.setSpeed(255);   // задаем скорость движения

  delay(2000);          // указываем время движения

  motor1.run(RELEASE);  // останавливаем мотор M1
  motor2.run(RELEASE);  // останавливаем мотор M2

  motor1.run(BACKWARD); // задаем движение назад
  motor2.run(BACKWARD); // задаем движение назад
  motor1.setSpeed(255);   // задаем скорость движения
  motor2.setSpeed(255);   // задаем скорость движения

  delay(2000);          // указываем время движения

  motor1.run(RELEASE);  // останавливаем мотор M1
  motor2.run(RELEASE);  // останавливаем мотор M2
}

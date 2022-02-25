#include <Servo.h>
#define PINPOT A0

Servo serv;
unsigned char servPos;
unsigned char potVal;
unsigned char lastVal;
bool active = false;

void setup()
{
  Serial.begin(9600);
  serv.detach();
  pinMode(PINPOT, INPUT);
  servPos = 30;
  serv.write(servPos);
}

void loop()
{
  if (Serial.available())
  {
    servPos = (unsigned char) map(Serial.read(), 0, 255, 0, 180);
    if (servPos != 0 && !active)
    {
      serv.attach(3);
      active = true;
    }
    if (servPos == 0 && active)
    {
      serv.detach();
      active = false;
    }
    if (active)
      serv.write(servPos);
  }
  lastVal = potVal;
  potVal = map(analogRead(PINPOT), 0, 1024, 0, 255);
  potVal = (potVal-19)*2.61;
  if (lastVal != potVal)
  {
    Serial.write(potVal);
    lastVal = potVal;
  }
  delay(20);
}

#include <Arduino.h>

void enableOutputs(){
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
}

void enableLedWithDelay(int ledPin, int delayTime)
{
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}

void setup()
{
  enableOutputs();
}

void loop()
{
  enableLedWithDelay(15, 1000);
  enableLedWithDelay(16, 1000);
  enableLedWithDelay(17, 1000);
  
}
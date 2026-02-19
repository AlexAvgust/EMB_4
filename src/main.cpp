#include <Arduino.h>

void led_init(){
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  for (u_int8_t i = 15; i <= 17; i++)
  {
    digitalWrite(i, LOW);
  }
}

void led_blink(u_int8_t ledPin, u_int16_t delayTime)
{
  delay(delayTime);
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
}

void setup()
{
  led_init();

}

void loop()
{
  led_blink(15, 600);
  led_blink(16, 600);
  led_blink(17, 600);
  
}
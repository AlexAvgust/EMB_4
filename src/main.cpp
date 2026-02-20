#include <Arduino.h>
// PINS
#define LED_RED 15
#define LED_GREEN 16
#define LED_BLUE 17

void led_init()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
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
  led_blink(LED_RED, 600);
  led_blink(LED_GREEN, 600);
  led_blink(LED_BLUE, 600);
}
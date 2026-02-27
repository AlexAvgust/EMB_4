#include <Arduino.h>
#include "leds/leds.h"
#include "buttons/button.h"
#include "globals.h"

LED_MODE MODE = LED_MODE::OFF;

void setup()
{
  Serial.begin(115200);
  pinMode(EXTERNAL_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INTERNAL_BUTTON_PIN, INPUT_PULLUP);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop()
{
  handleButtons(MODE);
  updateLeds(MODE);
}

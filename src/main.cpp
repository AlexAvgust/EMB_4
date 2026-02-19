#include <Arduino.h>
#include "leds/leds.h"
#include "buttons/button.h"

//PINS
constexpr uint8_t externalButtonPin = 4;
constexpr uint8_t internalButtonPin = 0;
constexpr uint8_t ledPin1 = 15;
constexpr uint8_t ledPin2 = 16;

uint8_t currentLedMode = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(externalButtonPin, INPUT_PULLUP);
  pinMode(internalButtonPin, INPUT_PULLUP);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop()
{ handleButtons(currentLedMode);
  updateLeds(currentLedMode);
}

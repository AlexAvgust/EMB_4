#include <Arduino.h>
#include "leds/leds.h"
#include "buttons/button.h"
// TIMING
const int debounceDelay = 50;

// STATE
unsigned long externalLastDebounceTime = 0;
unsigned long internalLastDebounceTime = 0;
uint8_t externalButtonState = LOW;
uint8_t internalButtonState = LOW;

uint8_t externalConfirmedState = LOW;
uint8_t internalConfirmedState = LOW;

uint8_t prevExternalConfirmedState = LOW;
uint8_t prevInternalConfirmedState = LOW;

// PINS
constexpr uint8_t externalButtonPin = 4;
constexpr uint8_t internalButtonPin = 0;

void debounceButton(uint8_t buttonPin, uint8_t &buttonState, unsigned long &lastDebounceTime)
{
  uint8_t reading = digitalRead(buttonPin);

  if (reading != buttonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    uint8_t *confirmed = nullptr;
    if (buttonPin == externalButtonPin)
      confirmed = &externalConfirmedState;
    else if (buttonPin == internalButtonPin)
      confirmed = &internalConfirmedState;

    if (confirmed && reading != *confirmed)
    {
      *confirmed = reading;
    }
  }

  buttonState = reading;
}

void handleButtons(uint8_t &currentLedMode)
{
  debounceButton(externalButtonPin, externalButtonState, externalLastDebounceTime);
  debounceButton(internalButtonPin, internalButtonState, internalLastDebounceTime);
  bool externalRising = (externalConfirmedState == HIGH && prevExternalConfirmedState == LOW);
  bool internalRising = (internalConfirmedState == HIGH && prevInternalConfirmedState == LOW);

  if (externalConfirmedState == HIGH &&
      internalRising)
  {
    Serial.println("BOTH LEDS ON");
    currentLedMode = 2;
  }
  else if (internalRising)
  {
    Serial.println("SLOW FLICKERING MODE");
    currentLedMode = 0;
  }
  else if (externalRising)
  {
    Serial.println("FAST FLICKERING MODE");
    currentLedMode = 1;
  }
 

    prevExternalConfirmedState = externalConfirmedState;
  prevInternalConfirmedState = internalConfirmedState;
}
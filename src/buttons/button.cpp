#include <Arduino.h>
#include "leds/leds.h"
#include "buttons/button.h"
#include "globals.h"

#define DEBOUNCE_DELAY_MS 50

ButtonState EXT_BTN = {EXTERNAL_BUTTON_PIN}; 
ButtonState INT_BTN = {INTERNAL_BUTTON_PIN};

void debounceButton(ButtonState &button)
{
  uint8_t reading = digitalRead(button.pin);

  if (reading != button.lastRawReading)
  {
    button.lastDebounceTime = millis();
  }

  if ((millis() - button.lastDebounceTime) > DEBOUNCE_DELAY_MS)
  {
    if (reading != button.confirmedState)
    {
      button.confirmedState = reading;
    }
  }

  button.lastRawReading = reading;
}

void handleButtons(LED_MODE &currentLedMode)
{
  debounceButton(EXT_BTN);
  debounceButton(INT_BTN);
  
  bool externalRising = (EXT_BTN.confirmedState == HIGH && EXT_BTN.prevState == LOW);
  bool internalRising = (INT_BTN.confirmedState == HIGH && INT_BTN.prevState == LOW);

  if ((externalRising && INT_BTN.confirmedState == HIGH) || 
      (internalRising && EXT_BTN.confirmedState == HIGH))
  {
    Serial.println("BOTH LEDS ON");
    currentLedMode = LED_MODE::SOLID;
  }
  else if (internalRising && EXT_BTN.confirmedState == LOW)
  {
    Serial.println("SLOW FLICKERING MODE");
    currentLedMode = LED_MODE::BLINKING;
  }
  else if (externalRising && INT_BTN.confirmedState == LOW)
  {
    Serial.println("FAST FLICKERING MODE");
    currentLedMode = LED_MODE::FAST_FLICKER;
  }

  EXT_BTN.prevState = EXT_BTN.confirmedState;
  INT_BTN.prevState = INT_BTN.confirmedState;
}
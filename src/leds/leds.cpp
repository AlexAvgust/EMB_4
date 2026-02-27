#include <Arduino.h>
#include "globals.h"

unsigned long lastFlickerUpdate = 0;
bool flickerState = false;

void updateLeds(LED_MODE &currentLedMode)
{
    unsigned long currentMillis = millis();
    int interval = 0;

    switch (currentLedMode)
    {
    case LED_MODE::SOLID:
        interval = 1000;
        break;
    case LED_MODE::BLINKING:
        interval = 100;
        break;
    case LED_MODE::FAST_FLICKER:
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, HIGH);
        break;
    }

    if (currentMillis - lastFlickerUpdate >= interval)
    {
        lastFlickerUpdate = currentMillis;
        flickerState = !flickerState;

        digitalWrite(GREEN_LED_PIN, flickerState);
        digitalWrite(RED_LED_PIN, !flickerState);
    }
}

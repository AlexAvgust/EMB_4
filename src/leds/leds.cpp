#include <Arduino.h>

// PINS
constexpr uint8_t ledPin1 = 15;
constexpr uint8_t ledPin2 = 16;

// STATE
//  TIMING FOR LEDs
unsigned long lastFlickerUpdate = 0;
bool flickerState = false;

void updateLeds(uint8_t currentLedMode)
{
    unsigned long currentMillis = millis();
    int interval = 0;

    switch (currentLedMode)
    {
    case 0:
        interval = 1000;
        break;
    case 1:
        interval = 100;
        break;
    case 2:
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        break;
    }

    if (currentMillis - lastFlickerUpdate >= interval)
    {
        lastFlickerUpdate = currentMillis;
        flickerState = !flickerState;

        digitalWrite(ledPin1, flickerState);
        digitalWrite(ledPin2, !flickerState);
    }
}

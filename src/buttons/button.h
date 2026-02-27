#pragma once

void handleButtons(LED_MODE& currentLedMode);
struct ButtonState
{
    ButtonState(uint8_t buttonPin) : pin(buttonPin) {}
    const uint8_t pin;
    unsigned long lastDebounceTime = 0;
    uint8_t lastRawReading = LOW;
    uint8_t confirmedState = LOW;
    uint8_t prevState = LOW;
};

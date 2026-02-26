#include <Arduino.h>
#include <OneButton.h>
#include <button/button.h>
#include <globals.h>

// OneButton click callback for upper button
// Forwards to the appropriate handler stored in application state
void upperButtonClick(void *ptr)
{
    WifiMonitorState *state = static_cast<WifiMonitorState *>(ptr);
    Serial.println("Upper button clicked");

    if (state->upperButtonCb) {
        state->upperButtonCb(state);
    }
}

// OneButton click callback for lower button
// Forwards to the appropriate handler stored in application state
void lowerButtonClick(void *ptr)
{
    WifiMonitorState *state = static_cast<WifiMonitorState *>(ptr);
    Serial.println("Lower button clicked");

    if (state->lowerButtonCb) {
        state->lowerButtonCb(state);
    }   
}

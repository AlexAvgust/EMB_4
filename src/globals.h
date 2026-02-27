#pragma once

#define EXTERNAL_BUTTON_PIN 4
#define INTERNAL_BUTTON_PIN 0
#define GREEN_LED_PIN 15
#define RED_LED_PIN 16

enum class LED_MODE : uint8_t
{
  OFF = 0,
  SOLID = 1,
  BLINKING = 2,
  FAST_FLICKER = 3
};
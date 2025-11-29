#pragma once
#include <FastLED.h>

namespace SharedPalette {
  static const CRGB kHolidayPalette[] = {
    CRGB::Purple,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Red,
    CRGB::Teal,
    CRGB::Yellow,
  };
  const uint8_t kNumColors = sizeof(kHolidayPalette) / sizeof(kHolidayPalette[0]);

  // Warm white color definition
  static const CRGB kWarmWhite = CRGB(255, 255, 90);
}

#pragma once
#include "Pattern.h"
#include "SharedPalette.h"
#include "SystemConfig.h"

class HolidayColorsPattern : public Pattern {
public:
  void draw(CRGB* L) override {
    // Shift the pattern by half the palette size every 5 seconds
    uint8_t offset = ((millis() / kColorShiftIntervalMs) % 2) * (SharedPalette::kNumColors / 2);

    for (int j = 0; j < System::kNumLeds; j++) {
      L[j] = SharedPalette::kHolidayPalette[(j + offset) % SharedPalette::kNumColors];
    }
  }

private:
  static constexpr uint16_t kColorShiftIntervalMs = 5000;
};

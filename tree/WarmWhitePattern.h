#pragma once
#include "Pattern.h"
#include "SystemConfig.h"
#include "SharedPalette.h"

class WarmWhitePattern : public Pattern {
public:
  void draw(CRGB* L) override {
    uint16_t time = millis() / kTimeDivisor;
    for (int i = 0; i < System::kNumLeds; i++) {
      uint8_t phase = (i * kPhaseMultiplier) + time;
      uint8_t wave = sin8(phase);
      
      // Map wave (0-255) to brightness (~160-255) for subtle shimmering
      // Amplitude is approx 3/8 (0.375) of full range
      uint8_t brightness = (255 - ((255 >> 2) + (255 >> 3))) + ((wave >> 2) + (wave >> 3));
      
      L[i] = SharedPalette::kWarmWhite;
      L[i].nscale8(brightness);
    }
  }

private:
  static constexpr uint8_t kTimeDivisor = 20;
  // Use a large prime to scatter the phases so it looks random
  static constexpr uint8_t kPhaseMultiplier = 67;
};

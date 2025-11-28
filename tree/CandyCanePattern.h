#pragma once
#include "Pattern.h"
#include "SystemConfig.h"

class CandyCanePattern : public Pattern {
public:
  void draw(CRGB* L) override {
    uint16_t offset = millis() / kScrollSpeedMs;
    
    for (int i = 0; i < System::kNumLeds; i++) {
      // Calculate position within the repeating stripe pattern
      // Pattern length is 2 * kStripeWidth (one red stripe, one white stripe)
      uint16_t pos = (i + offset) % (kStripeWidth * 2);
      
      if (pos < kStripeWidth) {
        L[i] = kRed;
      } else {
        L[i] = kWhite;
      }
    }
  }

private:
  static constexpr uint8_t kStripeWidth = 10;
  static constexpr uint8_t kScrollSpeedMs = 100; // Lower is faster (ms per pixel)
  static constexpr uint32_t kRed = CRGB::Red;
  static constexpr uint32_t kWhite = CRGB::Gray;
};


#pragma once
#include "Pattern.h"
#include "SharedPalette.h"
#include "SystemConfig.h"

class TwinklePattern : public Pattern {
public:
  void start() override {
    // Cycle to the next background color each time we start
    m_currentColorIndex = (m_currentColorIndex + 1) % SharedPalette::kNumColors;
  }

  void draw(CRGB* L) override {
    // "prng16" is the pseudorandom number generator
    // It MUST be reset to the same starting value each time
    // this function is called, so that the sequence of 'random'
    // numbers that it generates is (paradoxically) stable.
    uint16_t prng16 = kPrngSeed;
    uint32_t clock32 = millis();
    CRGB bg = SharedPalette::kHolidayPalette[m_currentColorIndex];
    uint8_t backgroundBrightness = bg.getAverageLight();

    for (int i = 0; i < System::kNumLeds; i++) {
      prng16 = (uint16_t)(prng16 * kPrngMultiplier) + kPrngIncrement;
      uint16_t pixelPhase = prng16;
      prng16 = (uint16_t)(prng16 * kPrngMultiplier) + kPrngIncrement;
      
      uint8_t pixelFrequencyQ5_3 = ((((prng16 & 0xFF) >> 4) + (prng16 & 0x0F)) & 0x0F) + 0x08;
      uint32_t pixelClock = (uint32_t)((clock32 * pixelFrequencyQ5_3) >> 3) + pixelPhase;
      uint8_t pixelSalt = prng16 >> 8;

      CRGB c = computeOneTwinkle(pixelClock, pixelSalt);
      uint8_t cbright = c.getAverageLight();
      int16_t deltabright = cbright - backgroundBrightness;
      
      if (deltabright >= kBrightnessThreshold || (!bg)) {
        L[i] = c;
      } else if (deltabright > 0) {
        L[i] = blend(bg, c, deltabright * 8);
      } else {
        L[i] = bg;
      }
    }
  }

private:
  static constexpr uint8_t kSpeed = 4;
  static constexpr uint8_t kDensity = 2;
  static constexpr uint16_t kPrngSeed = 11337;
  static constexpr uint16_t kPrngMultiplier = 2053;
  static constexpr uint16_t kPrngIncrement = 1384;
  static constexpr uint8_t kAttackThreshold = 86;
  static constexpr uint8_t kBrightnessThreshold = 32;
  
  uint8_t m_currentColorIndex = 0;

  CRGB computeOneTwinkle(uint32_t ms, uint8_t salt) {
    uint16_t ticks = ms >> (8 - kSpeed);
    uint8_t fastCycle8 = ticks;
    uint16_t slowCycle16 = (ticks >> 8) + salt;
    slowCycle16 += sin8(slowCycle16);
    slowCycle16 = (slowCycle16 * kPrngMultiplier) + kPrngIncrement;
    uint8_t slowCycle8 = (slowCycle16 & 0xFF) + (slowCycle16 >> 8);

    uint8_t bright = 0;
    if (((slowCycle8 & 0x0E) / 2) < kDensity) {
      bright = attackDecayWave8(fastCycle8);
    }

    CRGB c;
    if (bright > 0) {
      c = SharedPalette::kWarmWhite;
      c.maximizeBrightness(bright);
    } else {
      c = CRGB::Black;
    }
    return c;
  }

  uint8_t attackDecayWave8(uint8_t i) {
    if (i < kAttackThreshold) {
      return i * 3;
    } else {
      i -= kAttackThreshold;
      return 255 - (i + (i / 2));
    }
  }
};

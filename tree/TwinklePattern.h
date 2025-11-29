#pragma once
#include "Pattern.h"
#include "SharedPalette.h"
#include "SystemConfig.h"
#include "Clock.h"

class TwinklePattern : public Pattern {
public:
  void start() override {
    // Cycle to the next background color each time we start
    m_currentColorIndex = (m_currentColorIndex + 1) % SharedPalette::kNumColors;
  }

  void draw(CRGB* L) override {
    CRGB bg = SharedPalette::kHolidayPalette[m_currentColorIndex];
    uint32_t ms = millis();

    for (int i = 0; i < System::kNumLeds; i++) {
      // Use the clock to generate a value for this pixel
      // 15ms per step = ~3.75s period
      uint8_t clock = Clock::getRandomPixel(ms, i, 15);
      
      // Use a sine wave to make it pulse smoothly
      uint8_t wave = sin8(clock);
      
      // Only light up if wave is high (creates sparsity)
      // Threshold of 235 means only ~10% of the cycle is "on"
      if (wave > 235) {
        // Map the top range (235-255) to full brightness (0-255)
        uint8_t brightness = map(wave, 235, 255, 0, 255);

        CRGB twinkle = SharedPalette::kWarmWhite;
        twinkle.nscale8(brightness);
        
        // Blend with background
        if (bg) {
             L[i] = blend(bg, twinkle, brightness);
        } else {
             L[i] = twinkle;
        }
      } else {
        L[i] = bg;
      }
    }
  }

private:
  uint8_t m_currentColorIndex = 0;
};

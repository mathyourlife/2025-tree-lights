#include <FastLED.h>

#include "SystemConfig.h"
#include "SharedPalette.h"
#include "Pattern.h"
#include "TwinklePattern.h"
#include "HolidayColorsPattern.h"
#include "WarmWhitePattern.h"
#include "CandyCanePattern.h"
#include "PixiePattern.h"

CRGB leds[System::kNumLeds];

// ---------------------------------------------------------------------------
// Main Program
// ---------------------------------------------------------------------------

TwinklePattern twinklePattern;
HolidayColorsPattern holidayColorsPattern;
WarmWhitePattern warmWhitePattern;
CandyCanePattern candyCanePattern;
PixiePattern pixiePattern;

Pattern* patterns[] = {
  &pixiePattern,
  &twinklePattern,
  &holidayColorsPattern,
  &warmWhitePattern,
  &candyCanePattern
};

const uint8_t kNumPatterns = sizeof(patterns) / sizeof(patterns[0]);
uint8_t currentPatternIndex = 0;

void setup() {
  FastLED.addLeds<WS2812B, System::kLedPin, RGB>(leds, System::kNumLeds);
  // ALITOVE 12V WS2811 pixels usually need TypicalLEDStrip correction
  // to fix the bluish tint of the white.
  // If pixels look too yellow/warm, try Typical8mmPixel correction instead.
  FastLED.setCorrection(TypicalLEDStrip);
  
  // Initialize all pixels to black
  FastLED.clear(true);
  
  FastLED.setBrightness(System::kGlobalBrightness);
  FastLED.setMaxPowerInMilliWatts(System::kMaxPowerMw);

  // Initialize the first pattern
  patterns[currentPatternIndex]->start();
  FastLED.show();  
}

void loop() {
  EVERY_N_MILLISECONDS(System::kFrameRateMs) {
    EVERY_N_SECONDS(System::kPatternDurationSec) {
      currentPatternIndex = (currentPatternIndex + 1) % kNumPatterns;
      patterns[currentPatternIndex]->start();
    }

    patterns[currentPatternIndex]->draw(leds);
    FastLED.show();
  }
}

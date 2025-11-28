#pragma once
#include <FastLED.h>

class Pattern {
public:
  // Draw (redraw) the pattern into the provided LED array
  virtual void draw(CRGB* leds) = 0;
  // Called when pattern becomes active
  virtual void start() {}
  virtual ~Pattern() {}
};

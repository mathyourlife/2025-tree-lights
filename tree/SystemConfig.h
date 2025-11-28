#pragma once
#include <Arduino.h>

namespace System {
  constexpr uint8_t kLedPin = 7;
  constexpr uint16_t kNumLeds = 300;
  constexpr uint32_t kMaxPowerMw = 180000; // 180W
  constexpr uint8_t kGlobalBrightness = 255;
  constexpr uint8_t kFrameRateMs = 20;  // 50 FPS
  constexpr uint8_t kPatternDurationSec = 60;
}

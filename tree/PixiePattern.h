#pragma once
#include "Pattern.h"
#include "SystemConfig.h"
#include "SharedPalette.h"

class PixiePattern : public Pattern {
public:
  void start() override {
    m_activePixies = random(1, kNumPixies + 1);
    for (int i = 0; i < m_activePixies; i++) {
      m_pixies[i].pos = random(System::kNumLeds);
      m_pixies[i].color = SharedPalette::kHolidayPalette[i % SharedPalette::kNumColors];
      changeVelocity(m_pixies[i]);
    }
  }

  void draw(CRGB* leds) override {
    fadeToBlackBy(leds, System::kNumLeds, 32);

    uint32_t now = millis();
    
    for (int i = 0; i < m_activePixies; i++) {
      Pixie& p = m_pixies[i];

      if (now > p.nextChange) {
        changeVelocity(p);
      }

      float nextPos = p.pos + p.velocity;
      
      // Handle bounces and drawing
      if (nextPos < 0) {
          drawLine(leds, p.pos, 0, p.color);
          nextPos = -nextPos;
          p.velocity = -p.velocity;
          drawLine(leds, 0, nextPos, p.color);
      } else if (nextPos >= System::kNumLeds) {
          drawLine(leds, p.pos, System::kNumLeds - 1, p.color);
          nextPos = System::kNumLeds - 1 - (nextPos - (System::kNumLeds - 1));
          p.velocity = -p.velocity;
          drawLine(leds, System::kNumLeds - 1, nextPos, p.color);
      } else {
          drawLine(leds, p.pos, nextPos, p.color);
      }
      
      p.pos = nextPos;
    }
  }

private:
  struct Pixie {
    float pos;
    float velocity;
    uint32_t nextChange;
    CRGB color;
  };

  static const int kNumPixies = SharedPalette::kNumColors;
  Pixie m_pixies[kNumPixies];
  int m_activePixies = kNumPixies;

  void changeVelocity(Pixie& p) {
    // Random speed: 0.01 to 1.0 pixels per frame
    float speed = random(0, 100) / 100.0f;
    if (random(2) == 0) speed = -speed;
    p.velocity = speed;
    p.nextChange = millis() + random(200, 1500);
  }

  void drawLine(CRGB* leds, float startPos, float endPos, CRGB color) {
    int start = (int)startPos;
    int end = (int)endPos;
    int step = (start < end) ? 1 : -1;
    
    if (start == end) {
        if (start >= 0 && start < System::kNumLeds) {
            leds[start] = color;
        }
    } else {
        for (int i = start; i != end + step; i += step) {
            if (i >= 0 && i < System::kNumLeds) {
                leds[i] = color;
            }
        }
    }
  }
};

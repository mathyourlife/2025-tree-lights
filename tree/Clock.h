#pragma once
#include <Arduino.h>

namespace Clock {

/**
 * Generates a unique 8-bit clock value for a pixel based on time and its index.
 * Useful for each pixel in a strip getting its own phase shifted clock.
 * 
 * @param ms The current time in milliseconds (e.g. from millis())
 * @param pixelIndex The index of the pixel (0 to N)
 * @param msPerClockStep The period in milliseconds for one clock step.
 *                       A full 0-255 cycle takes 256 * msPerClockStep.
 * @return A 0-255 value that cycles over time.
 */
inline uint8_t getRandomPixel(uint32_t ms, uint16_t pixelIndex, uint16_t msPerClockStep) {
  // Hash the index to get a pseudo-random phase
  // This uses a simple integer hash to scatter the bits
  uint32_t x = pixelIndex;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  
  return (uint8_t)x + (ms / msPerClockStep);
}

}

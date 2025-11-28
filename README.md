# Tree Lights 2025

## Adding a New Pattern

To add a new light pattern to the system:

* Create a new header file in the `tree/` directory (e.g., `MyNewPattern.h`).
* Define a class that inherits from the `Pattern` interface.
* Implement the `draw` method to update the LEDs.

Example `MyNewPattern.h`:

```cpp
#pragma once
#include "Pattern.h"

class MyNewPattern : public Pattern {
public:
  void draw(CRGB* leds) override {
    // Update leds[] array here
    // e.g. fill_solid(leds, System::kNumLeds, CRGB::Red);
  }
  
  // Optional: reset state when pattern starts
  void start() override {
    // Reset variables
  }
};
```

* Register the pattern in `tree/tree.ino`:
  * Add `#include "MyNewPattern.h"` at the top.
  * Instantiate the pattern object: `MyNewPattern myNewPattern;`
  * Add `&myNewPattern` to the `patterns` array.

## Compiling with Arduino CLI

You can use `arduino-cli` to test compile the code from the command line.

* Install the required library:
```bash
arduino-cli lib install FastLED
```

* Compile the sketch (replace `arduino:avr:uno` with your target board FQBN):
```bash
arduino-cli compile --fqbn arduino:avr:uno tree
```

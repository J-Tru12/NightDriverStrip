#pragma once

#include "effectmanager.h"
#include "effects/strip/musiceffect.h"
// Derived from https://wokwi.com/projects/288857088376963592

#if ENABLE_AUDIO
class PatternSMSinDots : public BeatEffectBase,
                         public LEDStripEffect
#else
class PatternSMSinDots : public LEDStripEffect
#endif
{
 private:
 public:
  PatternSMSinDots()
      :
#if ENABLE_AUDIO
        BeatEffectBase(1.50, 0.05),
#endif
        LEDStripEffect(EFFECT_MATRIX_SMSIN_DOTS, "Sin Dots") {
  }

  PatternSMSinDots(const JsonObjectConst& jsonObject)
      :
#if ENABLE_AUDIO
        BeatEffectBase(1.50, 0.05),
#endif
        LEDStripEffect(jsonObject) {
  }

  void Start() override { g()->Clear(); }

  void Draw() override {
#if ENABLE_AUDIO
    ProcessAudio();
#endif
    int8_t i, t, u;
    t = millis() / 15;
    u = t * 2;
    int size = std::min(MATRIX_WIDTH, MATRIX_HEIGHT) - 1;  // always a square.
    // This might look better with the FP-based setPixelXYF that we
    // have floating (ha!) around elsewhere in this code. Maybe later.
    // The large final argument to blur2d helps a lot.
    for (i = size; i--;)
      g()->leds[g()->xy((sin8(t + i * size) >> 3) + (size / 2),
                        sin8(u + i * size) >> 3)]
          .setHue(i * (size - 1));
    g()->blur2d(g()->leds, MATRIX_WIDTH, 0, MATRIX_HEIGHT, 0, 128);
    fadeAllChannelsToBlackBy(60);
  }

#if ENABLE_AUDIO
  void HandleBeat(bool bMajor, float elapsed, float span) override {}
#endif
};

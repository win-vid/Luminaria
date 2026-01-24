/*
 * ===============================================
 * Animations.ino - LED-Animationen
 * ===============================================
 */

// ============================================
// Fade-Animationen
// ============================================

/**
 * Sanfter Farbübergang von aktueller Farbe zu Zielfarbe
 * @param targetColor Zielfarbe
 * @param totalTime Gesamtdauer der Animation in ms
 */
void ColourFadeTo(CRGB targetColor, uint16_t totalTime) {
  const uint8_t frameDelay = 20;  // 20ms = 50 FPS
  uint16_t steps = totalTime / frameDelay;
  
  if (steps == 0) steps = 1;
  
  previousColor = currentColor;
  
  for (uint16_t step = 0; step <= steps; step++) {
    uint8_t r = map(step, 0, steps, currentColor.r, targetColor.r);
    uint8_t g = map(step, 0, steps, currentColor.g, targetColor.g);
    uint8_t b = map(step, 0, steps, currentColor.b, targetColor.b);
    
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(frameDelay);
  }
  
  currentColor = targetColor;
}

/**
 * Fade zurück zur vorherigen Farbe (Hin-und-Her-Effekt)
 * @param totalTime Gesamtdauer der Animation in ms
 */
void ColourFadeBack(uint16_t totalTime) {
  const uint8_t frameDelay = 20;
  uint16_t steps = totalTime / frameDelay;
  
  if (steps == 0) steps = 1;
  
  CRGB temp = currentColor;
  
  for (uint16_t step = 0; step <= steps; step++) {
    uint8_t r = map(step, 0, steps, currentColor.r, previousColor.r);
    uint8_t g = map(step, 0, steps, currentColor.g, previousColor.g);
    uint8_t b = map(step, 0, steps, currentColor.b, previousColor.b);
    
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(frameDelay);
  }
  
  currentColor = previousColor;
  previousColor = temp;
}

/**
 * Fade zwischen zwei spezifischen Farben
 * @param startColor Startfarbe
 * @param endColor Zielfarbe
 * @param totalTime Gesamtdauer der Animation in ms
 */
void ColourFade(CRGB startColor, CRGB endColor, uint16_t totalTime) {
  const uint8_t frameDelay = 20;
  uint16_t steps = totalTime / frameDelay;
  
  if (steps == 0) steps = 1;
  
  for (uint16_t step = 0; step <= steps; step++) {
    uint8_t r = map(step, 0, steps, startColor.r, endColor.r);
    uint8_t g = map(step, 0, steps, startColor.g, endColor.g);
    uint8_t b = map(step, 0, steps, startColor.b, endColor.b);
    
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(frameDelay);
  }
  
  currentColor = endColor;
}

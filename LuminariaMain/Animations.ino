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

// Generates a rainbow test image. Used to test functionality of the LED-Matrix.
  void TestImage(){
    for(hue = 0; hue <= 255; hue++){
      // Increment hue each frame for animation
      fill_rainbow(leds, NUM_LEDS, hue, 7);  // 7 = spacing between LEDs
      FastLED.show();
      
      delay(10);
  }
  }

// Emulated a fire flicker effect 
void Fire(CRGB* leds, int height, int width){
  BlendCheckerBoard(leds, CRGB::Red, CRGB::Orange, height, width);
  FastLED.setBrightness(random(30,100));
  BlendCheckerBoard(leds, CRGB::Orange, CRGB::Red, height, width);
  FastLED.setBrightness(random(30,100));
}

// Blends a CheckerBoard between its two given colors
void BlendCheckerBoard(CRGB* leds, CRGB color1, CRGB color2, int height, int width) {

  for(int lerpAmount = 0; lerpAmount < 255; lerpAmount++){
    // Matrix Loop
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {

        if(y % 2 == 0){
          if (x % 2 == 0) {
            leds[XY(x, y)] = blend(color1, color2, lerpAmount);
          } else {
            leds[XY(x, y)] = blend(color2, color1, lerpAmount);
          }
        } else{
          if (x % 2 == 1) {
            leds[XY(x, y)] = blend(color1, color2, lerpAmount);
          } else {
            leds[XY(x, y)] = blend(color2, color1, lerpAmount);
          }
        }
      }
    }
    FastLED.show();

    delay(1);
  }
}

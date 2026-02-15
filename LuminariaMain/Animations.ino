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

/**
 * Generates top-down Perlin noise based fire effect on the LED matrix.
 *
 * @param leds   Pointer to LED buffer
 * @param width  Matrix width in pixels
 * @param height Matrix height in pixels
 * @param scale  Scale of noise. Set to 1 to fill the matrix with a single color.
 *
 * TODO: Sometimes we have dead pixels.
 */
void Fire(CRGB* leds, int height, int width, int scale, int brightness){
  
  // t to move the perlin noise per frame
  static uint16_t t = 0;
  t += 1;

  for (uint8_t y = 0; y < height; y++) {
    for (uint8_t x = 0; x < width; x++) {

      // Generates noise on current x, y position multiplied by scale
      uint8_t noise = inoise8(x * scale, y * scale, t);

      // Increase contrast
      uint8_t heat = qsub8(noise, 40);
      heat = scale8(heat, 200);

      // Calculates color based on the height of the noise
      leds[XY(x, y)] = ColorFromPalette(
        HeatColors_p,
        heat,
        brightness,
        LINEARBLEND
      );
    }
  }
  FastLED.show();
  delay(15);
}

// Blends a checker board between its two given colors
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

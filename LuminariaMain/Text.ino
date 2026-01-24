/*
 * ===============================================
 * Text.ino - Text und Scrolling-Funktionen
 * ===============================================
 */

// ============================================
// 5x7 Font-Definition
// ============================================
// Jedes Zeichen ist 5 Pixel breit, 7 Pixel hoch
// 1 = LED an, 0 = LED aus

const uint8_t font5x7[][5] = {
  {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
  {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
  {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
  {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
  {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
  {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
  {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
  {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
  {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
  {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
  {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
  {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
  {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
  {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
  {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
  {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
  {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
  {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
  {0x46, 0x49, 0x49, 0x49, 0x31}, // S
  {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
  {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
  {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
  {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
  {0x63, 0x14, 0x08, 0x14, 0x63}, // X
  {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
  {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
  {0x00, 0x00, 0x00, 0x00, 0x00}, // Leerzeichen
  {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
  {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
  {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
  {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
  {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
  {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
  {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
  {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
  {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
  {0x06, 0x49, 0x49, 0x29, 0x1E}  // 9
};

// ============================================
// Hilfsfunktionen
// ============================================

/**
 * Konvertiert ein Zeichen in Font-Index
 * @param c Zeichen (A-Z, 0-9, Leerzeichen)
 * @return Index im Font-Array
 */
uint8_t charToIndex(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a';  // Kleinbuchstaben → Großbuchstaben
  if (c == ' ') return 26;
  if (c >= '0' && c <= '9') return 27 + (c - '0');
  return 26;  // Unbekannte Zeichen → Leerzeichen
}

/**
 * Zeichnet ein Zeichen an Position x
 * @param c Zeichen
 * @param xOffset X-Offset (kann negativ sein für Scrolling)
 * @param color Farbe
 */
void drawChar(char c, int8_t xOffset, CRGB color) {
  uint8_t index = charToIndex(c);
  
  for (uint8_t col = 0; col < 5; col++) {
    int8_t x = xOffset + col;
    if (x < 0 || x >= 8) continue;  // Außerhalb der Matrix
    
    for (uint8_t row = 0; row < 7; row++) {
      if (font5x7[index][col] & (1 << row)) {
        leds[XY(x, row)] = color;
      }
    }
  }
}

// ============================================
// Scrolling-Text
// ============================================

/**
 * Scrollt einen Text von rechts nach links über die Matrix
 * @param text Text zum Anzeigen
 * @param color Textfarbe
 * @param speed Geschwindigkeit in ms pro Frame (kleiner = schneller)
 */
void scrollText(const char* text, CRGB color, uint16_t speed) {
  uint8_t textLength = strlen(text);
  int16_t totalWidth = textLength * 6;  // 5 Pixel + 1 Pixel Abstand pro Zeichen
  
  // Von rechts außerhalb nach links außerhalb scrollen
  for (int16_t offset = 8; offset > -totalWidth; offset--) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Matrix löschen
    
    // Jedes Zeichen zeichnen
    for (uint8_t i = 0; i < textLength; i++) {
      drawChar(text[i], offset + (i * 6), color);
    }
    
    FastLED.show();
    delay(speed);
  }
}

/**
 * Zeigt einen einzelnen Buchstaben zentriert an
 * @param c Zeichen
 * @param color Farbe
 */
void showChar(char c, CRGB color) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  drawChar(c, 1, color);  // Zentriert bei x=1 (da Zeichen 5 Pixel breit)
  FastLED.show();
}

/*
 * ===============================================
 * Matrix.ino - Matrix-spezifische Funktionen
 * ===============================================
 */

// ============================================
// XY-Koordinaten Mapping
// ============================================

/**
 * Konvertiert XY-Koordinaten in LED-Index
 * @param x X-Koordinate (0-7)
 * @param y Y-Koordinate (0-7)
 * @return LED-Index (0-63) oder 64 bei ungültigen Koordinaten
 */
uint8_t XY(uint8_t x, uint8_t y) {
  // Koordinaten-Validierung mit Debug-Ausgabe
  if (x >= MATRIX_WIDTH || y >= MATRIX_HEIGHT) {
    Serial.print("FEHLER: Ungültige Koordinate(n) - ");
    
    if (x >= MATRIX_WIDTH && y >= MATRIX_HEIGHT) {
      Serial.print("X und Y außerhalb! ");
    } else if (x >= MATRIX_WIDTH) {
      Serial.print("X außerhalb! ");
    } else {
      Serial.print("Y außerhalb! ");
    }
    
    Serial.print("(");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(") - Erlaubt: X: 0-");
    Serial.print(MATRIX_WIDTH - 1);
    Serial.print(", Y: 0-");
    Serial.println(MATRIX_HEIGHT - 1);
    return 64;  // Fallback: keine LED ansprechen
  }
  
  // Y-Achse invertieren (0,0) = oben links
  return ((MATRIX_HEIGHT - 1 - y) * MATRIX_WIDTH) + x;
}

// ============================================
// Zeilen- und Spalten-Funktionen
// ============================================

/**
 * Setzt eine komplette Zeile auf eine Farbe
 * @param row Zeilen-Index (0-7, 0=oben)
 * @param color Farbe
 */
void setRow(uint8_t row, CRGB color) {
  if (row >= MATRIX_HEIGHT) {
    Serial.print("FEHLER: Ungültige Zeile ");
    Serial.println(row);
    return;
  }
  for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
    leds[XY(x, row)] = color;
  }
}

/**
 * Setzt eine komplette Spalte auf eine Farbe
 * @param col Spalten-Index (0-7)
 * @param color Farbe
 */
void setCol(uint8_t col, CRGB color) {
  if (col >= MATRIX_WIDTH) {
    Serial.print("FEHLER: Ungültige Spalte ");
    Serial.println(col);
    return;
  }
  for (uint8_t y = 0; y < MATRIX_HEIGHT; y++) {
    leds[XY(col, y)] = color;
  }
}

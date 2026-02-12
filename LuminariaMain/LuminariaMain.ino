/*
 * ===============================================
 *          LED Matrix Controller - Luminaria
 * ===============================================
 * 
 * Projekt:     Luminaria - LED Matrix Steuerung
 * Autor:       Tim
 * Datum:       23. Januar 2026
 * 
 * Hardware:
 *   - Microcontroller: ESP32-S3-N16-R8-DevModul
 *   - LED Matrix: CJMCU-8x8 Modul (WS2812B)
 *   - Anschlüsse:
 *     DIN  -> GPIO 23
 *     VCC  -> 5V
 *     GND  -> GND
 * 
 * Beschreibung:
 *   Steuerung einer 8x8 WS2812B LED Matrix (64 LEDs)
 *   mit Farbanimationen und koordinatenbasierter Ansteuerung
 * 
 * ===============================================
 */

// ============================================
// Bibliotheken
// ============================================
#include <FastLED.h>

// ============================================
// Hardware-Konfiguration
// ============================================
#define LED_PIN       16        // DIN Pin (Datenleitung)
#define BRIGHTNESS    50         // Helligkeit (0-255)
#define LED_TYPE      WS2812B   // LED Typ
#define COLOR_ORDER   GRB       // Farbordnung der LEDs
#define MATRIX_WIDTH  8         // Breite der Matrix
#define MATRIX_HEIGHT 8         // Höhe der Matrix
#define NUM_LEDS      (MATRIX_WIDTH * MATRIX_HEIGHT)


// ============================================
// Matrix-Layout
// ============================================
/*
 * LED 0 ist unten links am DIN-Pin
 * 
 * y=0 (oben):   (0,0) (1,0) (2,0) (3,0) (4,0) (5,0) (6,0) (7,0)  →  56  57  58  59  60  61  62  63
 * y=1:          (0,1) (1,1) (2,1) (3,1) (4,1) (5,1) (6,1) (7,1)  →  48  49  50  51  52  53  54  55
 * y=2:          (0,2) (1,2) (2,2) (3,2) (4,2) (5,2) (6,2) (7,2)  →  40  41  42  43  44  45  46  47
 * y=3:          (0,3) (1,3) (2,3) (3,3) (4,3) (5,3) (6,3) (7,3)  →  32  33  34  35  36  37  38  39
 * y=4:          (0,4) (1,4) (2,4) (3,4) (4,4) (5,4) (6,4) (7,4)  →  24  25  26  27  28  29  30  31
 * y=5:          (0,5) (1,5) (2,5) (3,5) (4,5) (5,5) (6,5) (7,5)  →  16  17  18  19  20  21  22  23
 * y=6:          (0,6) (1,6) (2,6) (3,6) (4,6) (5,6) (6,6) (7,6)  →   8   9  10  11  12  13  14  15
 * y=7 (unten):  (0,7) (1,7) (2,7) (3,7) (4,7) (5,7) (6,7) (7,7)  →   0   1   2   3   4   5   6   7
 *                                                                     ↑
 *                                                                    DIN
 * Verwendung: leds[XY(x, y)] = CRGB::Color;
 */

// ============================================
// Globale Variablen
// ============================================
CRGB leds[NUM_LEDS];                 // LED Array
CRGB currentColor = CRGB::Black;     // Aktuelle Farbe der Matrix
CRGB previousColor = CRGB::Black;    // Vorherige Farbe (für Hin-und-Her-Fades)
int hue = 0;

// ============================================
// Setup & Loop
// ============================================

void setup() {
  // Serielle Kommunikation initialisieren
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("  Luminaria - LED Matrix v1.0");
  Serial.println("=================================");
  Serial.println("Initialisierung läuft...");
  
  // FastLED initialisieren
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  Serial.println("✓ Matrix initialisiert");
  Serial.println("=================================");
}

void loop() {
  Fire(leds, 8, 8, 100,100);
}


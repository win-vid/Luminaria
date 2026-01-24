/*
 * ===============================================
 * LED Matrix Controller für CJMCU-8x8
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
 *   Steuerung einer 8x8 WS2812B LED Matrix (64 adressierbare LEDs)
 * 
 * ===============================================
 */

// Bibliotheken für WS2812B LED Matrix
#include <FastLED.h>          // Library: "FastLED" von Daniel Garcia et al. Fehler ignorieren VS kennt Bib nicht.

// Pin-Definitionen für ESP32-S3
#define LED_PIN     23        // DIN Pin (Datenleitung)
#define NUM_LEDS    64        // 8x8 = 64 LEDs
#define BRIGHTNESS  50        // Helligkeit (0-255)
#define LED_TYPE    WS2812B   // LED Typ
#define COLOR_ORDER GRB       // Farbordnung

// LED Array erstellen
CRGB leds[NUM_LEDS];

void setup() {
  // Serielle Kommunikation initialisieren
  Serial.begin(9600);
  Serial.println("Luminaria - LED Matrix wird initialisiert...");
  
  // FastLED initialisieren
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Testmuster: Alle LEDs rot anzeigen
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  
  Serial.println("Initialisierung abgeschlossen - Matrix sollte rot leuchten!");
}

void loop() {
  // Hauptprogramm hier einfügen
  
}

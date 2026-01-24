/*
 * ===============================================
 * Colours.ino - Farbdefinitionen
 * ===============================================
 */

// ============================================
// Standard FastLED Farben (Referenz)
// ============================================
/*
 * Von FastLED bereitgestellt (direkt nutzbar):
 * 
 * CRGB::AliceBlue           CRGB::Aqua              CRGB::Aquamarine
 * CRGB::Azure               CRGB::Beige             CRGB::Bisque
 * CRGB::Black               CRGB::Blue              CRGB::BlueViolet
 * CRGB::Brown               CRGB::BurlyWood         CRGB::CadetBlue
 * CRGB::Chartreuse          CRGB::Chocolate         CRGB::Coral
 * CRGB::Crimson             CRGB::Cyan              CRGB::DarkBlue
 * CRGB::DarkCyan            CRGB::DarkGoldenrod     CRGB::DarkGray
 * CRGB::DarkGreen           CRGB::DarkKhaki         CRGB::DarkMagenta
 * CRGB::DarkOliveGreen      CRGB::DarkOrange        CRGB::DarkOrchid
 * CRGB::DarkRed             CRGB::DarkSalmon        CRGB::DarkSeaGreen
 * CRGB::DarkSlateBlue       CRGB::DarkSlateGray     CRGB::DarkTurquoise
 * CRGB::DarkViolet          CRGB::DeepPink          CRGB::DeepSkyBlue
 * CRGB::DimGray             CRGB::DodgerBlue        CRGB::FireBrick
 * CRGB::ForestGreen         CRGB::Fuchsia           CRGB::Gold
 * CRGB::Goldenrod           CRGB::Gray              CRGB::Green
 * CRGB::GreenYellow         CRGB::HotPink           CRGB::IndianRed
 * CRGB::Indigo              CRGB::Ivory             CRGB::Khaki
 * CRGB::Lavender            CRGB::LawnGreen         CRGB::LightBlue
 * CRGB::LightCoral          CRGB::LightCyan         CRGB::LightGreen
 * CRGB::LightGrey           CRGB::LightPink         CRGB::LightSalmon
 * CRGB::LightSeaGreen       CRGB::LightSkyBlue      CRGB::LightSlateGray
 * CRGB::Lime                CRGB::LimeGreen         CRGB::Magenta
 * CRGB::Maroon              CRGB::MediumBlue        CRGB::MediumOrchid
 * CRGB::MediumPurple        CRGB::MediumSeaGreen    CRGB::MediumSlateBlue
 * CRGB::MediumSpringGreen   CRGB::MediumTurquoise   CRGB::MediumVioletRed
 * CRGB::MidnightBlue        CRGB::Navy              CRGB::Olive
 * CRGB::OliveDrab           CRGB::Orange            CRGB::OrangeRed
 * CRGB::Orchid              CRGB::Pink              CRGB::Plum
 * CRGB::Purple              CRGB::Red               CRGB::RoyalBlue
 * CRGB::SaddleBrown         CRGB::Salmon            CRGB::SandyBrown
 * CRGB::SeaGreen            CRGB::Sienna            CRGB::Silver
 * CRGB::SkyBlue             CRGB::SlateBlue         CRGB::SlateGray
 * CRGB::Snow                CRGB::SpringGreen       CRGB::SteelBlue
 * CRGB::Tan                 CRGB::Teal              CRGB::Thistle
 * CRGB::Tomato              CRGB::Turquoise         CRGB::Violet
 * CRGB::White               CRGB::Yellow            CRGB::YellowGreen
 * 
 * Verwendung: leds[0] = CRGB::Red;
 */

// ============================================
// Benutzerdefinierte Farben
// ============================================

/**
 * Warmweißes Licht Variante 1 (gemütlich, gelblich)
 */
CRGB getWarmWhite_I() {
  return CRGB(255, 245, 230);
}

/**
 * Warmweißes Licht Variante 2 (mittlere Wärme)
 */
CRGB getWarmWhite_II() {
  return CRGB(255, 235, 205);
}

/**
 * Warmweißes Licht Variante 3 (sehr warm, bernstein)
 */
CRGB getWarmWhite_III() {
  return CRGB(255, 220, 180);
}

/**
 * Kaltweißes Licht Variante 1 (neutral weiß)
 */
CRGB getColdWhite_I() {
  return CRGB(245, 254, 255);
}

/**
 * Kaltweißes Licht Variante 2 (leicht bläulich)
 */
CRGB getColdWhite_II() {
  return CRGB(208, 248, 249);
}

/**
 * Kaltweißes Licht Variante 3 (kühl, tageslicht)
 */
CRGB getColdWhite_III() {
  return CRGB(180, 230, 255);
}

// ============================================
// Farbpaletten-Hilfsfunktionen
// ============================================

/**
 * Gibt eine Regenbogenfarbe basierend auf Index zurück
 * @param index Farbindex (0-255)
 * @return Regenbogenfarbe
 */
CRGB getRainbowColor(uint8_t index) {
  return CHSV(index, 255, 255);
}

/**
 * Erstellt eine Farbe aus HSV-Werten
 * @param hue Farbton (0-255): 0=Rot, 64=Gelb, 96=Grün, 160=Blau, 192=Lila
 * @param saturation Sättigung (0-255): 0=Weiß, 255=Volle Farbe
 * @param value Helligkeit (0-255): 0=Schwarz, 255=Hell
 * @return CRGB Farbe
 */
CRGB colorFromHSV(uint8_t hue, uint8_t saturation, uint8_t value) {
  return CHSV(hue, saturation, value);
}

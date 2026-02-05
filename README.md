# Luminaria
LED-light control software.

## Setup
### Parts
* A controll unit, ideally an ESP32S3, or similair
* LED-Stripe / -Matrix

### Software & Packages
You need the Arduino IDE and the latest version of FastLED. You can install FastLED via the Arduino package manager.
Additionally, you need the latest version of the ESP32S3 Dev Module which can also be installed via the Arduino IDE.

### Installation
1. Copy this repo.

2. Upload LuminariaMain.ino in your Arduino IDE.

## FAQ
Q: Arduino IDE throws a timeout exception when I try to install the ESP32S3 Dev Module
A: The following solution applies to both windows- and linux systems. In your local file-system find the "arduino-cli.yaml" file. Open it and add the following:

network:
  connection_timeout: 300s

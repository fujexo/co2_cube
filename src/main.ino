#include <Wire.h>
#include <FastLED.h>
#include "SparkFun_SCD30_Arduino_Library.h"

#define DATA_PIN D0
#define NUM_LEDS 1

SCD30 airSensor;
CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    Serial.println("CO2 Cube");
    Wire.begin();

    if (airSensor.begin() == false) {
        Serial.println("Air sensor not detected. Please check wiring. Freezing...");
        while (1);
    }

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
    if (airSensor.dataAvailable()) {

        int co2_level = airSensor.getCO2();

        if (co2_level < 600) {
            leds[0] = CRGB::Blue;
        } else if (co2_level < 800) {
            leds[0] = CRGB::Green;
        } else if (co2_level < 1000) {
            leds[0] = CRGB::Green;
        } else if (co2_level < 1200) {
            leds[0] = CRGB::Yellow;
        } else if (co2_level > 1200) {
            leds[0] = CRGB::Red;
        }

        FastLED.show();

        Serial.print("co2(ppm):");
        Serial.print(co2_level);

        Serial.print(" temp(C):");
        Serial.print(airSensor.getTemperature(), 1);

        Serial.print(" humidity(%):");
        Serial.print(airSensor.getHumidity(), 1);

        Serial.println();
    }

   delay(1000);
}

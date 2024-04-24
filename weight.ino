#include <HX711.h>
const int DOUT_PIN = 19; // Connect to the data pin of HX711
const int SCK_PIN = 2;  // Connect to the clock pin of HX711

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale(-222);
  scale.tare();
}

void loop() {
Serial.print("Weight : ");
Serial.println(scale.get_units(10), 1);
scale.power_down();
delay(1000);
scale.power_up();
} 
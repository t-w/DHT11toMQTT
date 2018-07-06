#include <Arduino.h>

#include "Sensor.h"
#include "Publisher.h"

Sensor    sensor;
Publisher publisher;

void setup() {
  Serial.begin(115200);
  publisher.connect();
}

void loop() {

  byte temp, hum;

  temp = sensor.getTemperature();
  hum  = sensor.getHumidity();

  sensor.showData();

  publisher.publish(temp, hum);
  
  publisher.loop();

  // DHT11 sampling rate is 1HZ.
  delay(1000);
}
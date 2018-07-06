
#include "Sensor.h"

void Sensor::read()
{
  unsigned long now = millis();
  //Serial.println(now, DEC);
  if (now - last_read < 2000)
    return;

  last_read = now;

  // start working...
  //Serial.println("=================================");
  //Serial.println("Sample DHT11...");
  
  // read with raw sample data.
  temperature = 0;
  humidity    = 0;
  memset (data, dsize, sizeof(byte));

  if ( int result = dht11.read( pinDHT11, &temperature, &humidity, data ) ) {
    Serial.print( "Read DHT11 failed : " );
    Serial.println( result, DEC );
    //delay(2000);
    return;
  }
  
  //Serial.print( "Sample RAW Bits: " );
  /*for ( int i = 0; i < dsize; i++ ) {
    Serial.print( (int) data[i] );
    if (i > 0 && ( ( i + 1 ) % 4 ) == 0 ) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  */
  //Serial.print("Sample OK: ");
  //Serial.print((int)temperature); Serial.print(" *C, ");
  //Serial.print((int)humidity); Serial.println(" %");
}

void Sensor::showData(){
    static unsigned long last_shown = 0;
    if (last_shown == last_read)
        return;

    Serial.print("Sensor data timestamp:");
    Serial.print(last_read, DEC);Serial.print(" ");
    Serial.print( (int) temperature ); Serial.print(" *C, ");
    Serial.print( (int) humidity );    Serial.println(" %");
}

byte Sensor::getTemperature()
{
    read();
    return temperature;
}

byte Sensor::getHumidity()
{
    read();
    return humidity;
}
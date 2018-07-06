
#include <SimpleDHT.h>



class Sensor
{
    // for DHT11, 
    //      VCC: 5V or 3V
    //      GND: GND
    //      DATA: 2

    #ifdef __AVR
    const int pinDHT11 = 2;  //AtMega2560
    #else
    const int pinDHT11 = D2;  // ESP8266
    #endif


    SimpleDHT11 dht11;

    // read with raw sample data.
    const static int dsize  = 40;
    byte      temperature   = 0;
    byte      humidity      = 0;
    byte      data[ dsize ] = {0};

    const static int read_interval = 2000;
    unsigned long    last_read     = 0;

public:
    Sensor()
    { 
        dht11 = SimpleDHT11( pinDHT11 );
    }

    void showData();

    byte getTemperature();
    byte getHumidity();

private:
    void read();

};
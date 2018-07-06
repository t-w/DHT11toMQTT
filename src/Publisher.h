#include <ESP8266WiFi.h>
#include <PubSubClient.h>



class Publisher
{
    const char* ssid         = "WIFI";
    const char* password     =  "";

    const char* mqttServer   = "";
    const int   mqttPort     = 12345;
    const int   mqttSSLPort  = 12346;
    const char* mqttUser     = "user";
    const char* mqttPassword = "pass";

    WiFiClient   espClient;
    PubSubClient client;
    const int     interval   = 10000;
    unsigned long lastPub    = 0;

public:
    Publisher();

    void connect(void);
    void loop(void);
    void publish(byte temp, byte hum);

//private:
    //void callback(char* topic, byte* payload, unsigned int length);

};

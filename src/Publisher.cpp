#include "Publisher.h"


void callback(char* topic, byte* payload, unsigned int length);


Publisher::Publisher() {
    client = PubSubClient( espClient);
}


void Publisher::connect(void)
{
    // Nework (WiFi)
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
        Serial.print("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    // MQTT
    client.setServer( mqttServer, mqttPort );
    client.setCallback( callback );

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
            Serial.println("connected");  
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    client.subscribe("esp/test");
    client.subscribe("esp/temperature");
    client.subscribe("esp/humidity");
}

void Publisher::loop(void)
{
    client.loop();
}


void Publisher::publish(byte temperature, byte humidity)
{
    // publishing frequency 10s
    unsigned long now = millis();
    if ( now - lastPub < 10000)
        return;
    lastPub = now;

    //client.publish("esp/test", "Hello from ESP8266");
    
    char buf[32];
    snprintf( buf, sizeof(buf), "timestamp: %d Temp: %d deg. C", now, temperature );
    client.publish( "esp/temperature", buf );

    snprintf( buf, sizeof(buf), "timestamp: %d Humidity: %d", now, humidity );
    client.publish( "esp/humidity", buf );
}


void callback(char* topic, byte* payload, unsigned int length)
{

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for ( unsigned int i = 0; i < length; i++ ) {
        Serial.print( (char) payload[ i ] );
    }

    Serial.println();
    Serial.println("-----------------------");

}

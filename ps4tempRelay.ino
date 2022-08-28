#include <ESP8266WiFi.h>
#include "DHT.h"
#include <SimpleTimer.h> 

#define DHTTYPE DHT11
#define dht_dpin D4
#define relay_dpin D1

DHT dht(dht_dpin, DHTTYPE); 

SimpleTimer timer;

float maxTemp = 30.0;
float currTemp = 0.0;

void setup()
{
    Serial.begin(9600);
    pinMode(relay_dpin, OUTPUT);
    dht.begin();
    timer.setInterval(2000, getTemp);
    timer.setInterval(4000, relayControl);
}

void loop()
{
  timer.run();
}

void getTemp()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  currTemp = t;
}

void relayControl()
{
  if(currTemp > maxTemp){
    digitalWrite(relay_dpin, HIGH);
    Serial.print("HIGH");
  }else {
    digitalWrite(relay_dpin, LOW);
    Serial.print("LOW");
  }
}

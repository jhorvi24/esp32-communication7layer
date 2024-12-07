#include <DHT.h>
#include <DHT_U.h>
#include <WiFiClientSecure.h>
#include "credentials.h"

const char* ssid = "ssid";
const char* password = "password";

//const char* server = "192.168.1.20";

#define dhtpin 14
#define DHTTYPE DHT11
#define led 2

WiFiClientSecure client;
DHT dht(dhtpin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  //pinMode(11, INPUT);
  Serial.begin(9600);
  dht.begin();
  pinMode(led, OUTPUT);

  
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

    // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.println("WiFi connected");
  Serial.println("Connected to IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connected to ");
  Serial.println(ssid);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    WiFi.begin(ssid, password);
  }

  Serial.println("WiFi connected");
  Serial.println("Connected to IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  if (t>=33){
    digitalWrite(led, HIGH);    
  }else{
    digitalWrite(led, LOW);
  }

}
#include <DHT.h>
#include <DHT_U.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include "credentials.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char* server = "server Address";
const int httpsPort = 443;
const char* Endpoint = "/data";

//IPAddress server(35, 175, 188, 98);

#define dhtpin 14
#define DHTTYPE DHT11
#define led 2


float h;
float t;

WiFiClientSecure client;


DHT dht(dhtpin, DHTTYPE);





void setup() 
{
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

  client.setInsecure(); //ignore ssl/tls certificate errors


  



}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    WiFi.begin(ssid, password);
  }

  Serial.println("WiFi connected");
  Serial.println("Connected to IP address: ");
  Serial.println(WiFi.localIP());

 

  delay(2000);

  h = dht.readHumidity();
  t = dht.readTemperature();

  

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

if (client.connect(server, httpsPort)) {
  Serial.println("Connected to server");
  String postData = "humidity=" + String(h) + "&temperature=" + String(t);  
  client.println("POST " + String(Endpoint) + " HTTP/1.1");  
  client.println("Host: " + String(server));  
  client.println("Content-Type: application/x-www-form-urlencoded");  
  client.println("Connection: close");  
  client.println("Content-Length: " + String(postData.length()));  
  client.println();  
  client.println(postData);  
  

  while (client.connected() || client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received, response:");
      } else {
        Serial.println(line);
        }
        }
  client.stop();
  Serial.println("Data sent and connection closed");  

}else {
  Serial.println("Connection failed to server");
}  

  

  if (t>=33){
    digitalWrite(led, HIGH);    
  }else{
    digitalWrite(led, LOW);
  }

}

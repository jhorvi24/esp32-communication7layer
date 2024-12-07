#include <DHT.h>
#include <DHT_U.h>

#define dhtpin 14
#define DHTTYPE DHT11


DHT dht(dhtpin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  //pinMode(11, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

}
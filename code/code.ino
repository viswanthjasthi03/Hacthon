#define pir D4
#define TrigPin D3
#define EchoPin D2
#define buzzer D1
int x,distance,duration;
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "xxxxxxxx";   // your network name
char pass[] = "xxxxxxxx";   // your network password
WiFiClient  client;

unsigned long myChannelField= 1495929;               //my Channel id
const int ChannelField = 1;                           //Channel Field 1  
const int ChannelField1 = 2;                           //Channel Field 2
const char * myWriteApIKey = "IA1W4NN37U9E60B8";     //write API key 

void setup() {
pinMode(pir,INPUT);
pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(buzzer, OUTPUT);
Serial.begin(9600);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
}

void loop() {
if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("\nAttempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print("Connecting...\n");
      delay(5000);
    }
  Serial.println("\nConnected.");
  }
x = digitalRead(pir);
/*Serial.print("PIR value is:");
Serial.print(x);
Serial.print("\n");*/
digitalWrite(TrigPin,LOW);
delayMicroseconds(2);
digitalWrite(TrigPin,HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin,LOW);
duration = pulseIn(EchoPin,HIGH);
distance = duration * 0.034/2;
if( x == 1)
{
 Serial.print("Human Detected at a distance of ");
 Serial.print(distance);
 Serial.print("\n");
}
else
{
  Serial.print("No Human Detected\n");
}
if(distance<25 && x == 1)
{
  digitalWrite(buzzer, HIGH);
}
else
{
  digitalWrite(buzzer, LOW);
}
if(isnan(x))
{
  Serial.print("Failed to read from the sensor");
  return;
}
ThingSpeak.writeField(myChannelField, ChannelField, x, myWriteApIKey);
ThingSpeak.writeField(myChannelField, ChannelField1, distance, myWriteApIKey);
delay(3000);
}

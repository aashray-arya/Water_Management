#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#define LED_BUILTIN 13
#define W_METER  14 //D5
#define SV 12 //D6
#define W_SENSOR  A0

long currentMillis = 0;
long previousMillis = 0;
long pM = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.8;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
float totalLitres;
int b;
int a;
int inte = 5000;
unsigned long timeout;

const String ESPId = "02";

// WiFi
const char* ssid = "Virus";              // Your personal network SSID
const char* wifi_password = "anjalian"; // Your personal network password

String apiKeyValue = "tPmAT5Ab3j7F9";
const char server[] = "f8techsol.io"; // domain name: example.com, maker.ifttt.com, etc
const char resource[] = "/post-data_v2.php";         // resource path, for example: /post-data.php
const int  port = 80;

// Initialise the WiFi and MQTT Client objects
WiFiClient client;


void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

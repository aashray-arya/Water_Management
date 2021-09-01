#include <Wire.h>
#include "PubSubClient.h"
#include "WiFi.h"

#define LED_BUILTIN 13
#define W_SENSOR  2
#define SV 26


long currentMillis = 0;
long previousMillis = 0;
long pM = 0;
int interval = 500;
boolean ledState = LOW;
float calibrationFactor = 2.6;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned long flowMilliLitres;
unsigned int totalMilliLitres;
float flowLitres;
float totalLitres;
int b;
int inte = 4000;


// WiFi
const char* ssid = "Virus";              // Your personal network SSID
const char* wifi_password = "anjalian"; // Your personal network password

//MQTT
const char* mqtt_server = "192.168.1.33";  // IP of the MQTT broker
const char* Wsensor_topic = "WaterM/HallSensor";
const char* solenoid_topic = "WaterM/SensorState";
const char* mqtt_username = "aash"; // MQTT username
const char* mqtt_password = "aash"; // MQTT password
const char* clientID = "client_water"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);


void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

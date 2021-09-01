#define TINY_GSM_MODEM_SIM800      // Modem is SIM800
#define TINY_GSM_RX_BUFFER   1024  // Set RX buffer to 1Kb


#include <Wire.h>
#include <TinyGsmClient.h>


#define LED_BUILTIN 13
#define W_METER  2
#define W_SENSOR 12
#define SV 15

// TTGO T-Call pins
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22


#define SerialMon Serial
#define SerialAT Serial1

#define TINY_GSM_MODEM_SIM800      // Modem is SIM800
#define TINY_GSM_RX_BUFFER   1024  // Set RX buffer to 1Kb

// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS


#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TwoWire I2CPower = TwoWire(0);
#define uS_TO_S_FACTOR 1000000UL   /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  3600        /* Time ESP32 will go to sleep (in seconds) 3600 seconds = 1 hour */

#define IP5306_ADDR          0x75
#define IP5306_REG_SYS_CTL0  0x00

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
int b=0;
int inte = 4000;

//GSM
const char apn[]      = "airtelgprs.com"; // Your APN
const char gprsUser[] = ""; // User
const char gprsPass[] = ""; // Password
const char simPIN[]   = ""; // SIM card PIN code, if any

const String ESPId="01";

//Server details
String apiKeyValue = "tPmAT5Ab3j7F9";
const char server[] = "f8techsol.io"; // domain name: example.com, maker.ifttt.com, etc
const char resource[] = "/post-data.php";         // resource path, for example: /post-data.php
const int  port = 80;

TinyGsmClient client(modem);


void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

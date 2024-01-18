//#include <stdlib.h>

//MQTT Lib
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//DHT11 Libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//BMP180 Libraries
#include <Wire.h> //I2C Protocol
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

//HP_BH1750 Libraries
#include <hp_BH1750.h>

//Macros
#define DHTPIN 14 //GPIO number
#define DHTTYPE DHT11 //1-wire Protocol
#define DELAY_BETWEEN_SAMPLES_MS 2000 //Update Time

//Instantiate Sensor Objects
DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
hp_BH1750 BH1750;

//Setup Global Variables
char* ssid = "Suite1415";
char* pass = "88467212ZhengHua";
const char* brokerAddress = "test.mosquitto.org";
uint16_t addressPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


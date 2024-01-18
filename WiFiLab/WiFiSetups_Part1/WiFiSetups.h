//#include <stdlib.h>

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

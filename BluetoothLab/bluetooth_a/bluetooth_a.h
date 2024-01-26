//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <AsyncAPDS9306.h>

//IIC Addresses for Temperature Sensor
#define ADDR (byte)(0x40)
#define TMP_CMD (byte)(0xF3)
#define HUM_CMD (byte)(0xF5)

//Sample frequency
#define DELAY_BETWEEN_SAMPLES_MS 3000

//Device information
String group_name = "Zhenghua Wu";
String device_name = "Bluetooth lab";

//Instantiating sensor object and configuration
AsyncAPDS9306 light_sensor;
const APDS9306_ALS_GAIN_t apds_gain = APDS9306_ALS_GAIN_1;
const APDS9306_ALS_MEAS_RES_t apds_time = APDS9306_ALS_MEAS_RES_16BIT_25MS;

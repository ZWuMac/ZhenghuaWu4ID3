#include "WiFiSetups.h"

void setup() {
  //Start the serial monitor at 115200 baud
  Serial.begin(115200); 

  //Create a sensor object that is passed into the getSensor method of the dht class
  //Only the dht sensor requires this
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  //Run the begin()method on each sensor to start communication
  dht.begin(); //Moisture
  bmp.begin(); //Pressure
  BH1750.begin(BH1750_TO_GROUND); //Light

}

void loop() {
  //Polling the DHT and BMP sensor using events
  sensors_event_t dhtTempEvent, dhtHumEvent, bmpEvent;
  dht.temperature().getEvent(&dhtTempEvent);
  dht.humidity().getEvent(&dhtHumEvent);
  bmp.getEvent(&bmpEvent);

  //Polling the BH sensor
  BH1750.start(); 
  float lux=BH1750.getLux(); 

  //Printing sensor readings to serial monitor
  Serial.println("\n-");

  if (!isnan(dhtTempEvent.temperature)){
     Serial.println("Temperature: " + String(dhtTempEvent.temperature) + " degC");
  }else{
     Serial.println("Temperature Sensor Disconnected");
  } //Display Temp
    
  if (!isnan(dhtHumEvent.relative_humidity)){
     Serial.println("Humidity: " + String(dhtHumEvent.relative_humidity) + " %");
   }else{
    Serial.println("Humidity Sensor Disconnected");
   } //Display Hum

  if (!isnan(bmpEvent.pressure)){
    Serial.println("Pressure: " + String(bmpEvent.pressure) + " hPa");
  }else{
    Serial.println("Pressure Sensor Disconnected");
  } //Display pres

  if (!isnan(lux)){
    Serial.println("Light Intensity: " + String(lux) + " lux");
  }else{
    Serial.println("Lux Sensor Disconnected");
  } //Display brightness

   delay(DELAY_BETWEEN_SAMPLES_MS);

   //system("CLS");
}

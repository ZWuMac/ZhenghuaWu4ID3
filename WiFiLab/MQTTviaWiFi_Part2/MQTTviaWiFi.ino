#include "WiFiSetups.h"

void setup() {
  //Start WiFi connection
  WiFi.begin(ssid, pass);

  //Print network info once connected
  Serial.print("\n");
  Serial.print("WiFi connected. IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");

  client.setServer(brokerAddress, addressPort);

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

    //Connection checks
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

//Callback function in case of connection failure
void reconnect(){
  while(!client.connected()){
    Serial.print("MQTT connection lost. Attempting to reconnect...");
    if (client.connect("ZWuClient")){
      Serial.print("Connection successful");
      client.subscribe("testTopic");
    }else{
      Serial.print("Failed to reconnect, rc = ");
      Serial.print(client.state());
      Serial.print("\n");
      delay(2000);
    }
  }
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

   //system("CLS");

   //Publishing data through MQTT
   if(!client.loop()){
    client.connect("ZWuClient");
   }

   client.publish("recordedTemperature", String(dhtTempEvent.temperature).c_str());
   delay(200);
   client.publish("recordedHumidity", String(dhtHumEvent.relative_humidity).c_str());
   delay(200);
   client.publish("recordedPressure", String(bmpEvent.pressure).c_str());
   delay(200);
   client.publish("recordedBrightness", String(lux).c_str());

   delay(DELAY_BETWEEN_SAMPLES_MS);
}
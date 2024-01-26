#include "bluetooth_a.h"

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------\n  ZhenghuaWu  Lab4ID3  \n------------------------\n\n"); 

  Wire.begin();
  Wire.beginTransmission(ADDR);
  Wire.endTransmission();
  delay(300);
  
  light_sensor.begin(apds_gain, apds_time);
  
}

void loop() {
  Wire.beginTransmission(ADDR);
  Wire.write(TMP_CMD);
  Wire.endTransmission();
  delay(200);

  Wire.requestFrom(ADDR, 2);

  char dataT[2];
  if(Wire.available() == 2){
    dataT[0] = Wire.read();
    dataT[1] = Wire.read();
  }

  float temp = ((dataT[0] * 256.0) + dataT[1]);
  float temp_c = ((175.72 * temp) / 65536.0) - 46.85;

  Wire.beginTransmission(ADDR);
  Wire.write(HUM_CMD);
  Wire.endTransmission();
  delay(200);

  Wire.requestFrom(ADDR, 2);

  char dataH[2];
  if(Wire.available() == 2){
    dataH[0] = Wire.read();
    dataH[1] = Wire.read();
  }

  float humd = ((dataH[0] * 256.0) + dataH[1]);
  humd = ((125.0 * humd) / 65536.0) - 6;

  AsyncAPDS9306Data light_data = light_sensor.syncLuminosityMeasurement();
  float lux = light_data.calculateLux();

  String formatted_data = group_name + ", " 
  + device_name + ": " + "Temperature(degC): " 
  + temp_c + "; %Humidity: " + humd 
  + "; Brightness(lux): " + lux + "\n";
      
  Serial.println(formatted_data);
  
  delay(DELAY_BETWEEN_SAMPLES_MS);

}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

//Setup connection of the sensor
Adafruit_BMP280 bmp;  //I2C
 
//Variables
float pressure;    //to store barometric pressure
float temperature; //to store temperature
int altimeter;     //to store altimeter (m) 

void setup(){
  bmp.begin();
  Serial.begin(9600);
  Serial.println("Adafruit BMP280 Test:");
}

void loop(){
  //Read values from the sensor
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  altimeter = bmp.readAltitude (30.43); //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)
  
  //Print values to serial monitor:
  Serial.print(F("Pressure: "));
  Serial.print(pressure);
  Serial.print(" PA");
  Serial.print("  ");
  Serial.print(("Temp: ");
  Serial.print(temperature);
  Serial.print(" oC");
  Serial.print("  ");
  Serial.print("Altimeter: ");
  Serial.print(altimeter); // this should be adjusted to your local forcase
  Serial.print(" m");
  
  delay(5000); //update every 5 seconds
}


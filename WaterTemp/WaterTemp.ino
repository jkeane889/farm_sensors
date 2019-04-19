/*Using the DS18B20 sensor.  Need to connect a resistor with a value from about 4.7 K to 10 K between the red and yellow wires in addition
to connecting these wires to the 5 V and the input connection.  If you do not include this resistor, or if any of the connections are loose,
the sensor will always read negative 175 C, regardless of the temperature */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  //this will be the input for the yellow wire of the sensor (you can select any digital pints as input)
#define HeaterPin 13
#define CoolerPin 12
const float upperLimit = 85;
const float lowerLimit = 40;
float tempC;
float tempF;

OneWire oneWire(ONE_WIRE_BUS);  //sets the input to the pin which ONE_WIRE_BUS was set to
DallasTemperature sensors(&oneWire);  //defines sensors for the DallasTemperature function

void setup(void){
  pinMode(HeaterPin, OUTPUT);
  digitalWrite(HeaterPin, LOW);
  pinMode(CoolerPin, OUTPUT);
  digitalWrite(CoolerPin, LOW);
  sensors.begin;  //activates the reading of the sensors; merely opens the channel to them
  Serial.begin(9600);
} //end of setup

/* Notice the "0" for sensors.getTempCByIndex...the OneWire library allows you to connect more than one sensor to the same input pin.  If you have more than one,
the second one would be "sensors.getTempCByIndex(1)," the third would be "sensors.getTempCByIndex(2)" and so on. */

void loop(void){
  sensors.requestTemperatures();  //loads the temperature readings into variables
  tempC = sensors.getTempCByIndex(0); //loads the value of variable sensors.getTempCByIndex(0) into variable tempC
  tempF = (tempC * 1.8) + 32;
  Serial.print("Temperature= ");
  Serial.println(tempF);
  if(tempF < lowerLimit){
    digitalWrite(HeaterPin, HIGH);
    }
  if(tempF > lowerLimit + 3){
    digitalWrite(HeaterPin, LOW);
    }
  if(tempF > upperLimit){
    digitalWrite(CoolerPin, HIGH);
    }
  if(tempF < upperLimit - 3){
    digitalWrite(CoolerPin, LOW)'
  }
  delay(1000);
} //end of loop

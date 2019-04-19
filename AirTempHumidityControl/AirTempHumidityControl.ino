//A sketch to turn on heater or cooler depending on air temperature
// if you would like the readings to be sent to the Arduino IDE, you must put the command "Serial.being(9600)" in the Setup routine
// then you put commands: "Serial.print("Temperatuer=")" and "Serial.println(tempF)" in the code anywhere you want the information to be displayed
// in the serial monitor box
// In this sketch you could add these two lines immediately after the line " tempF = (tempC * 1.8) + 32;" . This will display the reading to the serial monitor.

#include <dht.h>
dht DHT;

const int relayPin = 13; //pin to control the pump
const int inputPin = 7;  //selected input pin for the temperature and humidity

/*Below we are setting limits for humidity in addition to temperature.  We are setting two limits for each.  This will allow you to adjust
the off periods of the pump for three different conditions: (1) over 80 degrees F, between 80 and 90 degrees F, and over 90 degrees.  You
can set as many of these trip points as you would like. */

const float TemperatureUpperLimit1 = 80;//floats are more accurate when converting from Fahrenheit to Celsius and vice versa
const float HumidityLowerLimit1 = 40;
const float TemperatureUpperLimit2 = 90;
const float HumidityLowerLimit2 = 35;

//initial state of relay is on is FALSE
bool PowerOn = false;
float tempC;
float tempF;
float HumidityReading;

//how long power is on and off in minutes
int TimeOff = 75;
int TimeOn = 15;

long PreviousTime = 0;
int TimePassed = 0;

void setup(){
  //set the digital pins as output and start out as off:
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);
}

void loop(){
  int TimeOff = 75;
  int error = DHT.read11(inputPin); 
  //if the value is 0, there was no error and the temperature and humidity have been recorded correctly.
  //Values such as -1 and -2 are returned for errors such as checksum error and timeout
  //if the data had an error, the loop below simply repeats until good data is obtained
  if(error == 0){ 
    tempC = DHT.temperature;
    tempF = (tempC * 1.8) + 32;
    HumidityReading = DHT.humidity;
    if (tempF > TemperatureUpperLimit1 && HumidityReading < HumidityLowerLimit1){ //checking to see if temp/humidity cross the first barrier for adverse conditions
      TimeOff = 60; //if the conditions above are true, if then lower the time off to cool
     }
    if(tempF > TemperatureUpperLimit2 && HumidityReading < HumidityLowerLimit2) { //checks again to see if temp/humidity have crossed the second barrier (worst conditions)
      TimeOff = 45;
     }
  }
  Serial.print("Temp = ");
  Serial.print("  ");
  Serial.print(tempF);
  Serial.print("Hum = ");
  Serial.print("  ");
  Serial.print(HumidityReading);
  Serial.print("Time = ");
  Serial.print("  ");
  Serial.println(TimeOff);
  
  if(millis() < PreviousTime){PreviousTime = 0;}
  if(millis() - PreviousTime >= 60000){
    TimePassed = TimePassed + 1;
    PreviousTime = millis();
  }
  
  if(PowerOn){
    if(TimePassed >= TimeOn){
      digitalWrite(relayPin, LOW);
      TimePassed = 0;
      PowerOn = false;
    }
  }  //end if power on
  
  if(!PowerOn){
    if(TimePassed >= TimeOff){
      digitalWrite(relayPin, HIGH);
      TimePassed = 0;
      PowerOn = true;
    }
  } //end of power not on
  delay(2000);
}//end of loop
        

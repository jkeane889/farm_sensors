/* This sketch is for the method discussed on pages88 through 92 of the Arduino
Kindle Book.  Will require alumimum baking nails or some other kind of stainless 
steel, rust resistant metal to be put into the soil 

In order to determine the "Too Dry" integer amount, use the testing instrument on a drier day 
and plug in your Arduino to run this program to determine what the value returned is and make
the "Too Dry" amount equal to that dry level.
*/

#include <EEPROM.h> //A library which allows you to store values in the Arduino's permanent memory

#define AddWaterPin 13//the pin to the relay that will turn on a pump or valve to add water
#define SetPin 12 //this is the pin you will briefly connect to ground to store the Too Dry level.
#define PowerPin1 3
#define PowerPin2 2

int TooDry = 5000; //currently set at maximum level
//Number of seconds to water the plant
unsigned long WaterTime = 30;
//Number of seconds between tests (300 = 5 minutes)
unsigned long TestInterval = 300;
unsigned long LastTest = 0;
bool WaterOn = false;
int MoistureLevel;
unsigned long StartTime;
unsigned long currentTime;

//Need changes starting here
void setup(){
  pinMode(AddWaterPin, OUTPUT);
  digitalWrite(AddWaterPin, LOW);
  pinMode(SetPin,INPUT_PULLUP);
  pinMode(PowerPin1, OUTPUT);
  digitalWrite(PowerPin1, LOW);
  pinMode(PowerPin2, OUTPUT);
  digitalWrite(PowerPin2, LOW);
  Serial.begin(9600);
  if(EEPROM.read(2) == 11){            //this line reads the value of memory location 2; if this equals 11, this indicates the value of TooDry has been saved from previous run of Arduino.
    Serial.println("LoadingTooDry");
    byte high = EEPROM.read(0);
    byte low = EEPROM.read(1);
    TooDry = (high << 8) + low;
    Serial.print("TooDry= ");
    Serial.println(TooDry)
  }  
} //End setup

void loop(){
  currentTime = millis();
  if(LastTest > currentTime){
    LastTest = 0;
    }
  if(digitalRead(SetPin) == LOW){
    GetReading();  //subroutine below main loop being called; saves memory instead of typing out this procedure twice
    TooDry = MoistureLevel;  //detects when you have pin 12 connected to ground; then returns code from the subroutine
    EEPROM.write(0, highByte(TooDry)); //stores the value of TooDry in the permanent memory on locations 0 and 1
    EEPROM.write(1, lowByte(TooDry));
    EEPROM.write(2, 11);  
    Serial.print("Too dry level set");
  }
    
  if(currentTime - LastTest > TestInterval * 1000){
    digitalWrite(PowerPin1, HIGH);
    delay(500);
    MoistureLevel = analogRead(A0);
    digitalWrite(PowerPin1, LOW);
    digitalWrite(PowerPin2, HIGH);
    delay(500);
    digitalWrite(PowerPin2, LOW);
    Serial.print("Moisture=");
    Serial.println(MoistureLevel);
    if(MoistureLevel > TooDry){
      digitalWrite(AddWaterPin, HIGH);
      StartTime = currentTime;
      WaterOn = true;
      }
      LastTest = currentTime;
    }
    if(WaterOn){
      if(StartTime > currentTime){
        StartTime = 0;
      }
      if(currentTime - startTime > WaterTime * 1000){
        digitalWrite(AddWaterPin, LOW);
        WaterOn = false;
      }
    }
} //End main loop

void GetReading(){
  digitalWrite(PowerPin1, HIGH);
  delay(500);
  MoistureLevel = analogRead(A0);
  digitalWrite(PowerPin1, LOW);
  digitalWrite(PowerPin2, HIGH);
  delay(500);
  digitalWrite(PowerPin2, LOW);
  Serial.print("Moisture=");
  Serial.println("MoistureLevel);
} 
    
    
    
    
    
    
    

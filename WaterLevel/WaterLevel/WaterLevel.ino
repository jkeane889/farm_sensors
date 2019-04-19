/*

Popular method to monitor water levels is to have a sonic range finder pointed at the water and have it monitor the distance from the
range finder to the top of the water.  Advantages are that it is not submerged in water and will return an accurate reading. 

The ultrasonic range finder occasionally gives a false reading due to vibrations, wind, electrical surges, or other random events.  These instances could cause the DrainPin or AddWaterPin
to activate.  The solution to this is to require several high or low water readings in a row before a pin is set HIGH.

*/

#define DrainPin 13
#define AddWaterPin 12
#define echoSensorPin 7
#define triggerPin 8
const float LowWaterDistance = 14;
const float HighWaterDistance = 6;
float Duration, Distance; //"Duration" is the time between a sound pulse being sent out by the sensor and the time it returns.  "Distance" is the distance measured (can be measured in in or cm).

unsigned long TooHighCount = 0;
unsigned long NotTooHighCount = 0;
unsigned long TooLowCount = 0;
unsigned long NotTooLowCount = 0;

bool Draining = false;
bool Adding = false;
int MinCount = 4;

void setup(){
  Serial.begin(9600);
  pinMode(echoSensorPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(DrainPin, OUTPUT);
  digitalWrite(DrainPin, LOW);
  pinMode(AddWaterPin, OUTPUT);
  digitalWrite(AddWaterPin, LOW);
} //end setup

void loop(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);  //this process with triggerPin is how to send sound pulses to be received.
  Duration = pulseIn(echoSensorPin, HIGH); //this variable gets the amount of time it took for the pulse to be bounced back.
  Distance = (Duration / 2)/74; //calculation to convert timer interval to distance in inches (can multiple this by 2.54 if cm desired).
  Serial.print("Distance= ");
  Serial.println(Distance);
  
  if(Distance < HighWaterDistance){
    TooHighCount++;
    if(TooHighCount >= MinCount){  //when this condition is true, the code sets DrainPin high
      digitalWrite(DrainPin, HIGH);
      Draining = true;
      }
    } //end of if (distance < HighWaterDistance)
  else {
    TooHighCount = 0;
  }
  
  if(Distance > HighWaterDistance + 1 && Draining){
    NotTooHighCount++;
    if(NotTooHighCount >= MinCount){
      digitalWrite(DrainPin, LOW);
      Draining = false;
      }
    }  //end of if(Distance > HighWaterDistance _ 1)
   else {
     NotTooHighCount = 0;
   }
   
   if(Distance > LowWaterDistance){
     TooLowCount++;
     if(TooLowCount >= MinCount){
       digitalWrite(AddWaterPin, HIGH);
       Adding = true;
       }
     }  //end of if (Distance > LowWaterDistance
   else {
     TooLowCount = 0;
   }
   
   if(Distance < LowWaterDistance - 1 && Adding){
     NotTooLowCount++;
     if(NotTooLowCount >= MinCount){
       digitalWrite(AddWaterPin, LOW);
       Adding = false;
       }
     } //end of if(Distance < LowWaterDistance - 1)
    else {
      NotTooLowCount = 0;
    }
    delay(500);
} //end main loop
   

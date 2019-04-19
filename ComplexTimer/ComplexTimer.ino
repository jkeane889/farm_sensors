//More complex timer
//the number of the relay pin
const int relayPin = 13;
//initial state of relay is on is false
bool PowerOn = false;
//How long power is on and off in minutes
int TimeOff = 75;  //expressed as minutes..to be set by however many minutes you want off
int TimeOn = 15;  //expressed as minutes..to be set by however many minutes you want on

unsigned long PreviousTime = 0; //equivalent to StartTime from SimpleTimer sketch
unsigned long TimePassed = 0;

void setup(){
  //set the digital pin as output and start out as off:
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop(){
  if(millis() < PreviousTime){PreviousTime = 0;} //handles the roll over after 49 days have passed and the function millis resets to 0.
  if(millis() - PreviousTime >= 60000){  //is the equivalent of the minute hand on a clock advancing every time the second hand completes a revolution.
    TimePassed = TimePassed + 1;
    PreviousTime = millis();
  }
  if(PowerOn){
    if(TimePassed >= TimeOn){
      digitalWrite(relayPin, LOW);
      TimePassed = 0;
      PowerOn = false;
    }
  } //End of PowerOn
  if(!PowerOn){
    if(TimePassed >= TimeOff){
      digitalWrite(relayPin, HIGH);
      TimePassed = 0;
      PowerOn = true;
    }
  } //End of if power not on
} //end of loop

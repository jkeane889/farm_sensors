//Simple timer
//the number of the relay pin
const int relayPin = 13;
//Store start of timing
unsigned long startTime = 0;
unsigned long currentTime = 0;
//initial state of relay is on is false
bool PowerOn = false;

//How long power is on and off in minutes
long timeOff = 75 * 60 *1000;
long timeOn = 15 * 60 *1000;

void setup() {
  //set the digital pin as output and start out as off:
  pinMode(relayPin, OUTPUT); //each pin can either be input or output
  digitalWrite(relayPin, LOW); //sending a value of HIGH owuld cause this output to go to 5 volts
}

void loop() {
  currentTime = millis(); //millis gives the current number of milliseconds the Arduino has been running
  if (startTime > currentTime){
    startTime = 0;
  }  //since millis can only go 49.5 days, this will reset the start time to 0 also.
  if(PowerOn){
    if(currentTime - startTime > timeOn) //tests the time...if current time minus start time is greater than minutes you have set for the power to be on, goes to FALSE.
      digitalWrite(relayPin, LOW);
      startTime = currentTime;
      PowerOn = false;
    }
  }//End of PowerOn
  if(!PowerOn){ //if the Power is not currently on, execute
    if(currentTime - startTime > timeOff){ //if startTime and currentTime is greater than timeOff, the relay should then be off.
      digitalWrite(relayPin, HIGH);
      startTime = currentTime;
      PowerOn = true;
    }
  }//End of if power not on
} //end of loop

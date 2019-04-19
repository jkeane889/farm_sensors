//Double Timer
//the number of relay pins
const int relayPin = 13;
const int relayPin = 12;
//intial states of relays are off
bool PowerOn = false;
bool PowerOn2 = false;
//How long power is on and off in minutes
int TimeOff = 75;
int TimeOn = 13;
int TimeOff2 = 720;
int TimeOn2 = 720;
long PreviousTime = 0;
int TimePassed = 0;
int TimePassed2 = 0;

void setup() {
  //set the digital pin as output and start out as off:
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(relayPin2, OUTPUT);
  digitalWrite(relayPin2, LOW);
}

void loop(){
  if(millis() < PreviousTime){PreviousTime = 0;}
  if(millis() - PreviousTime >= 60000){
    TimePassed = TimePassed + 1;
    TimePassed2 = TimePassed2 + 1;
    PreviousTime = millis();
  }
  
  if(PowerOn){
    if(TimePassed >= TimeOn){
      digitalWrite(relayPin,LOW);
      TimePassed = 0;
      PowerOn = false;
    }
  } //End of if PowerOn
  
  if(!PowerOn){
    if(TimePassed >= TimeOff){
      digitalWrite(relayPin, HIGH);
      TimePassed = 0;
      PowerOn = true;
    }
  } //End of if power not on
  
  if(PowerOn2){
    if(TimePassed2 >= TimeOn2){
      digitalWrite(relayPin2, LOW);
      TimePassed2 = 0;
      PowerOn2 = false;
    }
  } //End of if PowerOn
  if(!PowerOn2){
    if(TimePassed 2 >= TimeOff2){
      digitalWrite(relayPin2, HIGH);
      TimePassed2 = 0;
      PowerOn2 = true;
    }
  } //End of power not on
} //end of loop

  

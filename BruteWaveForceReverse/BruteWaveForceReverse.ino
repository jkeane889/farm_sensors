int bluePin = 2;
int pinkPin = 3;
int yellowPin = 4;
int orangePin = 5;

//Keeps track of the current step
//Using a zero based index

int currentStep = 0;

boolean clockwise = true;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(bluePin, OUTPUT);
  pinMode(pinkPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  
  digitalWrite(bluePin, LOW);
  digitalWrite(pinkPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(orangePin, LOW);
  
}

void loop() {
  
  int directionStep = clockwise ? currentStep : (4-1)-currentStep;
  
  switch(directionStep){
    case 0:
      digitalWrite(bluePin, HIGH);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, LOW);
      break;
     case 1:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, LOW);
      break;
     case 2:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(orangePin, LOW);
      break;
     case 3:
      digitalWrite(bluePin, LOW);
      digitalWrite(pinkPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(orangePin, HIGH);
      break;
  }
   
  delay(2);
}


const int analogPin=A0; //the A0 of the module attach to A0
const int digitalPin=7; //Do attach to pin7
const int ledPin=13; //pin 13 built-in led
int Astate=0; //store the value of A0
boolean Dstate=0; //store the value of D0

void setup(){
  pinMode(ledPin,OUTPUT); //set the ledPin as output
  pinMode(digitalPin,INPUT); //set digitalPin as input
  Serial.begin(9600); //initalize the serial monitor
}

void loop(){
  Astate=analogRead(analogPin); //read the value of A0
  Serial.print("A0: ");
  Serial.println(Astate); //print the value in the serial monitor
  Dstate=digitalRead(digitalPin); //read the value of D0
  Serial.print("Do: ");
  Serial.println(Dstate);
  if(Dstate == HIGH){
    digitalWrite(ledPin, LOW);
    }
  else //if the value of D0 is LOW
  {
    digitalWrite(ledPin, HIGH); //turn on the led
  }
}

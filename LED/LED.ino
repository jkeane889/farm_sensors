//Simple program that flashes the Arduino's Onboard LED

int ledPin = 13;

void setup()
{
  //intialize pins as outputs
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(5000);
  digitalWrite(ledPin, LOW);
  delay(5000);
}

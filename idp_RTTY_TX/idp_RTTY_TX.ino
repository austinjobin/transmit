//Authors: Alvin Chung, Austin Jobin

String input;
const int signalPin = 12;
unsigned int Time=235;

void setup() //Runs Once
{
Serial.begin(9600);
pinMode(signalPin, OUTPUT);

while(Serial.available() == 0)
{
  input = Serial.readString();

  Serial.print(input);

  if(input.length())
    break;

}
bool output[input.length()];
}

void loop() //Runs Continuously, indefinitely
{
  // put your main code here, to run repeatedly  
digitalWrite(signalPin,HIGH);
delayMicroseconds(Time);
digitalWrite(signalPin,LOW);
delayMicroseconds(Time);

}

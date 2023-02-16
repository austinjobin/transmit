const int OP= 12;
unsigned int Time=235;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(OP, OUTPUT);
while(Serial.available()==0){
String input = Serial.readString();
Serial.print(input);
if(input.length()){
break;
}
}
bool output[input.length()];
}

void loop() {
  // put your main code here, to run repeatedly  
digitalWrite(OP,HIGH);
delayMicroseconds(Time);
digitalWrite(OP,LOW);
delayMicroseconds(Time);

}

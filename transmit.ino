const int OP= 12;
unsigned int Time=235;
int  p=0;
String input;
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
int Size=input.length()*10;
bool output[Size];
for(int i{0};i<input.length();i++){
  p=10*i;
output[p]=0;
int h=0;
for(int j{p+1}; j<p+9;j++){
output[j]=((input[i]>>h)&1);
h++;
}
output[p+9]=1;
}

}

void loop() {
  // put your main code here, to run repeatedly  
digitalWrite(OP,HIGH);
delayMicroseconds(Time);
digitalWrite(OP,LOW);
delayMicroseconds(Time);

}

const int OP= 12;
unsigned int Time=235;
int  p=0;
void setup() 
{
  
  Serial.begin(9600);
  pinMode(OP, OUTPUT);
  
  while(Serial.available()==0){
  String input = Serial.readString();
  Serial.print(input);
  
  if(input.length())
    break;
  
}
int Size=input.length()*10;
bool output[Size];
for(int i{0};i<input.length();i++){
  //p=l*
  output[i]=0;

for(int j{0}; j<8;j++)
}

}

void loop() {
  // put your main code here, to run repeatedly  
digitalWrite(OP,HIGH);
delayMicroseconds(Time);
digitalWrite(OP,LOW);
delayMicroseconds(Time);

}

const int OP= 12;
int  p=0;
int arraycount{0};
bool start{1};
String input{""};
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(OP, OUTPUT);
while(Serial.available()==0){
input = Serial.readString();
if(input.length()){
break;
}
}
static int Size=(input.length())*10;
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
//while(1)  //send message repeatedly
 {    
  // if(arraycount>Size-1)
  {
   //  arraycount=0;
  //   start=true;
   }
while(arraycount<Size-1)  //send message and stop
{
if(!start){
    arraycount++;
}
start=false;

switch(output[arraycount]){
case 0:
tone(OP,2295,22);
Serial.println("zero");
delay(22);
break;
case 1:
tone(OP,2125,22);
Serial.println("one");
delay(22);
break;
}
}

}
}
void loop() {
  // put your main code here, to run repeatedly  
 
}

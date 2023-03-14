//Authors: Austin Jobin, Alvin Chung

const int transmitPin = 12;    // the pin used for transmitting, in this case digital pin 12
int p = 0;            //constant in charge of keeping track which character is being assigned in the array
int arrayCount{ 0 };  // counter for what bit is being transmitted in the array
bool start{ 1 };      //flag for the initial start of the message
String input{ "" };   //intitializing input string to NULL

void setup() //Runs once
{
  Serial.begin(9600);               //ardino bitrate
  pinMode(transmitPin, OUTPUT);     //setting digital pin 12 to output
  while (Serial.available() == 0)   //loop reading serial monitor
  {  
    
    input = Serial.readString();    //read from serial monitor
    if (input.length())             //when input has a value stop reading monitor
      break;
    
  }
  static int Size = (input.length()) * 10;     //size of array is 10 bits per character
  bool output[Size];                           //intilizing boolean array for output

  for (int i{ 0 }; i < input.length(); i++) {  // loop filling boolean array runs once for each character
    p = 10 * i;                                // size of P multiplied by 10 to keep track of where in the array a UART character is being encoded
    output[p] = 0;                             //Start bit assigned to 0
    
    int h = 0;                                 // intilizing variable to encode char to boolean value LSB to MSB
    for (int j{ p + 1 }; j < p + 9; j++) {     //nested loop for encoding char to the data portion of the UART frame consisting of 8 bits
      output[j] = ((input[i] >> h) & 1);       //bitshift operation encoding Char from input string to boolean value tobe stored in output array
      h++;                                     //increment h to get next bool value in input char
    }
    output[p + 9] = 1;  //UART END bit
  }
  
  while (1)  //send message repeatedly
  {
    if (arrayCount > Size - 1)  // if the count exceeds the array size (the string is finished) restart
    {
      arrayCount = 0;
      start = true;
    }
    //while(arrayCount<Size-1)  //send message and stop
    {
      //if (!start) {  //start flag only increments arrayCount after first bit is encoded
      //  arrayCount++;
      //}

      //start = false;  //sets flag to false ensuring array count is initialized

      switch (output[arrayCount])  //switch statment sending output as either a 2295 hz space and a 2125 hz mark
      {
        case 0:
          tone(transmitPin, 2295, 22);      //tone fuction sending 2295 Hz square wave for 22 ms to output digital pin 12
          Serial.println("zero");  //testing purposes prints if a zero was sent to output
          delay(22);               //delay allowing frequency tobe sent for 22ms before sending next bit
          break;
        case 1:
          tone(transmitPin, 2125, 22);  //same code as above for a 2125 Hz mark
          Serial.println("one");
          delay(22);
          break;
      }
      arrayCount++; //increment arrayCount
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly
}

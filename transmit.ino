//Authors: Austin Jobin, Alvin Chung

const int transmitPin = 12; // The pin used for transmitting, in this case digital pin 12
int bitIndex = 0;           // Used for keeping track of which bit is being assigned in the array
int arrayCount = 0;         // counter for what bit is being transmitted in the array
String input = "";          //intitializing input string as an empty string
int transmitSize;           //The number of bits for a single transmission

//We are using an array that only needs to be initialized once,
//so this bool will be set true when it has been initialized.
//We use this method since arrays have static size, so we need to
//initialize it  within the same scope we need to read it in.
bool outputInitialized = false;

void setup() //Runs once
{
  Serial.begin(9600);               // Initialize Serial port
  pinMode(transmitPin, OUTPUT);     // Set digital pin 12 to output

  //Reading input from the user from the Serial Monitor
  while (Serial.available() == 0)   // Keeps checking if there is anything stored in the Serial receive buffer
  {                                 // After there is something, 
    input = Serial.readString();    // Read data from serial buffer
    if (input.length() > 0)         // when input has a value, stop reading monitor
      break;
  }

}

void loop() //Runs continuously, indefinitely
{
 if(outputInitialized == false)
 {
  //Converting the input into bits
    //number of bytes * (8 bits for ASCII + 2 extra bits)
    // Instantiate transmission size - 10 bits per character (1 stop, 1 start, 8 for ASCII)
    //Subtract 1 from input.length() remove the space allocated for the NULL value of the string
  transmitSize = ((input.length() - 1) * (8 + 2) );    

  bool output[transmitSize];          // Intializing boolean array for output
  int maxIndex = transmitSize - 1;    // Storing the max index for readability

  //Convert input String to a char array
  char characters[input.length()];
  input.toCharArray(characters, input.length());

  //"Major" loop keeps track of which "symbol" is being encoded, each symbol requires 10 bits
  for(int symbolIndex = 0; symbolIndex <= maxIndex - 9; symbolIndex += 10)
  {
    output[symbolIndex] = 0;      // Start Bit = 0
    output[symbolIndex + 9] = 1;  // Stop Bit = 1
    
    char currentCharacter = characters[symbolIndex/10];

    //"Minor" loop keeps track of which bit within a single symbol is being encoded
    //Starts at "second" bit of frame, first bit of ASCII Code
    int maxFrameIndex = symbolIndex + 9;
    int bitNumber = 0;
    for(int frameIndex = symbolIndex + 1; frameIndex <= maxFrameIndex - 1; frameIndex++)
    {
      output[frameIndex] = bitRead(currentCharacter, bitNumber); //LSB first, insert bit into output array

      bitNumber++;
    }
  }

  //For debugging:
  Serial.print("Output size: ");
  Serial.println(sizeof(output));
  for(int i = 0; i < transmitSize; i++)
  {
    Serial.print("Bit ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(output[i]);
  }

  outputInitialized = true;
 }
 
  
}

//Produces a 2125Hz square wave for 22ms
void sendFrequencyOne()
{
  tone(transmitPin, 2125, 22);
}

//Produces a 2295Hz square wave for 22ms
void sendFrequencyZero()
{
  tone(transmitPin, 2295, 22);
}

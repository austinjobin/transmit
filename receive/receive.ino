//Authors: Alvin Chung, Austin Jobin

const int receivePin = 12;
char characterBuffer = 0;

bool readingData = false;
int dataBitIndex = 0;
int readValue = HIGH;

#define BAUD_TIME_PERIOD 22 //The time for each bit, in milliseconds
#define BITS_PER_DATA 8
#define BASE_2 2

void setup() //Runs once
{
  Serial.begin(9600); //Initialize Serial
  
  pinMode(receivePin, INPUT); //Initialize receiving pin as an input
}

void loop() //Runs continuously, indefinitely
{
  readValue = digitalRead(receivePin);

  //check if the program is currently reading data
  switch(readingData)
  {
    case false:
      //If not reading data, check for a start bit (LOW)
      if(readValue == LOW)
      {
        readingData = true; //Set a "flag" to begin reading

        //Wait one period and a half after falling edge
        //to start sampling in the middle of first data bit
        delay(BAUD_TIME_PERIOD + (BAUD_TIME_PERIOD / 2));
      }
      break;

    case true:
//Possible TODO add error checking for when a LOW is misinterpreted as a start bit, 
//dataBitIndex will be < 7 or stop bit is not read exactly when dataBitIndex > 7

      //Check if the end of the data has been reached by checking
      //the dataBitIndex and checking for a stop bit (HIGH)
      if(dataBitIndex > (BITS_PER_DATA - 1) && readValue == HIGH)
      {
  //DEBUGGING: print final binary value received
        //Serial.println(characterBuffer, BIN);
        
        Serial.print(characterBuffer); 
        
        readingData = false; //End reading mode and wait for next start bit
        //Serial.println(characterBuffer, BIN); //Print the character received
        dataBitIndex = 0; //Reset index to read
        characterBuffer = 0; //Reset character buffer
      }

      else if(dataBitIndex <= (BITS_PER_DATA - 1))
        {
          
  //DEBUGGING: Print the current bit
          // Serial.print("Bit ");
          // Serial.print(dataBitIndex);
          // Serial.print(": ");
          
          //If the bit is HIGH 
          if(readValue == HIGH) //add to decimal value of char
          {
            //the round() function is need otherwise, there will be
            //floating point errors
            characterBuffer += round(pow(BASE_2, dataBitIndex));
            
  //DEBUGGING: print a "1" if logic-1 is received
            //Serial.print("1 ");

            //Print the decimal value added to the char
            // Serial.print(round(pow(BASE_2, dataBitIndex)));
            // Serial.print(" Added, New Value: ");
            // Serial.println(characterBuffer, DEC); 
          }
  //DEBUGGING: print a "1" if logic-1 is received        
          // else
          //   Serial.println("0");

          dataBitIndex++;//increment place value of bit
          delay(BAUD_TIME_PERIOD); //wait for middle of next bit
        }
        
      break;
  }

}

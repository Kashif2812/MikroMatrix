/*
  ################################################################################
  # File Name:             MikroMatrix
  # Board:                 Arduino UNO
  # Programming Language:  C & C++  / Arduino IDE
  #
  # Objective:             Scrolling LED dot Matrix  &  Seven Segment
  #
  # Operation:             Scrolls a message over a 32x8 LED dot matrix
  #
  # Author:                MUHAMMAD KASHIF
  # Date:                  December 14, 2020
  # Place:                 Lahore - Pakistan
  #
  ################################################################################
 
 This code is a public example.
*/

#include <MikroMatrix.h> // download library from https://github.com/Kashif2812/MikroMatrix

#include <TimerOne.h>   // include timer library for software interrupt


#define CLOCK_PIN 13      // CLK pin of MAX7219 module on arduino UNO Pin no 13
#define CHIP_SELECT 10    // CLK pin of MAX7219 module on arduino UNO Pin no 10
#define DATA_PIN 11        // CLK pin of MAX7219 module on arduino UNO Pin no 11
#define NUM_OF_DEVICES 8   //change this variable to set how many MAX7219's you'll use
#define NUM_OF_DEVICES 8



//MAX_7219 class for LED_Matrix and Seven Segment driver:
MAX_7219 MAX_7219_MODULE(DATA_PIN, CHIP_SELECT, CLOCK_PIN, NUM_OF_DEVICES);


//MikroMatrixapp class for LED MATRIX applications
MikroMatrixapp LED_MATRIX(&MAX_7219_MODULE);


char message[100]; // array to store message

void setup() {
  Serial.begin(9600);                // begin serial and set buad rate 
  Timer1.initialize(200000);         // initialize timer with 200 milli seconds 
  Timer1.attachInterrupt(call_back);   // attach interupt with call back function 
  MAX_7219_MODULE.init();            // initializing hardware
  MAX_7219_MODULE.set_speed(90);     // setting of text scrolling speed
}

void call_back()     // This is a function called during interruption
{
  
int brightness;      // variable to hold the value of brightness
int Speed;           // variable to hold the value of speed

  
  if (Serial.available())   // condition to check if any value avail on seril buffer
      {
      
      char C=Serial.read();   // read identifier character 
        
        if (C=='B')    // check that if identifier character is equal to "B"
            {
              brightness=Serial.parseInt();               // then incoming value will be equal to brightness
              MAX_7219_MODULE.set_intensity(brightness);  // write the value of brightness in brightness register
            }
      

        if (C=='S')     // check that if identifier character is equal to "S"
            {
              Speed=Serial.parseInt();     // then incoming value will be equal to Speed
              MAX_7219_MODULE.set_speed(Speed);   // write the value of Speed in speed setting function
            }
      
      // note; For message identifier, use that character you are not using in your message
       
        if (C=='t')      // check that if identifier character is equal to "t"
            {
              memset(message , 0 , 100);      // function to clear message array for new message 
              Serial.readBytesUntil('\n' , message , 100);    // function to recive new message from Serial and store in message array
            }
        }
}



void loop() {
  
  
  
while (!Serial.available())    

{   
  LED_MATRIX.scroll_left(message); //function to scroll recieved message

}
}





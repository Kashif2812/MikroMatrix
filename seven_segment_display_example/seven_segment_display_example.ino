/*
  ################################################################################
  # File Name:             MikroMatrix
  # Board:                 Arduino UNO
  # Programming Language:  C & C++  / Arduino IDE
  #
  # Objective:             Scrolling LED dot Matrix  &  Seven Segment
  #
  # Operation:             Scrolls a message over a LED dot matrix Change its scrolling speed 
                           intensity and message text during scroll
  #
  # Author:                MUHAMMAD KASHIF
  # Date:                  December 14, 2020
  # Place:                 Lahore - Pakistan
  #
  ################################################################################
 
 This code is a public example.
*/

#include <MikroMatrix.h> // download library from https://github.com/Kashif2812/MikroMatrix



#define CLOCK_PIN 13      // CLK pin of MAX7219 module on arduino UNO Pin no 13
#define CHIP_SELECT 10    // CHIP_SELECT of MAX7219 module on arduino UNO Pin no 10
#define DATA_PIN 11        // DATA_PIN pin of MAX7219 module on arduino UNO Pin no 11
#define NUM_OF_DEVICES 4   //change this variable to set how many MAX7219's you'll use

#define POSITION_OF_7_SEGMENT 4   //change this variable on which position your 7 segment is connected

// i am using 4 digit seven segment 
#define NUMBER_OF_DIGIT       4 // define how many digits are on your seven segment display


//MAX_7219 class for LED_Matrix and Seven Segment driver:
MAX_7219 MAX_7219_MODULE(DATA_PIN, CHIP_SELECT, CLOCK_PIN, NUM_OF_DEVICES , POSITION_OF_7_SEGMENT , NUMBER_OF_DIGIT);



//Mikrosegapp class for Seven Segment applications
Mikrosegapp seven_seg(&MAX_7219_MODULE);


void setup() {
  Serial.begin(9600);                // begin serial and set buad rate 
  MAX_7219_MODULE.init();            // initializing hardware
  MAX_7219_MODULE.set_intensity(50); // set inensity of LEDs
  
}
  

void loop() { 
int num=0;

        num=Serial.parseInt();
        seven_seg.sevseg(num);
     delay(1000);   
}




      

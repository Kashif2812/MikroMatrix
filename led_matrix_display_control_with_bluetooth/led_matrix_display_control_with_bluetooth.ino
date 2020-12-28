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
#include <SoftwareSerial.h>
#include <MikroMatrix.h> // download library from https://github.com/Kashif2812/MikroMatrix
#include <TimerOne.h>   // include timer library for software interrupt


SoftwareSerial BT05(4, 5); //RX|TX

#define CLOCK_PIN 13      // CLK pin of MAX7219 module on arduino UNO Pin no 13
#define CHIP_SELECT 10    // CHIP_SELECT of MAX7219 module on arduino UNO Pin no 10
#define DATA_PIN 11        // DATA_PIN pin of MAX7219 module on arduino UNO Pin no 11
#define NUM_OF_DEVICES 4   //change this variable to set how many MAX7219's you'll use





char message[100];
int num;

//MAX_7219 class for LED_Matrix and Seven Segment driver:
MAX_7219 MAX_7219_MODULE(DATA_PIN, CHIP_SELECT, CLOCK_PIN, NUM_OF_DEVICES );



//Mikrosegapp class for Seven Segment applications
Mikrosegapp seven_seg(&MAX_7219_MODULE);


//MikroMatrixapp class for Seven Segment applications
MikroMatrixapp Matrix(&MAX_7219_MODULE);

void setup() {

  BT05.begin(9600);                // begin serial and set buad rate 
  MAX_7219_MODULE.init();            // initializing hardware
  Timer1.initialize(200000);         // initialize timer with 200 milli seconds 
  Timer1.attachInterrupt(call_back);   // attach interupt with call back function 

}







 void call_back()     // This is a function called during interruption
{
int brightness;      // variable to hold the value of brightness
int Speed;           // variable to hold the value of speed

    if (BT05.available())   // condition to check if any value avail on seril buffer
          {
      char C=BT05.read();   // read identifier character 

        if (C=='B')    // check that if identifier character is equal to "B"
            {
                 brightness=BT05.parseInt();               // then incoming value will be equal to brightness
              MAX_7219_MODULE.set_intensity(brightness);  // write the value of brightness in brightness register
            }


        if (C=='S')     // check that if identifier character is equal to "S"
            {
              Speed=BT05.parseInt();     // then incoming value will be equal to Speed
              MAX_7219_MODULE.set_speed(Speed);   // write the value of Speed in speed setting function
            }
      
      
      if (C=='n')     // check that if identifier character is equal to "S"
            {
              num=BT05.parseInt();     // then incoming value will be equal to Speed
              seven_seg.sevseg(num);
            }

            

       // note: For message identifier, use that character you are not using in your message
       
        if (C=='t')      // check that if identifier character is equal to "t"
            {
              memset(message , 0 , 100);      // function to clear message array for new message 
              BT05.readBytesUntil('\r' , message , 100);    // function to recive new message from Serial and store in message array

            }
        }
}

void loop() { 


seven_seg.sevseg(num);
Matrix. scroll_left(message);

}

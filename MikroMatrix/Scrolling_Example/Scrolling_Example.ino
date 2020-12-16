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
#define CLOCK_PIN 13      // CLK pin of MAX7219 module on arduino UNO Pin no 13
#define CHIP_SELECT 10    // CLK pin of MAX7219 module on arduino UNO Pin no 10
#define DATA_PIN 11        // CLK pin of MAX7219 module on arduino UNO Pin no 11
#define NUM_OF_DEVICES 4   //change this variable to set how many MAX7219's you'll use


//MAX_7219 class for LED_Matrix and Seven Segment driver:
MAX_7219 MAX_7219_MODULE(DATA_PIN,CHIP_SELECT,CLOCK_PIN,NUM_OF_DEVICES);


//MikroMatrixapp class for LED MATRIX applications
MikroMatrixapp LED_MATRIX(&MAX_7219_MODULE);




void setup() {
MAX_7219_MODULE.init();       // initializing hardware as per user requirement
MAX_7219_MODULE.set_intensity(100);  // setting intensity percentage 
MAX_7219_MODULE.set_speed(95);     // setting of text scrolling speed
  }

void loop() {

LED_MATRIX.scroll_left("MIKRO STAR TECH");      //  function to scroll text in left  direction 
LED_MATRIX.scroll_right("MIKRO STAR TECH");     //function to scroll text in right direction
}

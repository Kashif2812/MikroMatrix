

#ifndef _MikroMatrix_H_
#define _MikroMatrix_H_
#include "Arduino.h"
#include "SPI.h"

// Registers Address
#define No_operation    			0X00
#define digit_0    					0X01
#define digit_1    					0X02
#define digit_2    					0X03
#define digit_3    					0X04
#define digit_4    					0X05
#define digit_5    					0X06
#define digit_6    					0X07
#define digit_7    					0X08

#define display_test_reg    		0X0F
#define Shutdown_reg	 			0X0C
#define scan_limit_reg 	   			0X0B
#define Decode_Mode_reg    			0X09
#define intensity_cont_reg 			0X0A

// 	Display-Test Register (Address (Hex) = 0xXf)

#define Normal_operation   			0X00
#define display_test				0X01

// 	Shutdown Register Format (Address (Hex) = 0xXC)
#define Shutdown_Mode				0x00
#define Normal_Operation			0x01


//  Decode-Mode Register Examples (Address (Hex) = 0xX9)
#define No_decode_for_digits_7_0	0x00
#define decode_for_digit_0			0x01 	//no decode for digits 7-1
#define decode_for_digit_3_0		0x0F 	//no decode for digits 7-4
#define decode_for_digit_7_0		0xFF	

//   Scan-Limit Register Format (Address (Hex) = 0xXB)

#define Display_digit_0_only        0x00
#define Display_digit_0_&_1	        0x01
#define Display_digit_0_to_2        0x02
#define Display_digit_0_to_3        0x03
#define Display_digit_0_to_4        0x04
#define Display_digit_0_to_5        0x05
#define Display_digit_0_to_6        0x06
#define Display_digit_0_to_7        0x07


/*
Intensity Register Format (Address (Hex) = 0xXA)

DUTY CYCLE					HEX CODE
1/32		   	  (min on)  0xX0
3/32						0xX1
5/32						0xX2
7/32						0xX3
9/32						0xX4
11/32						0xX5
13/32						0xX6
15/32						0xX7
17/32						0xX8
19/32						0xX9
21/32						0xXA
23/32					 	0xXB
25/32						0xXC
27/32						0xXD
29/32						0xXE
31/32			   (max on) 0xXF
*/
const byte Alphabet[1000]PROGMEM = {
  

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0020 (space)
    0x10, 0x38, 0x38, 0x10, 0x10, 0x00, 0x10, 0x00,  // 0021 (exclam)
    0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0022 (quotedbl)
    0x24, 0x24, 0x7e, 0x24, 0x7e, 0x24, 0x24, 0x00,  // 0023 (numbersign)
    0x18, 0x3e, 0x40, 0x3c, 0x02, 0x7c, 0x18, 0x00,  // 0024 (dollar)
    0x00, 0x62, 0x64, 0x08, 0x10, 0x26, 0x46, 0x00,  // 0025 (percent)
    0x30, 0x48, 0x30, 0x56, 0x88, 0x88, 0x76, 0x00,  // 0026 (ampersand)
    0x10, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0027 (quotesingle)
    0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00,  // 0028 (parenleft)
    0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00,  // 0029 (parenright)
    0x00, 0x44, 0x38, 0xfe, 0x38, 0x44, 0x00, 0x00,  // 002a (asterisk)
    0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, 0x00,  // 002b (plus)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20,  // 002c (comma)
    0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,  // 002d (hyphen)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00,  // 002e (period)
    0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00,  // 002f (slash)
    0x3c, 0x42, 0x46, 0x4a, 0x52, 0x62, 0x3c, 0x00,  // 0030 (zero)
    0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c, 0x00,  // 0031 (one)
    0x3c, 0x42, 0x02, 0x0c, 0x30, 0x42, 0x7e, 0x00,  // 0032 (two)
    0x3c, 0x42, 0x02, 0x1c, 0x02, 0x42, 0x3c, 0x00,  // 0033 (three)
    0x08, 0x18, 0x28, 0x48, 0x7e, 0x08, 0x1c, 0x00,  // 0034 (four)
    0x7e, 0x40, 0x7c, 0x02, 0x02, 0x42, 0x3c, 0x00,  // 0035 (five)
    0x1c, 0x20, 0x40, 0x7c, 0x42, 0x42, 0x3c, 0x00,  // 0036 (six)
    0x7e, 0x42, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00,  // 0037 (seven)
    0x3c, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x3c, 0x00,  // 0038 (eight)
    0x3c, 0x42, 0x42, 0x3e, 0x02, 0x04, 0x38, 0x00,  // 0039 (nine)
    0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x00,  // 003a (colon)
    0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20,  // 003b (semicolon)
    0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x00,  // 003c (less)
    0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00,  // 003d (equal)
    0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00,  // 003e (greater)
    0x3c, 0x42, 0x02, 0x04, 0x08, 0x00, 0x08, 0x00,  // 003f (question)
    0x3c, 0x42, 0x5e, 0x52, 0x5e, 0x40, 0x3c, 0x00,  // 0040 (at)
    0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x00,  // 0041 (A)
    0x7c, 0x22, 0x22, 0x3c, 0x22, 0x22, 0x7c, 0x00,  // 0042 (B)
    0x1c, 0x22, 0x40, 0x40, 0x40, 0x22, 0x1c, 0x00,  // 0043 (C)
    0x78, 0x24, 0x22, 0x22, 0x22, 0x24, 0x78, 0x00,  // 0044 (D)
    0x7e, 0x22, 0x28, 0x38, 0x28, 0x22, 0x7e, 0x00,  // 0045 (E)
    0x7e, 0x22, 0x28, 0x38, 0x28, 0x20, 0x70, 0x00,  // 0046 (F)
    0x1c, 0x22, 0x40, 0x40, 0x4e, 0x22, 0x1e, 0x00,  // 0047 (G)
    0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x00,  // 0048 (H)
    0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00,  // 0049 (I)
    0x0e, 0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00,  // 004a (J)
    0x62, 0x24, 0x28, 0x30, 0x28, 0x24, 0x63, 0x00,  // 004b (K)
    0x70, 0x20, 0x20, 0x20, 0x20, 0x22, 0x7e, 0x00,  // 004c (L)
    0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x41, 0x00,  // 004d (M)
    0x62, 0x52, 0x4a, 0x46, 0x42, 0x42, 0x42, 0x00,  // 004e (N)
    0x18, 0x24, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00,  // 004f (O)
    0x7c, 0x22, 0x22, 0x3c, 0x20, 0x20, 0x70, 0x00,  // 0050 (P)
    0x3c, 0x42, 0x42, 0x42, 0x4a, 0x3c, 0x03, 0x00,  // 0051 (Q)
    0x7c, 0x22, 0x22, 0x3c, 0x28, 0x24, 0x72, 0x00,  // 0052 (R)
    0x3c, 0x42, 0x40, 0x3c, 0x02, 0x42, 0x3c, 0x00,  // 0053 (S)
    0x7f, 0x49, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00,  // 0054 (T)
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00,  // 0055 (U)
    0x41, 0x41, 0x41, 0x41, 0x22, 0x14, 0x08, 0x00,  // 0056 (V)
    0x41, 0x41, 0x41, 0x49, 0x49, 0x49, 0x36, 0x00,  // 0057 (W)
    0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, 0x00,  // 0058 (X)
    0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x1c, 0x00,  // 0059 (Y)
    0x7f, 0x42, 0x04, 0x08, 0x10, 0x21, 0x7f, 0x00,  // 005a (Z)
    0x78, 0x40, 0x40, 0x40, 0x40, 0x40, 0x78, 0x00,  // 005b (bracketleft)
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,  // 005c (backslash)
    0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00,  // 005d (bracketright)
    0x10, 0x28, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00,  // 005e (asciicircum)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,  // 005f (underscore)
    0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0060 (grave)
    0x00, 0x00, 0x3c, 0x02, 0x3e, 0x42, 0x3f, 0x00,  // 0061 (a)
    0x60, 0x20, 0x20, 0x2e, 0x31, 0x31, 0x2e, 0x00,  // 0062 (b)
    0x00, 0x00, 0x3c, 0x42, 0x40, 0x42, 0x3c, 0x00,  // 0063 (c)
    0x06, 0x02, 0x02, 0x3a, 0x46, 0x46, 0x3b, 0x00,  // 0064 (d)
    0x00, 0x00, 0x3c, 0x42, 0x7e, 0x40, 0x3c, 0x00,  // 0065 (e)
    0x0c, 0x12, 0x10, 0x38, 0x10, 0x10, 0x38, 0x00,  // 0066 (f)
    0x00, 0x00, 0x3d, 0x42, 0x42, 0x3e, 0x02, 0x7c,  // 0067 (g)
    0x60, 0x20, 0x2c, 0x32, 0x22, 0x22, 0x62, 0x00,  // 0068 (h)
    0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00,  // 0069 (i)
    0x02, 0x00, 0x06, 0x02, 0x02, 0x42, 0x42, 0x3c,  // 006a (j)
    0x60, 0x20, 0x24, 0x28, 0x30, 0x28, 0x26, 0x00,  // 006b (k)
    0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00,  // 006c (l)
    0x00, 0x00, 0x76, 0x49, 0x49, 0x49, 0x49, 0x00,  // 006d (m)
    0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x00,  // 006e (n)
    0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x3c, 0x00,  // 006f (o)
    0x00, 0x00, 0x6c, 0x32, 0x32, 0x2c, 0x20, 0x70,  // 0070 (p)
    0x00, 0x00, 0x36, 0x4c, 0x4c, 0x34, 0x04, 0x0e,  // 0071 (q)
    0x00, 0x00, 0x6c, 0x32, 0x22, 0x20, 0x70, 0x00,  // 0072 (r)
    0x00, 0x00, 0x3e, 0x40, 0x3c, 0x02, 0x7c, 0x00,  // 0073 (s)
    0x10, 0x10, 0x7c, 0x10, 0x10, 0x12, 0x0c, 0x00,  // 0074 (t)
    0x00, 0x00, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x00,  // 0075 (u)
    0x00, 0x00, 0x41, 0x41, 0x22, 0x14, 0x08, 0x00,  // 0076 (v)
    0x00, 0x00, 0x41, 0x49, 0x49, 0x49, 0x36, 0x00,  // 0077 (w)
    0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00,  // 0078 (x)
    0x00, 0x00, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x7c,  // 0079 (y)
    0x00, 0x00, 0x7c, 0x08, 0x10, 0x20, 0x7c, 0x00,  // 007a (z)
    0x0c, 0x10, 0x10, 0x60, 0x10, 0x10, 0x0c, 0x00,  // 007b (braceleft)
    0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10, 0x00,  // 007c (bar)
    0x30, 0x08, 0x08, 0x06, 0x08, 0x08, 0x30, 0x00,  // 007d (braceright)
    0x32, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 007e (asciitilde)
    0x00, 0x08, 0x14, 0x22, 0x41, 0x41, 0x7f, 0x00,  // 007f (uni007F)
    // ---------------------------  160-255 ---------------------------
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 00a0 (uni00A0)
    0x00, 0x10, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00,  // 00a1 (exclamdown)
    0x08, 0x08, 0x3e, 0x40, 0x40, 0x3e, 0x08, 0x08,  // 00a2 (cent)
    0x18, 0x24, 0x20, 0x70, 0x20, 0x42, 0x7c, 0x00,  // 00a3 (sterling)
    0x00, 0xc6, 0x38, 0x44, 0x44, 0x38, 0xc6, 0x00,  // 00a4 (currency)
    0x44, 0x28, 0x7c, 0x10, 0x7c, 0x10, 0x10, 0x00,  // 00a5 (yen)
    0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10, 0x00,  // 00a6 (brokenbar)
    0x3e, 0x63, 0x38, 0x44, 0x44, 0x38, 0xcc, 0x78,  // 00a7 (section)
    0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 00a8 (dieresis)
    

};

	class MAX_7219
		{
  		public:
  			
	  		int MAX_digit;
	  		int DIN_PIN;
   		  	int SS_PIN;
    	 	int CLK_PIN;
   		  	int Speed;
    		int MAX_DEV;
    		int seg_pos;
    		int temp1[1][8];  
    		void write_reg(uint8_t address, uint8_t value);
   		  	void str_prpnd(char ary[]);
  		  	void str_apnd(char ary[]);
   		  	void copy_ary_from_pgm(char ary, char num  );
  			void write_reg1(uint8_t address, uint8_t value);
  			void no_op();
  			void init();   
			void set_speed(int spd);
			void set_intensity(int brightness);
  			MAX_7219(){}
  			MAX_7219(int DIN_PIN, int SS_PIN, int CLK_PIN,int MAX_DEV);
			
			MAX_7219(int DIN_PIN, int SS_PIN, int CLK_PIN,int MAX_DEV,int MAX_digit);


  			MAX_7219(int DIN_PIN, int SS_PIN, int CLK_PIN,int MAX_DEV,int seg_pos,int MAX_digit);
};





class Mikrosegapp
		{
		private:
MAX_7219* max_7219;
public:

Mikrosegapp( MAX_7219* max_7219)
{
	this->max_7219 = max_7219;	
}
void sevseg(int num);
};


class MikroMatrixapp
		{
		private:
MAX_7219* max_7219;
public:

MikroMatrixapp( MAX_7219* max_7219)
{
	this->max_7219 = max_7219;	
}
				void scroll_right(char msg[]);
  				void scroll_left(char message1[]); 
  				void invtd_scroll_left(char msg[]);
  				void invtd_scroll_right(char msg[]);
  				void sevseg(int num);
  				 				
};

#endif
















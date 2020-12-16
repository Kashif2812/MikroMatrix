#include "MikroMatrix.h"
#include "SPI.h"
#include "Arduino.h"


MAX_7219::MAX_7219(int _data, int _ss_pin, int _clock,int _MAX_DEV , int _seg_pos, int _MAX_DIG) 
{
  DIN_PIN = _data;
  SS_PIN = _ss_pin;
  CLK_PIN = _clock;
  MAX_DEV=_MAX_DEV;
  MAX_digit=_MAX_DIG;
  seg_pos=_seg_pos;
  int Speed;
  int temp1[1][8];	
  
}

MAX_7219::MAX_7219(int _data, int _ss_pin, int _clock,int _MAX_DEV) 
{
  DIN_PIN = _data;
  SS_PIN = _ss_pin;
  CLK_PIN = _clock;
  MAX_DEV=_MAX_DEV;
  int Speed;
  int temp1[1][8];	
  
}


MAX_7219::MAX_7219(int _data, int _ss_pin, int _clock,int _MAX_DEV , int _MAX_DIG) 

{
  DIN_PIN = _data;
  SS_PIN = _ss_pin;
  CLK_PIN = _clock;
  MAX_DEV=_MAX_DEV;
  MAX_digit=_MAX_DIG;
  seg_pos=1;
  int Speed;
  int temp1[1][8];	
  
}



void MAX_7219::init()
			{
				  
				  Serial.begin(9600);
				  
				  SPI.setBitOrder(MSBFIRST);
				  SPI.begin();
				  pinMode(DIN_PIN,OUTPUT);
				  pinMode(SS_PIN,OUTPUT);
				  pinMode(CLK_PIN,OUTPUT);
				  
  				 
			
				  write_reg(display_test_reg, display_test);
				  delay(1000);
				  write_reg(display_test_reg, Normal_operation);
				  write_reg(Decode_Mode_reg,No_decode_for_digits_7_0 );
				  write_reg(scan_limit_reg,Display_digit_0_to_7 );
				  write_reg(Shutdown_reg, Normal_Operation);		
			
			
				
				  write_reg1(display_test_reg, display_test);
				  delay(1000);
				  write_reg1(display_test_reg, Normal_operation);
				  write_reg1(Decode_Mode_reg,decode_for_digit_3_0 );
				  write_reg1(scan_limit_reg,Display_digit_0_to_4 );
				  write_reg1(Shutdown_reg, Normal_Operation);		
				
		}
	



void MAX_7219::write_reg(uint8_t address, uint8_t value) {
	for (int i=1; i<=MAX_DEV; i++)
	{
    digitalWrite(SS_PIN, LOW);
    
    
	
		if (i!=seg_pos)
	{
		SPI.transfer(address);
    	SPI.transfer(value);
	}
		if (i==seg_pos)no_op();
	
	digitalWrite(SS_PIN, HIGH);
    
}
}

void MAX_7219::write_reg1(uint8_t address, uint8_t value) {




    digitalWrite(SS_PIN, LOW); 
	for (int i=1; i<=MAX_DEV; i++)
	{
	
	
		if (i!=seg_pos)no_op();
		
		if (i==seg_pos)
		{
		SPI.transfer(address);
    	SPI.transfer(value);
}
}
    digitalWrite(SS_PIN, HIGH);

}


void MAX_7219:: set_intensity(int brightness) {
  brightness = map(brightness, 0, 100, 0, 15);
  write_reg(intensity_cont_reg, brightness);
	
}

void MAX_7219:: set_speed(int spd) {
  spd = map(spd, 1, 100, 1000, 0);
  Speed = spd;
}

void MAX_7219:: copy_ary_from_pgm(char ary, char num  )
{ 
  char flash_ary[8];
  int Start_Byte = (ary - 32) * 8;
  for (int i = 0; i < MAX_DEV + 1; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (num == i)
      {
        flash_ary[j] = pgm_read_byte(&Alphabet[Start_Byte + j]);
        temp1[i][j] = flash_ary[j];
      }
    }

  }
}

void MikroMatrixapp:: scroll_left(char message1[]) {



int spd=max_7219->Speed;
int maxdev=max_7219->MAX_DEV;
int ss_pin=max_7219->SS_PIN;
int seg=max_7219->seg_pos;



int temp[maxdev + 1][8];
int data_num = 0;
int num = 0;
char message[1000];  

for (int p = strlen(message1)+maxdev; p >= maxdev; p--)
 {
   message[p] = message1[p - maxdev];
  }
  for (int p = 0; p < maxdev ; p++)
  {
    message[p] = ' ';  
  } 
{
  for (int i=0; i< maxdev; i++)
  {strcat(message , " ");}
}  
 
  for (int l = 0; message[data_num+maxdev ]!= '\0'; l++)
  {
    for (int a = 0; a < maxdev + 1; a++)
      {
        max_7219->copy_ary_from_pgm(message[data_num + a] , num + a);
      }
        for (uint8_t q = 0X00; q < 0X08 ; q++)
        {
          for (uint8_t i = digit_0; i <= digit_7; i++)
          {
            int j = i - 1;
            digitalWrite(ss_pin, LOW);
            for (int b = 0; b < maxdev; b++)
            {
              temp[b][j] = ((max_7219->temp1[b ][j] << q ) | ( (max_7219->temp1[b+1][j] & (0xFF << (8 - q))) >> (8 - q)));
              SPI.transfer(i);
              SPI.transfer(temp[b][j]);
        	
        	
        	if (b==seg-1)
        	{
        		max_7219->no_op();
			}
        	
        	}
            digitalWrite(ss_pin, HIGH);
          }
          delay(spd);
        }
    data_num++;
  }
}












void MikroMatrixapp:: scroll_right(char message1[])
{ 


int spd=max_7219->Speed;
int maxdev=max_7219->MAX_DEV;
int ss_pin=max_7219->SS_PIN;
int seg=max_7219->seg_pos;

char message[1000];  

for (int p = strlen(message1)+maxdev; p >= maxdev; p--)
 {
   message[p] = message1[p - maxdev];
  }
  for (int p = 0; p < maxdev ; p++)
  {
    message[p] = ' ';  
  } 
{
  for (int i=0; i< maxdev; i++)
  {strcat(message , " ");}
}  


 
  int temp[maxdev + 1][8];
  int num = 0;
  int data_num = 0;
	int l = 0;
  for ( l = 0; message[l + (maxdev + 1)] != '\0'; l++)
  {
    data_num++;
  }

  do
  {
    for (int a = 0; a < maxdev + 1; a++)
	    {
	      max_7219->copy_ary_from_pgm(message[data_num + a] , num + a);
	    }
		    for (uint8_t q = 0X00; q < 0X08 ; q++)
		    {
		      for (uint8_t i = 0x01; i < 0x09; i++)
		      {
		        int j = i - 1;
		        digitalWrite(ss_pin, LOW);
		        for (int b = 0; b < maxdev; b++)
		        {
		          temp[b][j] = ((max_7219->temp1[b + 1][j] >> q ) | ( (max_7219->temp1[b][j] & (0xFF >> (8 - q))) << (8 - q)));
		          SPI.transfer(i);
		          SPI.transfer(temp[b][j]);
				
				
				if (b==seg-1)
        	{
        		max_7219->no_op();
			}

				}
		        digitalWrite(ss_pin, HIGH);
		      }
		      delay(spd);
		    }
    data_num--;
  }
while (data_num>=0);
}

void Mikrosegapp::sevseg(int num){
int digit=max_7219->MAX_digit;

    while(num > 0) 
    {
        int mod = num % 10;  
        digitalWrite(max_7219->SS_PIN, LOW); 
	for (int i=1; i<=max_7219->MAX_DEV; i++)
	{
	
	
		max_7219->no_op();
		
		if (i==max_7219->seg_pos)
		{
		SPI.transfer(digit);
    	SPI.transfer(mod);
}
}
    digitalWrite(max_7219->SS_PIN, HIGH);
    
        num = num / 10;   
    digit--;
	}
    
}
			
void MAX_7219::no_op(){
SPI.transfer(0x00);
SPI.transfer(0x00);

}




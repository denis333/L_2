/*
 * mycharpad.c
 *
 * Created: 2/21/2017 9:33:31 AM
 *  Author: denis
 */ 
#include "keypad.h"
#include <avr/io.h>
unsigned char KB_Getmychar(void)
{
	DDRA=0x0f;//0..3-in;4..7-out
	PORTA=0xF0;
	unsigned char cols = PINA;
	DDRA=0xf0;	
	PORTA=0x0f;
	unsigned char row = PINA;
	DDRA=0x0f;//0..3-in;4..7-out
	PORTA=0xF0;
	return (cols | row);
	
}
unsigned char KB_Convert(unsigned char mymychar)
{
	unsigned char mychar;
	 switch (mymychar) {
		 case 0b11101110:
		mychar = '1';
		 break;
		 case 0b11101101:
		mychar = '2';
		 break;
		 case 0b11101011:
		mychar = '3';
		 break;
		 case 0b11100111:
		mychar = '4';
		 break;
		 case 0b11011110:
		mychar = '5';
		 break;
		 case 0b11011101:
		mychar = '6';
		 break;
		 case 0b11011011:
		mychar = '7';
		 break;
		 case 0b11010111:
		mychar = '8';
		 break;
		 case 0b10111110:
		mychar = '9';
		 break;
		 case 0b10111101:
		mychar = '0';
		 break;
		 case 0b10111011:
		mychar = '=';
		 break;
		 case 0b10110111:
		mychar = '+';
		 break;
		 case 0b01111110:
		mychar = '-';
		 break;
		 case 0b01111101:
		mychar = '*';
		 break;
		 case 0b01111011:
		mychar = '/';
		 break;
		 default : mychar = 'D';
		 break;
	 }
	  return mychar;
}
/*
 * L2.c
 *
 * Created: 2/21/2017 9:28:15 AM
 * Author : denis
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "calculator.h"

volatile char i=0;
unsigned char operation;
volatile unsigned int my_number;
volatile unsigned int my_number2;
volatile unsigned char mch,disp_counter;
volatile float div_result;
char final_result[10];

/*
Functia data creaza legatura dintre libraria
calculator si keypad
Input:
1)array de 5 caractere-in care se va salva 
n-rul reprezentat sub forma de caractere
2)un parameru de tip char-reprezinta tasta 
apasata de utilizator
*/
void ProcessPushedButton(char str_number[5],char mch)
{
//daca utilizatorul apasa pe 'Del',atunci 
//aducem i la starea initiala,str_number-resetam
	if(mch == 'D'){i=0; str_number[0] = '\0';}
	else
	{
		str_number[i++] = mch;//umplem tabloul cu caractere
//Daca utilizatorul apasa pe semn,atunci are loc salvarea
//semnului in variabila 'operation',din str_number se scoate semnul		
		if(mch == '+' | mch == '-' | mch == '*' | mch == '/')
		{
			operation = mch;
			str_number[--i]='\0';//excludem semnul din tablou
			my_number=atoi(str_number);//convertim in int n-rul
			i=0; str_number[i]='\0';
		}
/*Daca a fost folosit '=',
prelucram operatia aritmetica*/
		else if(mch == '=')
		{
			str_number[--i]='\0';//excludem egalul din tablou
			my_number2=atoi(str_number);//convertim in int n-r2
			i=0; str_number[i]='\0';
/*Identificarea operatiei cerute de utilizator*/
			switch (operation)
			{
				case '+':
				my_number = Suma(my_number,my_number2);
				break;
				case '-':
				my_number = Scaderea(my_number,my_number2);
				break;
				case '*':
				my_number = Inmultirea(my_number,my_number2);
				break;
				case '/':
				div_result = Impartirea(my_number,my_number2);
				break;
			}
		}
	}
	
}

ISR(INT0_vect)
{
/*Afisarea pe LCD
in dependenta de butonul apasat*/
	char str_number[5];
	mch = KB_Getmychar();
	mch = KB_Convert(mch);

	ProcessPushedButton(str_number[5],mch);
//valoarea aceasta se incrementeaza atunci 
//cind este indeplinita ISR;poate fi inlocuita cu bool	
disp_counter++;			
}

void SystemInit(void);

int main(void)
{		
	SystemInit();
	
	while (1) 
    {	
		/*conditia pentru afisarea aceluiasi caracter o data*/
		if(disp_counter>0)
		{
			Lcd_clear();
			Lcd_putc(mch);
			if(mch=='D') Lcd_clear();
			else if(mch=='=')
			{
				Lcd_clear();
				if(operation == '/')
				{
					dtostrf(div_result,3,2,final_result);
					Lcd_clear();
					Lcd_puts(final_result);
				}
				else{
					itoa(my_number,final_result,10);
					Lcd_clear();
					Lcd_puts(final_result);
				}
			}
		
		disp_counter=0;
		}
		
    }
}

void SystemInit()
{
/*PORT INIT*/	
	DDRD  = 0b0000000;
	PORTD = 0xff;
	DDRA=0x0f;//0..3-in;4..7-out
	PORTA=0xf0;
/*EXT0 INIT*/	
	MCUCR |= (1<<ISC01);
	GICR |=(1<<INT0);
	GIFR |=(1<<INTF0);
	
	sei();
	Lcd_Init();
	Lcd_puts("   CALCULATOR");
}
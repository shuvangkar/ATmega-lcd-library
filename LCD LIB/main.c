/*
 * LCD LIB.c
 *
 * Created: 2/20/2020 1:07:37 AM
 * Author : Shuvangkar
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include "util/delay.h"
#include "lcd.h"

int main(void)
{
	DDRD |= (1<<PD3);
	PORTD &= ~(1<<PD3);
	//PIN(DDRD) &= ~(1<<PD3);
// 	lcd_port_init_4Bit();
// 	map_data_port(6);
	lcd_begin();
	
    while (1) 
    {
		//busyState = PIN(D7_PORT) & (1<<D7_PIN);
// 		busyState = PIN(D7_PORT)&(1<<D7_PIN);
// 		if(busyState==0)
// 		{
// 			PORTD |= 1<<PD3;
// 		}
// 		else
// 		{
// 			PORTD &= ~(1<<PD3);
// 		}
// 		PORTD |= 1<<PD3;
// 		lcd_print("Hello");
// 		

		lcd_set_cursor(3,0);
		PORTD |= 1<<PD3;
		lcd_print("Hello");
		PORTD &=~(1<<PD3);
		_delay_ms(1000);
    }
}


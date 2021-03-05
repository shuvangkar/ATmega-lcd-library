/*
 * lcd.c
 *
 * Created: 2/20/2020 1:16:41 AM
 *  Author: Shuvangkar
 */ 
#include "lcd.h"


void lcd_port_init_4Bit()
{
	DDR(RS_PORT) |= 1<<RS_PIN;
	DDR(RW_PORT) |= 1<<RW_PIN;
	DDR(EN_PORT) |= 1<<EN_PIN;
	
	DDR(D4_PORT) |= 1<<D4_PIN;
	DDR(D5_PORT) |= 1<<D5_PIN;
	DDR(D6_PORT) |= 1<<D6_PIN;
	DDR(D7_PORT) |= 1<<D7_PIN;
}


void map_data_port(unsigned char data)
{

	/*MAP_BIT(data,0,D4_PORT,D4_PIN);
	MAP_BIT(data,1,D5_PORT,D5_PIN);
	MAP_BIT(data,2,D6_PORT,D6_PIN);
	MAP_BIT(data,3,D7_PORT,D7_PIN);
	*/
	uint8_t state = (data>>0)&0b00000001;
	WRITE_PIN(D4_PORT,D4_PIN,state);
	
	state = (data>>1)&0b00000001;
	WRITE_PIN(D5_PORT,D5_PIN,state);
	
	state = (data>>2)&0b00000001;
	WRITE_PIN(D6_PORT,D6_PIN,state);
	
	state = (data>>3)&0b00000001;
	WRITE_PIN(D7_PORT,D7_PIN,state);
	

}

void lcd_write_nibble(unsigned char data, uint8_t type)
{
	
	if(type == 0)
	{
		RS_LO(); //for command
	}
	else
	{
		RS_HI(); //for data
	}
	RW_LO(); //for write
	
	EN_LO();
	EN_HI();
	map_data_port(data);
	EN_LO();
	
}

void lcd_write_byte(unsigned char data, uint8_t type)
{
	uint8_t temp;
	
	temp = (data>>4)& 0X0F;
	lcd_write_nibble(temp,type);//Sending high nibble
	
	temp = data & 0X0F;
	lcd_write_nibble(temp,type);//Sending lower nible
	_delay_us(40);
	//lcd_busy_wait();
}

void lcd_write_cmd_with_delay(unsigned char data)
{
	uint8_t temp;
	
	
	_delay_ms(10);
	temp = (data>>4)& 0X0F; //Masking upper nibble
	lcd_write_nibble(temp,CMD);
	
	_delay_ms(10);
	temp = data & 0X0F;
	lcd_write_nibble(temp,CMD);
}

void lcd_write_cmd_byte(unsigned char data)
{
	uint8_t temp;
	temp = (data>>4)& 0X0F;
	lcd_write_nibble(temp,CMD);
	
	temp = data & 0X0F;
	lcd_write_nibble(temp,CMD);	
}


void lcd_busy_wait()
{
	//DDR(D7_PORT) &=~(1<<D7_PIN);;//D7 pin input for reading pin state
	RS_LO(); //for CMD
	RW_HI(); //Read Mode
	
	PORTB &= ~(1<<PB3);
	
	uint8_t busyFlag = 1;//Busy flag in D7 pin
	do 
	{
		//EN_LO();
		//EN_HI();
		EN_LO();
		//_delay_us(0.1);
		EN_HI();
		busyFlag = PINB & (1 << PB3);
		EN_LO();
		_delay_us(0.5);
		//_delay_us(0.1);
		//EN_HI();
		/*
		if (busyFlag)
		{
			PORTD |= 1<<PD3;
		}
		else
		{
			PORTD &= ~(1<<PD3);
		}
		*/
		
	} while (busyFlag);
	
	PORTB |= 1<<PB3;
	RW_LO();
	return;
}


void lcd_begin()
{
	_delay_ms(50);
	lcd_port_init_4Bit();
	
	lcd_write_cmd_byte(0x03);
	_delay_ms(5);
	lcd_write_cmd_byte(0x03);
	_delay_us(160);
	lcd_write_cmd_byte(0x03);
	_delay_us(160);
	lcd_write_cmd_byte(0x02); //to initialize LCD in 4-bit mode.
	_delay_ms(10);
	lcd_write_cmd_byte(0x28); //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	_delay_ms(10);
	lcd_write_cmd_byte(0x0C); //Display on, cursor off
	_delay_ms(10);
	lcd_write_cmd_byte(0x80); //Beginning of the first line
	_delay_ms(10);
}

void lcd_set_cursor(char x,char y)
{
	if(x<40)
	{
		switch(y)
		{
			case 0://1 line starts at 0×80(0b10000000)
			x |=0b10000000;
			break;
			case 1://2 line starts at 0xC0(0b11000000)
			x |=0b11000000;
			break;
			case 2://3 line starts at 0×94(0b10010100)
			x |=0b10010100;
			break;
			case 3://4 line starts at 0xD4(0b11010100)
			x |=0b11010100;
			break;
		}
		lcd_write_byte(x,CMD);
		//_delay_ms(1);
	}
}

void lcd_print(char* str)
{
	uint8_t i = 0;
	//lcd_write_byte(0x80,CMD);
	while(str[i] != '\0')
	{
		lcd_write_byte(str[i],DATA);
		i++;
	}
}
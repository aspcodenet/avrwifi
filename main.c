#define F_CPU 16000000UL 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "ESP8266.h"

unsigned int getDummyData();

int main (void)
{
    lcd_init(); 
    lcd_enable_blinking();
    lcd_enable_cursor();

    
    lcd_puts("Starting:");

	_delay_ms(1000);					 	// Delay on startup
	
	int data;

	init_serial();		
    lcd_set_cursor(0,1);
	lcd_puts("RESET          ");
	ESPinit();								// Setup ESP8266
	while(1)
	{
		data = getDummyData();				// Get dummy data
		addData("field1",data);
		data = getDummyData();				// Get dummy data
		addData("field2",data);
		pushData();							// Push data to Firebase
		_delay_ms(5000);
	}
}

unsigned int getDummyData(void)
{
	unsigned int data;
	data = rand() % 42;						// Random number from 0 to 42
	return data;
}

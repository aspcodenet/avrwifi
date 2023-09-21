#define F_CPU 16000000UL 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "thesupersensor.h"
#include "uart.h"
#include "ESP8266.h"


void initializeLcd(){
    lcd_init(); 
    lcd_enable_blinking();
    lcd_enable_cursor();
    lcd_puts("Starting:");
}

int main (void)
{
	initializeLcd();
	_delay_ms(1000);					 	// Delay on startup
	
	int data;

	init_serial();		
    lcd_set_cursor(0,1);
	lcd_puts("RESET          ");
	ESPinit();								// Setup ESP8266

	supersensor_init();
	while(1)
	{
/*
    int data = supersensor_get();				// Get dummy data
    addData("field1",data);
    data = supersensor_get();				// Get dummy data
    addData("field2",data);
    pushData();							// Push data to Firebase
*/		
		fetchAndSend();
		_delay_ms(5000);
	}
}

// unsigned int getDummyData(void)
// {
// 	unsigned int data;
// 	data = rand() % 42;						// Random number from 0 to 42
// 	return data;
// }

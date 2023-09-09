#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "ESP8266.h"

#define _OK "OK"
#define _CONNECT "CONNECT"
#define _CLOSED "CLOSED"

char ssid[] = "Wokwi-GUEST";
char psk[] = "";						// If no password leave it like this = "";
char api_key[] = "RQZXY61HSJURBPZL";			// Api key from ThingSpeak ThingHTTP app
char api_key_twitter[] = "";	// Api key from ThingSpeak ThingTweet app (optional)
int port = 80;									// Port for TCP connection
char buffer [64];								// Placeholder for handling data
char HTTP[512];									// HTTP request array placeholder
int dataCount = 0;

void ESPinit(void)
{
	// Reset ESP8266
	printf("AT+RST\r\n");
	lcd_set_cursor(0,1);
	lcd_puts("1            ");
	_delay_ms(100);
	lcd_set_cursor(0,1);
	lcd_puts("2            ");
	ping();					// Check if ready after reset
	lcd_set_cursor(0,1);
	lcd_puts("3            ");
	
	// Connect to Wi-Fi
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,psk);

	ping();					// Check if ready after reset
//	waitFor(_OK);
	
	// Client mode
	printf("AT+CWMODE=1\r\n");

	ping();					// Check if ready after reset
	//waitFor(_OK);
	
	// Enable multiple connections
	printf("AT+CIPMUX=1\r\n");
	ping();					// Check if ready after reset
	//waitFor(_OK);

	_delay_ms(500);
}

void waitFor(char* response)
{
	while(1){
		memset(buffer,0,strlen(buffer));		// Reset array
		scanf("\n%s", buffer);					// Get message from ESP8266
		if (strstr(buffer,response) == NULL)	// Finding specific ESP8266 response (returns NULL if not found)
		{
			_delay_ms(500);
		}else break;

	}
}

void addData(char* name, int data)
{
	if (dataCount == 0)
	{
		// HTTP GET request base
		strcat(HTTP,"GET https://api.thingspeak.com/update?api_key=");
		// Add api_key to HTTP request array
		strcat(HTTP,api_key);
	}
	// Add the data to be sent
	strcat(HTTP,"&");
	strcat(HTTP,name);
	strcat(HTTP,"=");
	memset(buffer,0,strlen(buffer));
	itoa(data,buffer,10);				// Transform integer to string
	strcat(HTTP,buffer);
	dataCount++;
}

void pushData(void)
{
	// Check if ESP8266 is ready to send
	ping();
	
	// Start TCP connection with ThingSpeak on port 80 channel 0 (ESP8266 can handle 4 channels)
	printf("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",%d\r\n",port);
	ping();
//	waitFor(_OK);
	
	// Use channel 0 and define length of message
	printf("AT+CIPSEND=0,%d\r\n",strlen(HTTP)+34);	// 34 is the length of "HTTP/1.1 Host: api.thingspeak.com" added later on
	_delay_ms(1000);
	//ping();
	//waitFor(_OK);
//	waitFor(_OK);
	
	// Send HTTP request with data
	printf("%s\nHTTP/1.1 Host: api.thingspeak.com\r\n",HTTP);

	// Wait for connection to get closed
	ping();
//	waitFor(_CLOSED);
	printf("Data sent\n");
	
	// Reset HTTP array and close connection to be sure
	printf("AT+CIPCLOSE=0\r\n");
	memset(HTTP,0,strlen(HTTP));
	dataCount=0;
}

void ping(void)
{
	// Check if ESP8266 is responding to AT with OK
	for(int i = 0; i < 3;i++){
		printf("AT\r\n");
		memset(buffer,0,strlen(buffer));		// Reset array
		scanf("\n%s", buffer);					// Get message from ESP8266
		if (strstr(buffer,"OK") == NULL)		// Finding specific response (returns NULL if not found)
		{
			_delay_ms(1000);						// Default interval: 100ms
		} else break;
		
	}
}


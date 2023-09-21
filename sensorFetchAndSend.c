#include "thesupersensor.h"
#include "esp8266.h" 

void fetchAndSend(){
    int data = supersensor_get();				// Get dummy data
    addData("field1",data);
    data = supersensor_get();				// Get dummy data
    addData("field2",data);
    pushData();							// Push data to Firebase
}
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "thesupersensor_config.h"

void supersensor_init(){
    //whatever
    SUPERSENSOR_PORT |= 12;//
}

unsigned int supersensor_get(){
    //whatever
    SUPERSENSOR_PORT |= 12;
    return SUPERSENSOR_PORT &= (1<< SUPERSENSOR_PIN);
}





// file name: ldr.cpp

#include "ldr.h"
#include "Arduino.h"
#include "main.h"

unsigned int Light_intensity, duty;

void init_ldr(void)
{
   pinMode(GARDEN_LIGHT, OUTPUT);
   
}

void brightness_control(void)
{
   Light_intensity = analogRead(LDR_SENSOR); //0 to 1023

   duty = 255 - (Light_intensity / 4);

   analogWrite(GARDEN_LIGHT, duty);
  
}

// temperature_system.cpp

#include "temperature_system.h"
#include "Arduino.h"
#include "main.h"

float temperature;
void init_temperature_system(void)
{
  // setting heater and cooler GPIO pins as output pins
  pinMode(HEATER, OUTPUT);
  pinMode(COOLER, OUTPUT);
}
    

float read_temperature(void)
{
 // Read Temperature sensor and return the temperature
  int adc = analogRead(A0);  
  float mv = (adc / 1023.0) * 5000;
  temperature = mv / 10.0;
  return temperature;

}
void cooler_control(bool control) //recieving the state of the button on the mobile blynk app
{
   lcd.setCursor(8, 0); // second row
   // turn on/off the cooler here
   if(control)
   { 
    // turn on the cooler -> assign the digital value 1 to the cooler GPIO Pin
      digitalWrite(COOLER, 1);
      lcd.print("CLR_ON  ");
   }
   else{
      digitalWrite(COOLER, 0);
      lcd.print("CLR_OFF ");
   }
}
void heater_control(bool control)
{
   lcd.setCursor(8, 0); // second row
   if(control)
   { 
    // turn on the Heater -> assign the digital value 1 to the cooler GPIO Pin
      digitalWrite(HEATER, 1);
      lcd.print("HTR_ON ");
   }
   else{
      digitalWrite(HEATER, 0);
      lcd.print("HTR_OFF ");
   }
    
}

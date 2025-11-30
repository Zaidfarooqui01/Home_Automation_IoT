// file name: serial_tank.cpp
#include "HardwareSerial.h"

#include "serial_tank.h"
#include "Arduino.h"
#include "main.h"

unsigned int volume_s;
unsigned char value_h, value_l;

void init_serial_tank(void) 
{
    // connect arduino to blynk cloud
    //Serial.begin(19200);
    Serial.write(0xFF); //synchronize a comunicação
    Serial.write(0xFF);
    Serial.write(0xFF);   
}

unsigned int volume(void)
{
    Serial.write(CMD_VOLUME);
    // Check if data is available
    while(!Serial.available());
    value_h = Serial.read();
    while(!Serial.available());
    value_l = Serial.read();
    
    volume_s = value_h << 8 | value_l;

    return volume_s;
}

void enable_inlet(void)
{
    Serial.write(INLET_VALVE);
    Serial.write(ENABLE);
    
}  

void disable_inlet(void)
{
    Serial.write(INLET_VALVE);
    Serial.write(DISABLE);
}  

void enable_outlet(void)
{  
    Serial.write(OUTLET_VALVE);
    Serial.write(ENABLE);
    
}

void disable_outlet(void)
{  
    Serial.write(OUTLET_VALVE);
    Serial.write(DISABLE);
    
}

// file name: temperature_system.h

#ifndef TEMPERATURE_SYSTEM_H
#define TEMPERATURE_SYSTEM_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define HEATER                4
#define COOLER                5

extern LiquidCrystal_I2C lcd;
#define TEMPERATURE_SENSOR    A0


float read_temperature(void);
void init_temperature_system(void);
void cooler_control(bool control);
void heater_control(bool control);

#endif

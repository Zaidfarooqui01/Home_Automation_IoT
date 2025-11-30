/*
Title         :   Home automation using blynk
Description   :   To control light's brigntness with brightness,monitor temperature , monitor water level in the tank through blynk app
Pheripherals  :   Arduino UNO , Temperature system, LED, LDR module, Serial Tank, Blynk cloud, Blynk App.
*/
// file name: home_automation_blynk_controlled.ino

#define BLYNK_TEMPLATE_ID "TMPL3t8S9DGBz"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "iuBnehoqh_s3ainEEQoPOg9lzqooYfeL"

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);  

#include "ldr.h"
#include "main.h"
#include "temperature_system.h"
#include "serial_tank.h"

bool heater_sw = 0, inlet_sw = 0, outlet_sw = 0, cooler_sw = 0;

// object to update temperature on blynk app at particular period
BlynkTimer timer;



// This function is called every time the Virtual Pin 0 state changes
 /*To turn ON and OFF cooler based virtual PIN value*/
BLYNK_WRITE(COOLER_V_PIN)
{
  // Read and change the value on Pin
  cooler_sw = param.asInt();

  // Based on pin Val control heater and cooler
  cooler_control(cooler_sw);
  
}
 /*To turn ON and OFF heater based virtual PIN value*/
BLYNK_WRITE(HEATER_V_PIN )
{
  // Read and change the value on Pin
  heater_sw = param.asInt();

  // Based on pin Val control heater and cooler
  heater_control(heater_sw);
  
}
 /*To turn ON and OFF inlet vale based virtual PIN value*/
BLYNK_WRITE(INLET_V_PIN)
{
  inlet_sw = param.asInt();

    if(inlet_sw){
      enable_inlet();
      lcd.setCursor(8, 1);
      lcd.print("INFL:ON ");

    }else{
      disable_inlet();
      lcd.setCursor(8, 1);
      lcd.print("INFL:OFF ");
    }

}
 /*To turn ON and OFF outlet value based virtual switch value*/
BLYNK_WRITE(OUTLET_V_PIN)
{
  outlet_sw = param.asInt();
    if(outlet_sw){
      enable_outlet();
      lcd.setCursor(8, 1);
      lcd.print("OUTFL:ON ");

    }else{
      disable_outlet();
      lcd.setCursor(8, 1);
      lcd.print("OUTFL:OFF ");
    }
  }
 /* To display temperature and water volume as gauge on the Blynk App*/  
void update_temperature_reading()
{
  // we can send any value at any time.
  float t = read_temperature();
  Blynk.virtualWrite(TEMPERATURE_GAUGE, t);
  
  // send volume of water to blynk app on pin v1 
  Blynk.virtualWrite(WATER_VOL_GAUGE, volume());
  
}

 /*To turn off the heater if the temperature raises above 35 deg C*/
void handle_temp(void)
{
  //read the temperature and compare it 35 and if heater is on
  if(read_temperature() > 35.0 && heater_sw)
  {
    //turn off the heater and button on the bynk app also off
    heater_control(0);
    Blynk.virtualWrite(HEATER_V_PIN, 0);
    lcd.setCursor(8, 0);
    lcd.print("CutOff    ");
    lcd.clear();
    
  }
  
}

/*To control water volume above 2000ltrs*/
void handle_tank(void)
{
  // if volume of water less than 2000
  if(volume() < 2000 && inlet_sw == 0)
  {
    inlet_sw = 1;
    enable_inlet();
    Blynk.virtualWrite(INLET_V_PIN, 1);

    lcd.setCursor(8, 1);
    lcd.print("INFL:ON  ");

  }

}


void setup(void)
{
  init_ldr();                 // LDR connected to A1
  init_temperature_system();  // LM35 input
  Serial.begin(19200);

  Blynk.begin(BLYNK_AUTH_TOKEN);
  lcd.init();

  Wire.begin();
  
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.print("Home Automation...");
  delay(500);
  lcd.clear();

  //initialize the serial tank
  init_serial_tank();

  // updating values every 2 seconds, cannot send more than 10 values in 1 sec
  timer.setInterval(2000, update_temperature_reading);
}
float temp = 0.0;
unsigned int v;
void loop(void) 
{
    // control the heater and cooler from blynk app
    Blynk.run(); // button heater -> v0, cooler button -> v2, v1 -> temperature
    timer.run();
     //send the temp to the blynk app on virtual pin V1

    brightness_control();
    // read temp from temperature sensor LM35
    temp = read_temperature();


    handle_temp();

    // if volume of water goes less than 2000
    handle_tank();

    v = volume();
    //displaying on the clcd at 2nd row 1st clmn
    lcd.setCursor(0, 1);
    lcd.print("v:");
    lcd.print(v);

    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp); 

}




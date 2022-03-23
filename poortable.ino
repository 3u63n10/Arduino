
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High speed I2C
  
#include "Adafruit_AS726x.h"

//create the object
 Adafruit_AS726x ams;
 
uint16_t sensorValues[AS726x_NUM_CHANNELS];

void setup() {

  u8g2.begin();
   
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
    Serial.println("could not connect to sensor! Please check your wiring.");
    while(1);
  }
}

void loop() {
 
  ams.startMeasurement(); //begin a measurement
  
  bool rdy = false;
  while(!rdy){
    delay(5);
    rdy = ams.dataReady();
  }

  ams.readRawValues(sensorValues);

  float a = 1; // slope
  float b = 0; // intercep
  float F = (sensorValues[AS726x_ORANGE] - b ) / a;


  Serial.print(F *10); // App divides the value, keep it this way
  Serial.println();
  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_helvB12_tf);   // choose a suitable font
  u8g2.setCursor(0,12);    // write something to the internal memory
  u8g2.print("Fluoride");
  u8g2.setCursor(0,24);    // write something to the internal memory
  u8g2.print("concentration:");
  u8g2.setFont(u8g2_font_helvB24_tf); 
  u8g2.setCursor(0,60);    // write something to the internal memory
//  u8g2.print(sensorValues[AS726x_ORANGE], DEC); // Uncomment to measure calibration curve
  u8g2.print(F,1);
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.setCursor(70,60);    // write something to the internal memory
  u8g2.print("ppm");
  u8g2.sendBuffer();                    // transfer internal memory to the display
  delay(1000);  
  
}

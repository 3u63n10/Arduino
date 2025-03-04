#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Initialize the OLED display using hardware I2C on the default SCL/SDA pins.
// U8G2_R0 specifies no rotation and U8X8_PIN_NONE indicates no reset pin.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

#include "Adafruit_AS726x.h"

// Create the sensor object
Adafruit_AS726x ams;

// Array to store raw sensor values for all channels
uint16_t sensorValues[AS726x_NUM_CHANNELS];

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  
  // Initialize the OLED display
  u8g2.begin();
  
  // Configure the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the AS726x sensor and check for proper connection
  if (!ams.begin()){
    Serial.println("Could not connect to sensor! Please check your wiring.");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  // Start a sensor measurement
  ams.startMeasurement();
  
  // Wait until data is ready
  bool dataReady = false;
  while (!dataReady) {
    delay(5);
    dataReady = ams.dataReady();
  }

  // Read the raw sensor values into sensorValues array
  ams.readRawValues(sensorValues);

  // Apply calibration parameters (slope and intercept)
  // Currently, the calibration slope 'a' is set to 1 and intercept 'b' to 0.
  // Modify these values if calibration is needed.
  float a = 1.0; // Slope
  float b = 0.0; // Intercept
  float F = (sensorValues[AS726x_ORANGE] - b) / a;

  // Print the measurement to Serial.
  // Note: The value is multiplied by 10 to meet the requirements of the App.
  Serial.print(F * 10);
  Serial.println();

  // Update the OLED display with the measured fluoride concentration
  u8g2.clearBuffer();                         // Clear display buffer
  u8g2.setFont(u8g2_font_helvB12_tf);           // Set font for headings
  u8g2.setCursor(0, 12);
  u8g2.print("Fluoride");
  u8g2.setCursor(0, 24);
  u8g2.print("concentration:");
  u8g2.setFont(u8g2_font_helvB24_tf);           // Set larger font for numeric value
  u8g2.setCursor(0, 60);
  // Option to print raw sensor value for calibration: uncomment if needed
  // u8g2.print(sensorValues[AS726x_ORANGE], DEC);
  u8g2.print(F, 1);                           // Print the calibrated value with 1 decimal
  u8g2.setFont(u8g2_font_helvB12_tf);           // Set font for unit label
  u8g2.setCursor(70, 60);
  u8g2.print("ppm");                           // Display unit (ppm)
  u8g2.sendBuffer();                           // Render the buffer on the display

  // Wait for 1 second before taking the next measurement
  delay(1000);
}

#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <AS726X.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Initialize the sensor, SD card, and RTC
AS726X sensor;  // AS726X sensor object (e.g., AS7262)
LiquidCrystal_I2C lcd(0x27, 16, 4); // LCD using I2C (adjust address if necessary)
RTC_DS3231 rtc; // Real-Time Clock
const int chipSelect = 10; // SD card module chip select pin
char logFileName[12]; // Buffer for log file name (e.g., "LOG000.txt")

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize the SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card Initialization failed!");
    while(1) { delay(10); } // Halt execution if SD card fails to initialize
  }
  Serial.println("SD card initialized.");

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) { delay(10); } // Halt if RTC is not found
  }

  // If RTC lost power, reset time to compile time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // Adjust the RTC time (set only once; comment out if already set)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Create a new log file with a unique name
  createNewLogFile();

  // Write the current date to the first line of the log file
  writeDateToLogFile();

  // Initialize the AS726X sensor (e.g., AS7262)
  if (!sensor.begin()) { // Uses default I2C address (typically 0x49)
    Serial.println("AS7262 initialization failed!");
    while (1) { delay(10); } // Halt execution if sensor initialization fails
  }

  // Set sensor gain and integration time
  sensor.setGain(3);          // Set gain to 64x (library-specific value)
  sensor.setIntegrationTime(50); // Set integration time to 50 (units defined by library)

  // Initialize and clear the LCD display
  lcd.begin(16, 4);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(logFileName); // Display the current log file name
}

void loop() {
  // Get current timestamp in milliseconds
  unsigned long currentMillis = millis();

  // Take sensor measurements
  sensor.takeMeasurements();
  
  // Retrieve calibrated sensor values for different wavelengths
  float violet = sensor.getCalibratedViolet();
  float blue   = sensor.getCalibratedBlue();
  float green  = sensor.getCalibratedGreen();
  float yellow = sensor.getCalibratedYellow();
  float orange = sensor.getCalibratedOrange();
  float red    = sensor.getCalibratedRed();

  // Open the log file for appending data
  File dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    // Write timestamp and sensor data to the log file
    dataFile.print("Time: ");
    dataFile.print(currentMillis);
    dataFile.print(" ms\tV: ");
    dataFile.print(violet);
    dataFile.print("\tB: ");
    dataFile.print(blue);
    dataFile.print("\tG: ");
    dataFile.print(green);
    dataFile.print("\tY: ");
    dataFile.print(yellow);
    dataFile.print("\tO: ");
    dataFile.print(orange);
    dataFile.print("\tR: ");
    dataFile.println(red);
    dataFile.close();
    Serial.println("Data written to SD card.");
  } else {
    Serial.println("Error opening data file.");
  }

  // Print sensor data to the Serial monitor for debugging
  Serial.print("Time: ");
  Serial.print(currentMillis);
  Serial.print(" ms\tV: ");
  Serial.print(violet);
  Serial.print("\tB: ");
  Serial.print(blue);
  Serial.print("\tG: ");
  Serial.print(green);
  Serial.print("\tY: ");
  Serial.print(yellow);
  Serial.print("\tO: ");
  Serial.print(orange);
  Serial.print("\tR: ");
  Serial.println(red);

  // Display data on the LCD
  lcd.setCursor(0, 0);
  lcd.print(logFileName);
  lcd.print("  ");
  lcd.print(currentMillis / 1000);
  lcd.print("s");
  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.print(violet, 1);
  lcd.print(" B:");
  lcd.print(blue, 1);
  lcd.setCursor(0, 2);
  lcd.print("G:");
  lcd.print(green, 1);
  lcd.print(" Y:");
  lcd.print(yellow, 1);
  lcd.setCursor(0, 3);
  lcd.print("O:");
  lcd.print(orange, 1);
  lcd.print(" R:");
  lcd.print(red, 1);
  
  delay(200); // Short delay before next measurement
}

// Function to create a new log file with a unique name
void createNewLogFile() {
  for (int i = 1; i < 1000; i++) {
    sprintf(logFileName, "LOG%03d.txt", i);
    if (!SD.exists(logFileName)) {
      // Found an available file name, so break out of loop
      break;
    }
  }
}

// Function to write the current date and time to the log file
void writeDateToLogFile() {
  File dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    DateTime now = rtc.now();
    dataFile.print("Date: ");
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(" ");
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error opening data file to write date.");
  }
}

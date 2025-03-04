#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_AS7341.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Initialize the sensor, SD card, and RTC
Adafruit_AS7341 sensor;
LiquidCrystal_I2C lcd(0x27, 16, 4); // Adjust the I2C address if necessary
RTC_DS3231 rtc;
const int chipSelect = 10; // SD card module chip select pin
char logFileName[12]; // Buffer for log file name (e.g., "LOG000.txt")

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize the AS7341 sensor
  if (!sensor.begin()){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }
  
  // Configure sensor parameters
  sensor.setATIME(100);
  sensor.setASTEP(999);
  sensor.setGain(AS7341_GAIN_64X);
  sensor.setLEDCurrent(40); // Current in mA (range: 2-258 mA)
  sensor.enableLED(true);

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card Initialization failed!");
    // Halt further execution if SD card fails to initialize
    while (1) { delay(10); }
  }
  Serial.println("SD card initialized.");

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1) { delay(10); }
  }

  // If RTC lost power, set the time to compile time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // Set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Create a new log file with a unique name
  createNewLogFile();

  // Write the current date and time to the log file
  writeDateToLogFile();

  // Initialize and clear the LCD display
  lcd.begin(16, 4);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(logFileName); // Display the log file name
}

void loop() {
  uint16_t readings[12]; // Array to hold sensor raw data

  // Get current timestamp in milliseconds
  unsigned long currentMillis = millis();

  // Take sensor measurements from all channels
  if (!sensor.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
  }
  
  // Note: The conversion to basic counts is commented out since it is not used.
  // If needed, uncomment and use the 'counts' array accordingly.
  // float counts[12];
  // for (uint8_t i = 0; i < 12; i++) {
  //   if (i == 4 || i == 5) continue; // Skip duplicate clear/NIR readings (indices 4 and 5)
  //   counts[i] = sensor.toBasicCounts(readings[i]);
  // }

  // Open the log file for appending data
  File dataFile = SD.open(logFileName, FILE_WRITE);
  if (dataFile) {
    // Write timestamp and sensor readings to the log file
    dataFile.print("Time: ");
    dataFile.print(currentMillis);
    dataFile.print(" msec\tF1 415nm: ");
    dataFile.print(readings[0]);
    dataFile.print("\tF2 445nm: ");
    dataFile.print(readings[1]);
    dataFile.print("\tF3 480nm: ");
    dataFile.print(readings[2]);
    dataFile.print("\tF4 515nm: ");
    dataFile.print(readings[3]);
    dataFile.print("\tF5 555nm: ");
    dataFile.print(readings[6]);
    dataFile.print("\tF6 590nm: ");
    dataFile.print(readings[7]);
    dataFile.print("\tF7 630nm: ");
    dataFile.print(readings[8]);
    dataFile.print("\tF8 680nm: ");
    dataFile.print(readings[9]);
    dataFile.print("\tClear: ");
    dataFile.print(readings[10]);
    dataFile.print("\tNIR: ");
    dataFile.println(readings[11]);
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }

  // Print sensor data to the serial port for debugging
  Serial.print("Time: ");
  Serial.print(currentMillis);
  Serial.print(" msec\tF1 415nm: ");
  Serial.print(readings[0]);
  Serial.print("\tF2 445nm: ");
  Serial.print(readings[1]);
  Serial.print("\tF3 480nm: ");
  Serial.print(readings[2]);
  Serial.print("\tF4 515nm: ");
  Serial.print(readings[3]);
  Serial.print("\tF5 555nm: ");
  Serial.print(readings[6]);
  Serial.print("\tF6 590nm: ");
  Serial.print(readings[7]);
  Serial.print("\tF7 630nm: ");
  Serial.print(readings[8]);
  Serial.print("\tF8 680nm: ");
  Serial.print(readings[9]);
  Serial.print("\tClear: ");
  Serial.print(readings[10]);
  Serial.print("\tNIR: ");
  Serial.println(readings[11]);

  // Update LCD display with current data
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(logFileName);
  lcd.print(" ");
  lcd.print(currentMillis / 1000);
  lcd.print("s");
  lcd.setCursor(0, 1);
  lcd.print("F1:");
  lcd.print(readings[0]);
  lcd.print(" F2:");
  lcd.print(readings[1]);
  lcd.print(" F3:");
  lcd.print(readings[2]);
  lcd.setCursor(0, 2);
  lcd.print("F4:");
  lcd.print(readings[3]);
  lcd.print(" F5:");
  lcd.print(readings[6]);
  lcd.print(" F6:");
  lcd.print(readings[7]);
  lcd.setCursor(0, 3);
  lcd.print("F7:");
  lcd.print(readings[8]);
  lcd.print(" F8:");
  lcd.print(readings[9]);

  delay(500); // Short delay before the next measurement
}

void createNewLogFile() {
  // Generate a new log file name in the format "LOGxxx.txt" where xxx is a number
  for (int i = 1; i < 1000; i++) {
    sprintf(logFileName, "LOG%03d.txt", i);
    if (!SD.exists(logFileName)) {
      // Found an available log file name
      break;
    }
  }
}

void writeDateToLogFile() {
  // Open the log file to write the current date and time
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

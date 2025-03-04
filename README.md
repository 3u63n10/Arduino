# AS7262 Sensor Project – Arduino Uno with SD Shield

This project demonstrates the integration of an AS7262 spectral sensor with an SD card for data logging, a DS3231 RTC for time-stamping, and an I2C LCD display. The project is built on an Arduino Uno equipped with an SD shield.

## Overview

The system reads spectral data from the AS7262 sensor, logs the measurements along with timestamps to the SD card, and displays basic information on an I2C LCD. This setup is ideal for experiments where long-term data logging and real-time display of sensor readings are required.

## Features

- **Spectral Measurement:** Uses the AS7262 sensor to capture data across multiple wavelengths.
- **Data Logging:** Writes sensor data with timestamps to uniquely named log files on an SD card.
- **Real-Time Clock:** Integrates a DS3231 RTC module to provide accurate time information.
- **Display Output:** Uses a 16x4 I2C LCD to show the log file name and current measurement data.
- **Robust Error Handling:** Halts execution if any critical hardware (SD card, RTC, or sensor) fails to initialize.

## Hardware Requirements

- **Arduino Uno** (with SD shield)
- **AS7262 Sensor**
- **SD Card Module/SD Shield**
- **DS3231 RTC Module**
- **16x4 I2C LCD Display**
- Breadboard, jumper wires, and appropriate connectors

## Software Requirements

- Arduino IDE
- Required libraries:
  - `Wire`
  - `SD`
  - `SPI`
  - `AS726X` (for AS7262 sensor support)
  - `LiquidCrystal_I2C`
  - `RTClib`

## Setup and Installation

1. **Hardware Wiring:**  
   - Connect the AS7262 sensor via I2C (SCL/SDA) to the Arduino Uno.
   - Attach the SD shield to the Arduino Uno and insert a formatted SD card.
   - Connect the DS3231 RTC module via I2C.
   - Wire the 16x4 LCD display to the appropriate I2C pins.
   
2. **Software Configuration:**  
   - Install the required libraries in the Arduino IDE.
   - Open the provided sketch and adjust the I2C address of the LCD if necessary.
   
3. **Upload and Run:**  
   - Upload the code to the Arduino Uno.
   - Upon startup, the system creates a new log file, writes the current date and time, and begins logging sensor data.

## Code Structure

- **setup():**  
  Initializes the SD card, RTC, AS7262 sensor, and LCD. It also creates a new log file and writes the current date.
  
- **loop():**  
  Reads sensor measurements, logs the data along with a timestamp, prints the readings to the Serial monitor, and updates the LCD display.
  
- **Helper Functions:**  
  - `createNewLogFile()`: Generates a unique filename for logging.  
  - `writeDateToLogFile()`: Writes the current date and time from the RTC to the log file.

## Usage

- Connect the hardware as per the wiring instructions.
- Upload the sketch using the Arduino IDE.
- Monitor sensor readings via the Serial Monitor and on the attached LCD.
- Check the SD card for log files containing the recorded data.

# AS7262 Sensor Project – Seeeduino with Expansion Board

This project utilizes the AS7262 spectral sensor to capture spectral data and displays the calibrated results on an OLED display. The setup is implemented on a Seeeduino board equipped with a Seeeduino expansion board.

## Overview

The project reads spectral data from the AS7262 sensor, applies a simple linear calibration, and displays the results on a 128x64 OLED using the U8g2 library. The Seeeduino expansion board simplifies the integration of peripherals, making this project suitable for rapid prototyping and portable sensor applications.

## Features

- **Spectral Sensing:** Captures calibrated spectral data from the AS7262 sensor.
- **OLED Display:** Renders real-time measurement data on a 128x64 SSD1306 OLED.
- **Simple Calibration:** Applies adjustable linear calibration parameters (slope and intercept) to sensor readings.
- **Serial Debugging:** Outputs sensor data and calibration values to the Serial Monitor.
- **Efficient Data Acquisition:** Waits until sensor data is ready before reading measurements.

## Hardware Requirements

- **Seeeduino Board** (with Seeeduino expansion board)
- **AS7262 Sensor**
- Breadboard, jumper wires, and necessary connectors

## Software Requirements

- Arduino IDE
- Required libraries:
  - `U8g2lib`
  - `Wire`
  - `SPI` (if using hardware SPI)
  - `AS726X` (for AS7262 sensor support)

## Setup and Installation

1. **Hardware Assembly:**  
   - Connect the AS7262 sensor to the Seeeduino board via I2C (SCL/SDA).
   
2. **Software Configuration:**  
   - Install the required libraries using the Arduino Library Manager.
   - Open the provided sketch and verify that the I2C pins and display settings are correct.
   
3. **Upload and Run:**  
   - Upload the sketch to the Seeeduino board using the Arduino IDE.
   - The system will begin measuring sensor data, apply calibration, and display the results on the OLED. Debug information is also sent to the Serial Monitor.

## Code Structure

- **setup():**  
  Initializes the OLED display, configures the built-in LED, and starts communication with the AS7262 sensor.
  
- **loop():**  
  Triggers a sensor measurement, waits for data readiness, reads calibrated sensor values, prints them to the Serial Monitor, and updates the OLED display.
  
- **Calibration Section:**  
  A simple linear calibration is applied to the sensor reading using configurable slope (`a`) and intercept (`b`) values.

## Usage

- Assemble the Seeeduino board with the expansion shield and connect all components as specified.
- Upload the sketch with the Arduino IDE.
- View real-time sensor readings on the OLED display and use the Serial Monitor for debugging purposes.




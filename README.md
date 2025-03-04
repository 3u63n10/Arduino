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

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the Arduino community and contributors of the AS726X, RTClib, and LiquidCrystal_I2C libraries.
- Special thanks to hardware vendors for providing reliable sensor and peripheral modules.

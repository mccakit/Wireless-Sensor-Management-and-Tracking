# Wireless-Sensor-Management-and-Tracking

A set of tools for wireless sensor management and value tracking with a GUI, developed during an internship.

## Project Components

The project consists of four main programs:

1. Arduino sketch for serial communication from Arduino UNO to NodeMCU WiFi module.
2. Arduino sketch for reading the Serial port in NodeMCU and deploying a web server.
3. C++ program for fetching data via GET requests and storing it in a SQLite database.
4. C++ program for fetching data from the database and providing interactive plots and sensor management.

## Setup Instructions

### Hardware Setup

1. Connect the GND pin of Arduino and NodeMCU to the breadboard '-' line.
2. Connect 6-7 digital pins of Arduino to 6-7 digital pins of NodeMCU, using parallel resistors to lower voltage to 3.3V.
3. Connect an analog sensor of your choice to A0.
4. Connect NodeMCU to your PC using a data-capable microUSB cable.
5. Connect Arduino to your PC using its USB cable.

### Software Upload

1. Upload the UNO sketch from the 'UNO-TO_NODEMCU' folder to Arduino.
2. Upload the HYBRID sketch from the 'UNO-TO_NODEMCU' folder to NodeMCU.
3. Note the IP address displayed in the NodeMCU Serial Monitor. If not visible, try resetting NodeMCU.

## Usage

1. Disconnect USB cables from both devices.
2. Connect the 5V pin of Arduino UNO to NodeMCU VIN pin.
3. Run `Sensor-Database.exe`.
4. Run `Database-Sensor.exe`.
5. In the GUI, click "Add Sensor" and enter the IP address from the NodeMCU Serial Monitor.

## Contributing

[Add contribution guidelines if applicable]

## License

[Add license information if applicable]

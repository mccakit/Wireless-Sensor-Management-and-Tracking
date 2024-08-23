Wireless-Sensor-Management-and-Tracking
A set of tools I wrote during my internship that allows wireless sensor management and value tracking in a GUI.
The project is composed of 4 main programs:

An Arduino sketch designed for serial communication from Arduino UNO to NodeMCU WiFi module.
Another Arduino sketch designed for reading the Serial port in NodeMCU and deploying a web server.
A C++ program that fetches data via GET requests and stores it in a SQLite database.
Another C++ program that fetches data from the database and provides interactive plots and sensor management.

How to use:
Upload:

Connect the GND pin of Arduino and NodeMCU to the breadboard '-' line.
Connect 6-7 digital pins of Arduino to 6-7 digital pins of NodeMCU, making sure to lower voltage to 3.3V using parallel resistors.
Use the analog sensor of your choice and connect the output to A0.
Use a microUSB cable that can transfer data to connect NodeMCU to your PC.
Use the USB cable of Arduino to connect Arduino to your PC.
Upload the UNO sketch from the 'UNO-TO_NODEMCU' folder to Arduino.
Upload the HYBRID sketch from the 'UNO-TO_NODEMCU' folder to NodeMCU.
Copy the IP address from the Serial Monitor of NodeMCU. If you can't see it, resetting NodeMCU may help.

Usage:

Disconnect the USB cables from both devices, then connect the 5V pin of Arduino UNO to NodeMCU VIN pin.
Run Sensor-Database.exe.
Run Database-Sensor.exe.
In the GUI, click the "Add Sensor" button and paste the IP address you copied from the Serial Monitor.

Now you have a sensor you can track via Wifi!

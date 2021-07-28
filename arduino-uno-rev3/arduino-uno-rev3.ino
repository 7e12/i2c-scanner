/**
 * @author:  7e12
 * @file:    arduino-uno-rev3.ino
 * @date:    19 Jul 2021
 * @version: v1.0.0
 * @brief:   Arduino Uno Rev3 I2C scanner
**/

#include <Wire.h>

// User-defined macros
#define SERIAL_BAUD_RATE    115200
#define MAX_SCAN_ADDRESS    255
#define NEXT_SCAN_DELAY     5000    // ms

void setup() {
    // put your setup code here, to run once:
    // Set up serial debug
    Serial.begin(115200);
    while (!Serial); // Wait for serial monitor to get ready
    Serial.println("\n< I2C Scanner >\n");

    // Set up I2C bus
    Wire.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
    int dev_address, dev_return, dev_number = 0;

    Serial.println("Scanning...\n");

    // Scan addresses from 1 to MAX_SCAN_ADDRESS
    for (dev_address = 1; dev_address < MAX_SCAN_ADDRESS; ++dev_address) {
        Wire.beginTransmission(dev_address);
        dev_return = Wire.endTransmission();

        if (0 == dev_return) {
            Serial.print("Available I2C device at address 0x");
            if (dev_address < 16) Serial.print("0");
            Serial.print(dev_address, HEX);
            Serial.println("\n");
            ++dev_number;
        } else if (4 == dev_return) {
            Serial.print("Unknown error at address 0x");
            if (dev_address < 16) Serial.print("0");
            Serial.print(dev_address, HEX);
            Serial.println("\n");
        }
    }

    if (0 == dev_number) Serial.println("No available I2C devices found!\n");
    else Serial.println("Done!\n");

    delay(NEXT_SCAN_DELAY);
}

#include <Wire.h>

const uint8_t I2C_ADDRESS = 0x20;

uint8_t lower, upper, number;

void setup() {
    pinMode(13, OUTPUT);

    // Initialize serial console
    Serial.begin(9600);

    // Initialize I2C
    Wire.begin();
}

void loop() {
    Wire.requestFrom(I2C_ADDRESS, 2);

    // Get lower and upper bytes from i2c
    lower = ~Wire.read();
    upper = ~Wire.read();

    // We only need the lower part (8 switches)
    number = (uint8_t)lower;

    // Log output
    Serial.print("Number of people present: ");
    Serial.print(number);
    Serial.print("\r\n");

    delay(2000);
}

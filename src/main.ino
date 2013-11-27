#include <Wire.h>
#include "TM1637.h"

#define I2C_ADDRESS 0x20
#define DISP_CLK 2
#define DISP_DIO 3
#define DISP_BRIGHTNESS 4

uint8_t lower, upper, number;

TM1637 tm1637(DISP_CLK, DISP_DIO);
int8_t disp[] = {0x00, 0x00, 0x00, 0x00};

void setup() {
    // Initialize I2C
    Wire.begin();

    // Initialize display
    tm1637.set(DISP_BRIGHTNESS);
    tm1637.init();
    tm1637.clearDisplay();

    // Initialize serial console
    Serial.begin(9600);
}

void loop() {
    Wire.requestFrom(I2C_ADDRESS, 2);

    // Get lower and upper bytes from I²C
    lower = ~Wire.read();
    upper = ~Wire.read();

    // We only need the lower part (8 switches).
    // Make sure number has only 4 digits.
    number = lower % 10000;

    // Get the four digits
    disp[0] = number / 1000;
    disp[1] = number % 1000 / 100;
    disp[2] = number % 100 / 10;
    disp[3] = number % 10;

    // Display
    tm1637.display(disp);

    // Log output
    Serial.print("Number of people present: ");
    Serial.print(number);
    Serial.print("\r\n");

    delay(20);
}

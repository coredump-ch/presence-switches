#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include "TM1637.h"

#define I2C_ADDRESS 0x20
#define DISP_CLK 2
#define DISP_DIO 3
#define DISP_BRIGHTNESS 4

// Variables for I2C communication
uint8_t lower, upper, number;

// 7 segment display config
TM1637 tm1637(DISP_CLK, DISP_DIO);
int8_t disp[] = {0x00, 0x00, 0x00, 0x00};

// MAC address and IP address for ethernet controller.
static byte mac[] = {0xde, 0xad, 0xbe, 0xef, 0x13, 0x37};
static short port = 1337;
IPAddress ip(192, 168, 2, 222);

// Initialize ethernet server library on port 1337
EthernetServer server(port);

void setup() {
    // Initialize I2C
    Wire.begin();

    // Initialize display
    tm1637.set(DISP_BRIGHTNESS);
    tm1637.init();
    tm1637.clearDisplay();

    // Initialize serial console
    Serial.begin(9600);

    // Start the Ethernet connection and the server
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("Server is at ");
    Serial.print(Ethernet.localIP());
    Serial.print(":");
    Serial.println(port);
}

void loop() {
    // Get lower and upper bytes from I2C
    Wire.requestFrom(I2C_ADDRESS, 2);
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

    // Display number
    tm1637.display(disp);

    // Listen for incoming HTTP clients
    EthernetClient client = server.available();
    if (client) {
        Serial.println("New client:\n");

        // An HTTP request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);

                // If you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply.
                if (c == '\n'&& currentLineIsBlank) {
                    // Response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: application/json");
                    client.println("Connection: close");
                    client.println();

                    // Response body
                    client.print("{\"open\": ");
                    client.print(number > 0 ? "true" : "false");
                    client.print(", \"people\": ");
                    client.print(number);
                    client.println("}");

                    break;
                }

                if (c == '\n') {
                    currentLineIsBlank = true;
                } else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            }
        }

        // Give client time to receive the data
        delay(1);

        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
    }
}

#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Initialize the RFM95 LoRa module
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for the serial port to connect. Needed for native USB
    }

    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    // Reset the RFM95 module
    delay(10);
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    if (!rf95.init()) {
        Serial.println("RFM95 LoRa radio initialization failed!");
        while (1); // Halt further execution as RF module did not initialize
    }

    Serial.println("RFM95 LoRa radio initialization successful!");
    rf95.setSpreadingFactor(7); // Set spreading factor to balance range and speed
    rf95.setSignalBandwidth(500000); // Set bandwidth to 500kHz
    rf95.setCodingRate4(5); // Set coding rate to 4/5
}

void loop() {
    static String inputBuffer = ""; // Buffer to hold incoming serial data

    while (Serial.available() > 0) {
        char inChar = (char)Serial.read();
        inputBuffer += inChar;
        
        if (inputBuffer.endsWith("<EOT>")) {
            Serial.println("End of Transmission received.");
            // Perform any cleanup or reset necessary here
            
            inputBuffer = ""; // Clear the buffer to ensure it's clean for the next session
            return; // Optionally break out of loop or halt further processing
        }

        // Check if the end marker <END> has been reached
        if (inputBuffer.endsWith("<END>")) {
            // The complete message including <START> and <END> is now in inputBuffer
            Serial.println("Complete data received:");
            Serial.println(inputBuffer);

            // Transmit the complete message via LoRa
            Serial.println("Transmitting via LoRa...");
            rf95.send((uint8_t *)inputBuffer.c_str(), inputBuffer.length());
            rf95.waitPacketSent();
            Serial.println("Data transmitted via LoRa");

            // Clear the buffer for the next message
            inputBuffer = "";
        }

        // Check for the End of Transmission marker
        
    }
}

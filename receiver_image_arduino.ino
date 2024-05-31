#include <SPI.h>
#include <RH_RF95.h>
#include <Arduino.h> // For using String and other Arduino-specific functions

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the serial port to connect

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  if (!rf95.init()) {
    Serial.println("RFM95 LoRa radio initialization failed!");
    while (1); // Infinite loop if initialization fails
  }

  rf95.setTxPower(23, false); // Set the transmitter power to 23 dBm
  rf95.setSpreadingFactor(7); // Set the spreading factor
  rf95.setSignalBandwidth(500000); // Set the signal bandwidth
  rf95.setCodingRate4(5); // Set the coding rate
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // Convert the received bytes into a String object for easier manipulation
      String receivedData = String((char*)buf);

      // Look for the <EOT> tag
      if (receivedData.indexOf("<EOT>") != -1) {
        Serial.println("OVER");
      } else {
        // Look for the start and end tags
        int startIndex = receivedData.indexOf("<START>");
        int endIndex = receivedData.indexOf("<END>");

        if (startIndex != -1 && endIndex != -1 && endIndex > startIndex) {
          // Extract the text between <START> and <END>
          String message = receivedData.substring(startIndex + 7, endIndex); // +7 to skip "<START>"
          Serial.println(message);
        }
      }
    }
  }
}

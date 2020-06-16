#include <Arduino.h>
#include <SoftwareSerial.h>

#include "BTCommunicator.h"

// reintend code shift + alt + f

BTCommunicator com = BTCommunicator();

void setup() {
    Serial.begin(HC6_SPEED);
    Serial.println(F("Started"));
    com.setup();
}

void loop() {
    // uncomment after test
    // com.update();
    if (com.hc06.available()) {
        int data = com.hc06.read();
        Serial.write(data);
    }

    if (Serial.available()) {
        com.hc06.write(Serial.read());
    }
}

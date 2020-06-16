#include "BTCommunicator.h"

BTCommunicator::BTCommunicator()
    : hc06(BT_RX_PIN, BT_TX_PIN), receiveDataOffset(0), isReady(false) {
    // this->hc06 = SoftwareSerial(BT_RX_PIN, BT_TX_PIN);
}

void BTCommunicator::setup() {
    hc06.begin(HC6_SPEED);
    // need to run once
    // hc06.println(F("AT"));
    // hc06.println(F("AT+UART"));
    // hc06.println(F("AT+CMODE=1"));
    // hc06.println(F("AT+CMODE"));
    // hc06.println(F("AT+UART"));
    // hc06.println(F("AT+UART=57600,0,0"));
    // hc06.println(F("AT+UART"));
    // hc06.println(F("AT+NAME=LedBackPack 2"));
    // hc06.println(F("AT+PSWD:\"0305\""));
    // hc06.println(F("AT+RESET"));
}

void BTCommunicator::update() {
    if (hc06.available()) {
        int data = hc06.read();

        receivedBytes[receiveDataOffset] = data;
        receiveDataOffset++;
        if (receiveDataOffset == PACKAGE_SIZE) {
            onReceivePackage();
        } else if (receiveDataOffset >= 2 && receivedBytes[receiveDataOffset - 2] == '\r' && receivedBytes[receiveDataOffset - 1] == '\n') {
            receivedBytes[receiveDataOffset - 2] = '\0';
            onReceivePackage();
        }
    }
}

void BTCommunicator::onReceivePackage() {
    receiveDataOffset = 0;
    Serial.print("got: ");
    Serial.println(receivedBytes);
    if (strcmp(receivedBytes, "HI") == 0) {
        Serial.println(F("Sending pong"));
        delay(100);
        hc06.println(F("su12y12"));  // fucking hc06 skips most of charset symbols, hopefully uy exists...
                                     // const char resp[] = "HI!s:12x12\r\n";
                                     // for (int i=0;i < sizeof(resp)/sizeof(char); i++) {
                                     //   hc06.write(resp[i]);
                                     // }
                                     // for (int i= 0; i < 256; i++) {
                                     //   hc06.write((byte)i);
                                     // }
                                     // hc06.write("\r\n");
    } else {
        parsePackage();
    }
    resetBuffer();
}

void BTCommunicator::resetBuffer() {
    memset(receivedBytes, 0, sizeof(char) * PACKAGE_SIZE);
}

void BTCommunicator::parsePackage() {
    switch (receivedBytes[0]) {
        case PACKAGE_CODE_PING:
            break;
        case PACKAGE_CODE_REMOTE_COMMAND:
            onReceivedRemoteCommand(receivedBytes[1]);
            break;
        case PACKAGE_CODE_PLAIN_TEXT:
            break;
        case PACKAGE_CODE_IMAGE:
            break;
    }
}

void BTCommunicator::onReceivedRemoteCommand(uint8_t command) {
    switch (command) {
        case PACKAGE_REMOTE_COMMAND_brightnessDown:
            break;
        case PACKAGE_REMOTE_COMMAND_brightnessUp:
            break;
        case PACKAGE_REMOTE_COMMAND_prevSprite:
            break;
        case PACKAGE_REMOTE_COMMAND_nextSprite:
            break;
        case PACKAGE_REMOTE_COMMAND_displayText:
            break;
        case PACKAGE_REMOTE_COMMAND_displaySprite:
            break;
    }
}

void BTCommunicator::onReceivedPlainText() {
    // if size is 0 or more than 1 - ignore so far
    if (receivedBytes[2] != 1) return;
}
#ifndef BTCommunicator_h
#define BTCommunicator_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define HC6_SPEED 57600
#define PACKAGE_SIZE 32

#define PACKAGE_CODE_PING 1
#define PACKAGE_CODE_REMOTE_COMMAND 2
#define PACKAGE_CODE_PLAIN_TEXT 3
#define PACKAGE_CODE_IMAGE 4

#define PACKAGE_REMOTE_COMMAND_brightnessDown 1
#define PACKAGE_REMOTE_COMMAND_brightnessUp 2
#define PACKAGE_REMOTE_COMMAND_prevSprite 3
#define PACKAGE_REMOTE_COMMAND_nextSprite 4
#define PACKAGE_REMOTE_COMMAND_displayText 5
#define PACKAGE_REMOTE_COMMAND_displaySprite 6

#define BT_RX_PIN 2
#define BT_TX_PIN 3

class BTCommunicator {
   public:
    SoftwareSerial hc06;  //(BT_RX_PIN, BT_TX_PIN);
   private:
    char receivedBytes[PACKAGE_SIZE + 2];
    uint8_t receiveDataOffset;
    bool isReady;

   public:
    BTCommunicator();

    void setup();
    void update();

   private:
    void onReceivePackage();
    void resetBuffer();
    void parsePackage();
    void onReceivedRemoteCommand(uint8_t command);
    void onReceivedPlainText();
};

#endif
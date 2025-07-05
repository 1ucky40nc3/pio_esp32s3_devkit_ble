#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "config.h"
#include "led.h"

// BLE Server Name
#define bleServerName "ESP32-S3-DevKitC-1"
// Custom BLE Service UUID
#define SERVICE_UUID "fe0fadc2-a9dc-4566-96f5-dd8a4934dac2"
// Some time series data characteristic
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

bool deviceConnected = false;

// BLE Callbacks
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    turnLEDGreen();
  };
  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    turnLEDBlue();
  }
};

void setup()
{
  turnLEDOff();
  // Initialize the serial connection
  Serial.begin(SERIAL_BAUD);
  // // wait for Serial to come online (only for testing/development purposes)
  // while (!Serial)
  //   ;
  delay(DELAY_AFTER_SERIAL_INITIALIZED);
  Serial.println("Serial start");
  turnLEDWhite();

  // Create BLE Device
  BLEDevice::init(bleServerName);

  // Create BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic =
      pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

  pCharacteristic->setValue("Hello World says ESP32-S3-DevKitC-1");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  turnLEDBlue();
}

// the loop function runs over and over again forever
void loop()
{
  delay(2000);
}

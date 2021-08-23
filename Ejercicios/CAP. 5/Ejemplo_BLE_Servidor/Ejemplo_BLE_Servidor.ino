#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define UUID_SERVICIO        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define UUID_CARACTERISTICA_1  "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define UUID_CARACTERISTICA_2  "c631c487-3c02-40e9-a0dd-11a472f61dfd"

void setup() 
{
  BLEDevice::init("Servidor ESP32");
  BLEServer *Servidor1 = BLEDevice::createServer();
  BLEService *Servicio_A = Servidor1->createService(UUID_SERVICIO);
  
  BLECharacteristic *Caracteristica_1 = Servicio_A->createCharacteristic
  (UUID_CARACTERISTICA_1, 
   BLECharacteristic::PROPERTY_READ | 
   BLECharacteristic::PROPERTY_WRITE);
  Caracteristica_1->setValue("Mensaje 1 del ESP32");
  
  BLECharacteristic *Caracteristica_2 = Servicio_A->createCharacteristic
  (UUID_CARACTERISTICA_2, 
   BLECharacteristic::PROPERTY_READ | 
   BLECharacteristic::PROPERTY_WRITE);
  Caracteristica_2->setValue("Mensaje 2 del ESP32");

  Servicio_A->start();
  BLEAdvertising *enviarMensaje = BLEDevice::getAdvertising();
  enviarMensaje->addServiceUUID(UUID_SERVICIO);
  enviarMensaje->setScanResponse(true);
  enviarMensaje->setMinPreferred(0x06);
  enviarMensaje->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() 
{
}

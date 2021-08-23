#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define UUID_SERVICIO        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define UUID_CARACTERISTICA_1  "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* Servidor1 = NULL;
BLECharacteristic* Caracteristica_1 = NULL;

bool Dispositivo_conectado = false;
bool Anterior_dispositivo_conectado = false;
int Dato = 0;

class Llamadas_al_servidor: public BLEServerCallbacks 
{
    void onConnect(BLEServer* Servidor1) 
    {
      Dispositivo_conectado = true;
    };
    void onDisconnect(BLEServer* Servidor1) 
    {
      Dispositivo_conectado = false;
    }
};

void setup() 
{
  Serial.begin(115200);
  BLEDevice::init("Notificaciones ESP32");
  Servidor1 = BLEDevice::createServer();
  
  Servidor1->setCallbacks(new Llamadas_al_servidor());
  BLEService *Servicio_Notificaciones = Servidor1->createService(UUID_SERVICIO);

  Caracteristica_1 = Servicio_Notificaciones->createCharacteristic
  (UUID_CARACTERISTICA_1,
   BLECharacteristic::PROPERTY_READ   |
   BLECharacteristic::PROPERTY_WRITE  |
   BLECharacteristic::PROPERTY_NOTIFY |
   BLECharacteristic::PROPERTY_INDICATE);
                    
  Caracteristica_1->addDescriptor(new BLE2902());

  Servicio_Notificaciones->start();
  BLEAdvertising *enviarMensaje = BLEDevice::getAdvertising();
  enviarMensaje->addServiceUUID(UUID_SERVICIO);
  enviarMensaje->setScanResponse(false);
  enviarMensaje->setMinPreferred(0x0); 
  BLEDevice::startAdvertising();
  Serial.println("Esperando clientes...");
}

void loop() 
{
    if(Dispositivo_conectado) 
    {
      Caracteristica_1->setValue(Dato);
      Caracteristica_1->notify();
      Dato++;
      delay(1000);
    }
    
    if(!Dispositivo_conectado && Anterior_dispositivo_conectado) 
    {
      delay(500);
      Servidor1->startAdvertising();
      Serial.println("Enviando datos");
      Anterior_dispositivo_conectado = Dispositivo_conectado;
    }
    
    if(Dispositivo_conectado && !Anterior_dispositivo_conectado) 
    {
      Anterior_dispositivo_conectado = Dispositivo_conectado;
    }
}

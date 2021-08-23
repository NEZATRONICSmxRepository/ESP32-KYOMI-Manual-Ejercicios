#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "DHT.h"

#define UUID_SERVICIO "91bad492-b950-4226-aa2b-4ede9fa42f59"
#define UUID_CARACTERISTICA_CELSIUS "234cd7a8-3225-4d09-b290-f84acbab5791"
#define UUID_CARACTERISTICA_FAHRENHEIT "61901b28-abb5-4ff0-a01d-1f706ef6ccfe"
#define UUID_CARACTERISTICA_HUMEDAD "3cdcf7e4-72e6-4121-9bb1-0841d69a57dc"

BLEServer* Servidor_DHT11 = NULL;
BLECharacteristic* Caracteristica_CELSIUS = NULL;
BLECharacteristic* Caracteristica_FAHRENHEIT = NULL;
BLECharacteristic* Caracteristica_HUMEDAD = NULL;

float T_Celsius=0, T_Fahrenheit=0, Humedad=0;
char Temp_en_Celsius[6], Temp_en_Fahrenheit[6], P_Humedad[6];

const int GPIO_DHT = 14;
DHT dht(GPIO_DHT, DHT11);
bool Dispositivo_conectado = false;

class Llamadas_al_servidor: public BLEServerCallbacks 
{
    void onConnect(BLEServer* Servidor_DHT11) 
    {
      Dispositivo_conectado = true;
    };
    void onDisconnect(BLEServer* Servidor_DHT11) 
    {
      Dispositivo_conectado = false;
    }
};

void setup() 
{
  dht.begin();
  Serial.begin(115200);
  BLEDevice::init("Servidor ESP32 con DHT11");
  BLEServer *Servidor_DHT11 = BLEDevice::createServer();
  Servidor_DHT11->setCallbacks(new Llamadas_al_servidor());
  
  BLEService *Servicio1_DHT11 = Servidor_DHT11->createService(UUID_SERVICIO);

  Caracteristica_CELSIUS = Servicio1_DHT11->createCharacteristic
  (UUID_CARACTERISTICA_CELSIUS, 
   BLECharacteristic::PROPERTY_READ   |
   BLECharacteristic::PROPERTY_WRITE  |
   BLECharacteristic::PROPERTY_NOTIFY |
   BLECharacteristic::PROPERTY_INDICATE);
  Caracteristica_CELSIUS->addDescriptor(new BLE2902());

  Caracteristica_FAHRENHEIT = Servicio1_DHT11->createCharacteristic
  (UUID_CARACTERISTICA_FAHRENHEIT, 
   BLECharacteristic::PROPERTY_READ   |
   BLECharacteristic::PROPERTY_WRITE  |
   BLECharacteristic::PROPERTY_NOTIFY |
   BLECharacteristic::PROPERTY_INDICATE); 
  Caracteristica_FAHRENHEIT->addDescriptor(new BLE2902());

  Caracteristica_HUMEDAD = Servicio1_DHT11->createCharacteristic
  (UUID_CARACTERISTICA_HUMEDAD, 
   BLECharacteristic::PROPERTY_READ   |
   BLECharacteristic::PROPERTY_WRITE  |
   BLECharacteristic::PROPERTY_NOTIFY |
   BLECharacteristic::PROPERTY_INDICATE);
  Caracteristica_HUMEDAD->addDescriptor(new BLE2902());
  
  Servicio1_DHT11->start();
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
    T_Celsius = dht.readTemperature();
    T_Fahrenheit = dht.readTemperature(true);
    Humedad = dht.readHumidity();

    dtostrf(T_Celsius, 3, 2, Temp_en_Celsius);
    dtostrf(T_Fahrenheit, 3, 2, Temp_en_Fahrenheit);
    dtostrf(Humedad, 3, 2, P_Humedad);
    
    Caracteristica_CELSIUS->setValue(Temp_en_Celsius);
    Caracteristica_CELSIUS->notify();
    
    Caracteristica_FAHRENHEIT->setValue(Temp_en_Fahrenheit);
    Caracteristica_FAHRENHEIT->notify();
    
    Caracteristica_HUMEDAD->setValue(P_Humedad);
    Caracteristica_HUMEDAD->notify();
    
    Serial.print(T_Celsius);
    Serial.println("°C");
    Serial.print(T_Fahrenheit);
    Serial.println("°F");
    Serial.print(Humedad);
    Serial.println("%");
    
    if (isnan(T_Celsius) || isnan(T_Fahrenheit) || isnan(Humedad)) 
    {
      Serial.println("Lectura retrasada o fallida");
      Caracteristica_CELSIUS->setValue("--");
      Caracteristica_CELSIUS->notify();
    
      Caracteristica_FAHRENHEIT->setValue("--");
      Caracteristica_FAHRENHEIT->notify();
    
      Caracteristica_HUMEDAD->setValue("--");
      Caracteristica_HUMEDAD->notify();
    }
    delay(4000);
  }
}

#include "BLEDevice.h"

#define NOMBRE_SERVIDOR_DHT "Servidor ESP32 con DHT11"
#define UUID_SERVICIO "91bad492-b950-4226-aa2b-4ede9fa42f59"
#define UUID_CARACTERISTICA_CELSIUS "234cd7a8-3225-4d09-b290-f84acbab5791"
#define UUID_CARACTERISTICA_FAHRENHEIT "61901b28-abb5-4ff0-a01d-1f706ef6ccfe"
#define UUID_CARACTERISTICA_HUMEDAD "3cdcf7e4-72e6-4121-9bb1-0841d69a57dc"

BLEAddress *Direccion_SERVIDOR;
BLERemoteCharacteristic* CARACTERISTICA_CELSIUS_REMOTA;
BLERemoteCharacteristic* CARACTERISTICA_FAHRENHEIT_REMOTA;
BLERemoteCharacteristic* CARACTERISTICA_HUMEDAD_REMOTA;

const uint8_t notificacion_ON[] = {0x1, 0x0};

boolean Servidor_conectado = false;
boolean Estado_conexion = false;
char* temperatura_Celsius;
char* temperatura_Fahrenheit;
char* humedad;

boolean lectura_nueva_Celsius = false;
boolean lectura_nueva_Fahrenheit = false;
boolean lectura_nueva_humedad = false;

class BUSQUEDA_SERVIDOR: public BLEAdvertisedDeviceCallbacks 
{
  void onResult(BLEAdvertisedDevice Dispositivo_encontrado) 
  {
    if(Dispositivo_encontrado.getName() == NOMBRE_SERVIDOR_DHT) 
    { 
      Dispositivo_encontrado.getScan()->stop();
      Direccion_SERVIDOR = new BLEAddress(Dispositivo_encontrado.getAddress());
      Servidor_conectado = true;
      Serial.println("Se encontró el servidor, conectando...");
    }
  }
};

void setup() 
{
  Serial.begin(115200);
  Serial.println("Iniciando cliente...");

  BLEDevice::init("");
  BLEScan* escaneo_BLE = BLEDevice::getScan();
  escaneo_BLE->setAdvertisedDeviceCallbacks(new BUSQUEDA_SERVIDOR());
  escaneo_BLE->setActiveScan(true);
  escaneo_BLE->start(30);
}

bool conexion_Servidor(BLEAddress Direccion) 
{
   BLEClient* Cliente = BLEDevice::createClient();
   Cliente->connect(Direccion);
   Serial.println("Conectado al servidor.");
 
   BLERemoteService* SERVICIO_REMOTO = Cliente->getService(UUID_SERVICIO);
   if(SERVICIO_REMOTO == nullptr) 
   {
    Serial.println("No se encontró el servicio...");
    return (false);
   }

   CARACTERISTICA_CELSIUS_REMOTA = SERVICIO_REMOTO->getCharacteristic(UUID_CARACTERISTICA_CELSIUS);
   CARACTERISTICA_FAHRENHEIT_REMOTA = SERVICIO_REMOTO->getCharacteristic(UUID_CARACTERISTICA_FAHRENHEIT);
   CARACTERISTICA_HUMEDAD_REMOTA = SERVICIO_REMOTO->getCharacteristic(UUID_CARACTERISTICA_HUMEDAD);

   if(CARACTERISTICA_CELSIUS_REMOTA == nullptr || 
      CARACTERISTICA_FAHRENHEIT_REMOTA == nullptr || 
      CARACTERISTICA_HUMEDAD_REMOTA == nullptr) 
   {
    Serial.println("No se encontró la característica...");
    return false;
   }
   Serial.println("Se encontraron las características.");
   CARACTERISTICA_CELSIUS_REMOTA->registerForNotify(Notificacion_CELSIUS);
   CARACTERISTICA_FAHRENHEIT_REMOTA->registerForNotify(Notificacion_FAHRENHEIT);
   CARACTERISTICA_HUMEDAD_REMOTA->registerForNotify(Notificacion_HUMEDAD);
   return true;
}

void loop() 
{
  if(Servidor_conectado == true) 
  {
    if(conexion_Servidor(*Direccion_SERVIDOR)) 
    {
      Serial.println("Conexión correcta con el servidor");
      CARACTERISTICA_CELSIUS_REMOTA->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificacion_ON, 2, true);
      CARACTERISTICA_FAHRENHEIT_REMOTA->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificacion_ON, 2, true);
      CARACTERISTICA_HUMEDAD_REMOTA->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificacion_ON, 2, true);
      Estado_conexion = true;
    } 
    else 
    {
      Serial.println("Fallo en la conexión al servidor, reinicia el ESP32");
    }
    Servidor_conectado = false;
  }
  
  if(lectura_nueva_Celsius && lectura_nueva_Fahrenheit && lectura_nueva_humedad)
  {
    lectura_nueva_Celsius = false;
    lectura_nueva_Fahrenheit = false;
    lectura_nueva_humedad = false;
  }
  delay(1000);
}

static void Notificacion_CELSIUS(
  BLERemoteCharacteristic* 
  pBLERemoteCharacteristic, 
  uint8_t* DATOS, 
  size_t length, 
  bool isNotify) 
{
  temperatura_Celsius = (char*)DATOS;
  Serial.print(temperatura_Celsius);
  Serial.println("°C");
  lectura_nueva_Celsius = true;
}

static void Notificacion_FAHRENHEIT(
  BLERemoteCharacteristic* 
  pBLERemoteCharacteristic, 
  uint8_t* DATOS, 
  size_t length, 
  bool isNotify) 
{
  temperatura_Fahrenheit = (char*)DATOS;
  Serial.print(temperatura_Fahrenheit);
  Serial.println("°F");
  lectura_nueva_Fahrenheit = true;
}

static void Notificacion_HUMEDAD(
  BLERemoteCharacteristic* 
  pBLERemoteCharacteristic,
  uint8_t* DATOS, 
  size_t length, 
  bool isNotify) 
{
  humedad = (char*)DATOS;
  Serial.print(humedad);
  Serial.println("%");
  lectura_nueva_humedad = true;
}

#include "SPIFFS.h"
 
void setup() 
{
  Serial.begin(115200);
  
  if(!SPIFFS.begin(true))
  {
    Serial.println("Ocurrió un error al montar el sistema SPIFFS");
    return;
  }
  
  File ARCHIVO_1 = SPIFFS.open("/Prueba_1.txt");
  File ARCHIVO_2 = SPIFFS.open("/Prueba_2.txt");
  
  if(!ARCHIVO_1)
  {
    Serial.println("Ocurrió un error al abrir el archivo");
    return;
  }
  if(!ARCHIVO_2)
  {
    Serial.println("Ocurrió un error al abrir el archivo");
    return;
  }
  
  Serial.println("Contenido de Prueba_1.txt:");
  while(ARCHIVO_1.available())
  {
    Serial.write(ARCHIVO_1.read());
  }
  ARCHIVO_1.close();

  Serial.println("");
  Serial.println("Contenido de Prueba_2.txt:");
  while(ARCHIVO_2.available())
  {
    Serial.write(ARCHIVO_2.read());
  }
  ARCHIVO_2.close();
}
 
void loop() 
{
  
}

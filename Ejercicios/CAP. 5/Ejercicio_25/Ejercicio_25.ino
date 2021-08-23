#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

String ESTADO_LEDS="";
const int GPIO12=12, GPIO14=14;

void setup() 
{
  Serial.begin(115200);
  pinMode(GPIO12, OUTPUT);
  pinMode(GPIO14, OUTPUT);
  digitalWrite(GPIO12,LOW);
  digitalWrite(GPIO14,LOW);
  SerialBT.begin("ESP32 BT Serial"); 
}

void loop() 
{
  if(SerialBT.available())
  {
    char Mensaje_Entrante=SerialBT.read();
    if(Mensaje_Entrante!='\n')
    {
      ESTADO_LEDS += String(Mensaje_Entrante);
    }
    else
    {
      ESTADO_LEDS = "";
    }
  }
  
  if(ESTADO_LEDS=="GPIO12_ON") 
  {
    SerialBT.println("GPIO12 Encendido");
    Serial.println("GPIO12 Encendido");
    digitalWrite(GPIO12,HIGH);
  }
  
  if (ESTADO_LEDS=="GPIO12_OFF") 
  {
    SerialBT.println("GPIO12 Apagado");
    Serial.println("GPIO12 Apagado");
    digitalWrite(GPIO12,LOW);
  }

  if (ESTADO_LEDS=="GPIO14_ON") 
  {
    SerialBT.println("GPIO14 Encendido");
    Serial.println("GPIO14 Encendido");
    digitalWrite(GPIO14,HIGH);
  }
  
  if (ESTADO_LEDS=="GPIO14_OFF") 
  {
    SerialBT.println("GPIO14 Apagado");
    Serial.println("GPIO14 Apagado");
    digitalWrite(GPIO14,LOW);
  }
  delay(10);
}

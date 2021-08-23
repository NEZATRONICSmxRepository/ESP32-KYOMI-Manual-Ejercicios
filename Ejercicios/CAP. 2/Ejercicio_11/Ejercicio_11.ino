#include <Preferences.h>
Preferences MEMORIA;
const int GPIO_SUMA=14,GPIO_RESTA=12;
int VALOR_SUMA_RESTA=0, VALOR_GUARDADO;

void setup() 
{
  MEMORIA.begin("ESPACIO1", false);
  VALOR_GUARDADO=MEMORIA.getInt("VALOR1",0);
  MEMORIA.end();
  
  MEMORIA.begin("ESPACIO1", false);
  MEMORIA.putInt("VALOR1", VALOR_SUMA_RESTA);
  MEMORIA.end();
   
  pinMode(GPIO_SUMA, INPUT_PULLDOWN);
  pinMode(GPIO_RESTA, INPUT_PULLDOWN);
  Serial.begin(115200);
}

void loop() 
{ 
  if(digitalRead(GPIO_SUMA)==HIGH)
  {
    VALOR_GUARDADO++;
    Serial.print("SUMA+1=");
    GUARDADO();
  }
  if(digitalRead(GPIO_RESTA)==HIGH)
  {
    VALOR_GUARDADO--;
    Serial.print("RESTA-1=");
    GUARDADO();
  }
  delay(200);
}


void GUARDADO()
{
  VALOR_SUMA_RESTA=VALOR_GUARDADO;
  MEMORIA.begin("ESPACIO1", false);
  MEMORIA.putInt("VALOR1", VALOR_SUMA_RESTA);
  MEMORIA.end();
  Serial.println(VALOR_SUMA_RESTA);
}

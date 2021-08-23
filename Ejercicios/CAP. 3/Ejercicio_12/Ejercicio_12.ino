#include <Preferences.h>
Preferences FLASH;

const unsigned int FACTOR_uS=1000000;  
const unsigned int TIEMPO_SLEEP=10;
const int GPIO_SUMA_FLASH=14, GPIO_SUMA_RTC=12, GPIO_DEEPSLEEP=27;

int VALOR_SUMA_FLASH=0, VALOR_GUARDADO;
RTC_DATA_ATTR int VALOR_SUMA_RTC=0;

void setup()
{
  FLASH.begin("SUMA_FLASH", false);
  VALOR_GUARDADO=FLASH.getInt("VALOR",0);
  FLASH.end();
  
  FLASH.begin("SUMA_FLASH", false);
  FLASH.putInt("VALOR", VALOR_SUMA_FLASH);
  FLASH.end();

  esp_sleep_enable_timer_wakeup(TIEMPO_SLEEP*FACTOR_uS); 
   
  pinMode(GPIO_SUMA_FLASH, INPUT_PULLDOWN);
  pinMode(GPIO_SUMA_RTC, INPUT_PULLDOWN); 
  pinMode(GPIO_DEEPSLEEP, INPUT_PULLDOWN); 
  
  Serial.begin(115200);
  Serial.print("Valor recuperado de flash=");
  Serial.println(VALOR_GUARDADO);
  Serial.print("Valor recuperado de RTC=");
  Serial.println(VALOR_SUMA_RTC); 
}

void loop()
{
  if(digitalRead(GPIO_SUMA_FLASH)==HIGH)
  {
    VALOR_GUARDADO++;
    Serial.print("Suma en FLASH +1=");
    GUARDADO();
  }
  
  if(digitalRead(GPIO_SUMA_RTC)==HIGH)
  {
    VALOR_SUMA_RTC++;
    Serial.print("Suma en RTC +1=");
    Serial.println(VALOR_SUMA_RTC);
  }
  
  if(digitalRead(GPIO_DEEPSLEEP)==HIGH)
  {
    Serial.println("Modo DeepSleep 10 segundos");
    delay(200); 
    esp_deep_sleep_start();
  }
  delay(200);
}

void GUARDADO()
{
  VALOR_SUMA_FLASH=VALOR_GUARDADO;
  FLASH.begin("SUMA_FLASH", false);
  FLASH.putInt("VALOR", VALOR_SUMA_FLASH);
  FLASH.end();
  Serial.println(VALOR_SUMA_FLASH);
}



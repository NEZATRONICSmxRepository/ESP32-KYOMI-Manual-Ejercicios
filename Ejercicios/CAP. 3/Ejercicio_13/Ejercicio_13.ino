const int PINS_IZQ[5]={32,33,25,26,27}, PINS_DER[11]={23,22,21,19,18,5,17,16,4,0,15}, GPIO_BOTON=14;
RTC_DATA_ATTR int CONTADOR_DE_SECUENCIAS = 0;
int CONTADOR_FOR=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 Activo");

  for(CONTADOR_FOR=0;CONTADOR_FOR<=4;CONTADOR_FOR++)
  {
    pinMode(PINS_IZQ[CONTADOR_FOR],OUTPUT);
    digitalWrite(PINS_IZQ[CONTADOR_FOR],LOW); 
  }
  for(CONTADOR_FOR=0;CONTADOR_FOR<=10;CONTADOR_FOR++)
  {
    pinMode(PINS_DER[CONTADOR_FOR],OUTPUT); 
    digitalWrite(PINS_DER[CONTADOR_FOR],LOW);
  } 
  pinMode(GPIO_BOTON,INPUT_PULLDOWN);

  attachInterrupt(digitalPinToInterrupt(GPIO_BOTON),MODO_DEEPSLEEP,RISING);
  touchAttachInterrupt(T5,callback,5);
  esp_sleep_enable_touchpad_wakeup();
  
}

void loop()
{
  SECUENCIA_LEDS();
  CONTADOR_DE_SECUENCIAS++;
  Serial.print("Secuencia número:");
  Serial.println(CONTADOR_DE_SECUENCIAS);
  delay(50);
}

void SECUENCIA_LEDS()
{
  for(CONTADOR_FOR=0;CONTADOR_FOR<=3;CONTADOR_FOR++){digitalWrite(PINS_IZQ[CONTADOR_FOR],HIGH); delay(100);}
  for(CONTADOR_FOR=3;CONTADOR_FOR<=6;CONTADOR_FOR++){digitalWrite(PINS_DER[CONTADOR_FOR],HIGH); delay(100);}
  for(CONTADOR_FOR=0;CONTADOR_FOR<=3;CONTADOR_FOR++){digitalWrite(PINS_IZQ[CONTADOR_FOR],LOW); delay(100);}
  for(CONTADOR_FOR=3;CONTADOR_FOR<=6;CONTADOR_FOR++){digitalWrite(PINS_DER[CONTADOR_FOR],LOW); delay(100);}   
}

void MODO_DEEPSLEEP()
{
  esp_deep_sleep_start();
}

void callback()
{
}

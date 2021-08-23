const int PINS_IZQ[5]={32,33,25,26,27}, PINS_DER[11]={23,22,21,19,18,5,17,16,4,0,15}, BOTON_DEEP_SLEEP=14;
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
  pinMode(BOTON_DEEP_SLEEP,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOTON_DEEP_SLEEP),MODO_DEEPSLEEP,RISING);
  
  pinMode(12,INPUT_PULLDOWN);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, HIGH);
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


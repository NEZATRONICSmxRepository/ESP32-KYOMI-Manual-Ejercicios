#define MASCARA_GPIO 0x5000
const int PINS_DER[11]={23,22,21,19,18,5,17,16,4,0,15}, BOTON_DEEP_SLEEP=27;
int CONTADOR_FOR=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 Activo");

  for(CONTADOR_FOR=0;CONTADOR_FOR<=10;CONTADOR_FOR++)
  {
    pinMode(PINS_DER[CONTADOR_FOR],OUTPUT); 
    digitalWrite(PINS_DER[CONTADOR_FOR],LOW);
  } 
  pinMode(BOTON_DEEP_SLEEP,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOTON_DEEP_SLEEP),MODO_DEEPSLEEP,RISING);
  
  pinMode(12,INPUT);
  pinMode(14,INPUT);
  esp_sleep_enable_ext1_wakeup(MASCARA_GPIO, ESP_EXT1_WAKEUP_ALL_LOW);
}

void loop()
{
  SECUENCIA_LEDS();
}

void SECUENCIA_LEDS()
{
  for(CONTADOR_FOR=3;CONTADOR_FOR<=6;CONTADOR_FOR++){digitalWrite(PINS_DER[CONTADOR_FOR],HIGH); delay(100);}
  for(CONTADOR_FOR=3;CONTADOR_FOR<=6;CONTADOR_FOR++){digitalWrite(PINS_DER[CONTADOR_FOR],LOW); delay(100);}   
}

void MODO_DEEPSLEEP()
{
  esp_deep_sleep_start();
}


#define MASCARA_GPIO 0x5000
const int UMBRAL_TOUCH=5, TIEMPO_DEEP_SLEEP=10, FACTOR_uS=1000000, BOTON_DEEP_SLEEP=26;
int MODO_DESPERTADO, PIN_TOUCH;

void setup()
{
  Serial.begin(115200);
  Serial.println("ESP32 ACTIVO");
  pinMode(BOTON_DEEP_SLEEP,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BOTON_DEEP_SLEEP),MODO_DEEPSLEEP,RISING);
  pinMode(12,INPUT);
  pinMode(14,INPUT);
  
  RAZON_DESPERTADO();
  VER_PIN_TOUCH_DETECTADO();

  touchAttachInterrupt(T7, callback, UMBRAL_TOUCH);
  esp_sleep_enable_touchpad_wakeup();
  esp_sleep_enable_timer_wakeup(TIEMPO_DEEP_SLEEP*FACTOR_uS);
  esp_sleep_enable_ext1_wakeup(MASCARA_GPIO, ESP_EXT1_WAKEUP_ALL_LOW);
}

void loop()
{
}

void RAZON_DESPERTADO()
{
  MODO_DESPERTADO = esp_sleep_get_wakeup_cause();
  switch(MODO_DESPERTADO)
  {
    case 1  : Serial.println("Despertado por ext(0)"); break;
    case 2  : Serial.println("Despertado por ext(1)"); break;
    case 3  : Serial.println("Despertado por temporizador"); break;
    case 4  : Serial.println("Despertado por pin touch"); break;
  }
}

void VER_PIN_TOUCH_DETECTADO()
{
  PIN_TOUCH = esp_sleep_get_touchpad_wakeup_status();
  switch(PIN_TOUCH)
  {
    case 0  : Serial.println("Touch T0 detectado"); break;
    case 1  : Serial.println("Touch T1 detectado"); break;
    case 2  : Serial.println("Touch T2 detectado"); break;
    case 3  : Serial.println("Touch T3 detectado"); break;
    case 4  : Serial.println("Touch T4 detectado"); break;
    case 5  : Serial.println("Touch T5 detectado"); break;
    case 6  : Serial.println("Touch T6 detectado"); break;
    case 7  : Serial.println("Touch T7 detectado"); break;
    case 8  : Serial.println("Touch T8 detectado"); break;
    case 9  : Serial.println("Touch T9 detectado"); break;
  }
}

void MODO_DEEPSLEEP()
{
  esp_deep_sleep_start();
}

void callback()
{
}


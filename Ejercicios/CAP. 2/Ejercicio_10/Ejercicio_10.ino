const int GPIO_LED = 14, SENSOR_PIR = 27;
int TIEMPO_LED_SEGUNDOS=10;
unsigned long TIEMPO_ACTUAL = millis(), ULTIMA_ACTIVACION = 0;
bool ARRANCAR_TEMPORIZADOR = false;


void setup() 
{
  pinMode(SENSOR_PIR, INPUT_PULLUP);
  pinMode(GPIO_LED, OUTPUT);
  digitalWrite(GPIO_LED, LOW);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIR), DETECTA_MOVIMIENTO , RISING);
}

void loop() 
{
  TIEMPO_ACTUAL = millis();
  if(ARRANCAR_TEMPORIZADOR==true && (TIEMPO_ACTUAL - ULTIMA_ACTIVACION > (TIEMPO_LED_SEGUNDOS*1000))) 
  {
   Serial.println("No hay movimiento...");
   digitalWrite(GPIO_LED, LOW);
   ARRANCAR_TEMPORIZADOR = false;
  }
}

void DETECTA_MOVIMIENTO() 
{
  Serial.println("Hay movimiento!");
  digitalWrite(GPIO_LED, HIGH);
  ARRANCAR_TEMPORIZADOR = true;
  ULTIMA_ACTIVACION = millis();
}

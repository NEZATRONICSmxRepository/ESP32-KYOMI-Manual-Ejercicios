const int GPIO_MOTOR=14, GPIO_CONTROL=12, FRECUENCIA=20000, RESOLUCION=12;
void setup()
{
  ledcSetup(0, FRECUENCIA, RESOLUCION);
  ledcAttachPin(GPIO_MOTOR, 0);
  pinMode(GPIO_MOTOR,OUTPUT);
  pinMode(GPIO_CONTROL,INPUT_PULLDOWN);
  digitalWrite(GPIO_MOTOR, LOW);   
}

void loop() 
{
  ledcWrite(0,analogRead(GPIO_CONTROL));
}

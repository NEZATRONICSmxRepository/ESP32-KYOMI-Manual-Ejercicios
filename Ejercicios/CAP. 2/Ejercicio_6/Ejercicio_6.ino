const int GPIO_ROJO=27, GPIO_VERDE=26, GPIO_AZUL=25, FRECUENCIA=5000, RESOLUCION=6; 
void setup() 
{
  ledcSetup(0, FRECUENCIA, RESOLUCION);
  ledcAttachPin(GPIO_ROJO, 0);

  ledcSetup(1, FRECUENCIA, RESOLUCION);
  ledcAttachPin(GPIO_VERDE, 1);

  ledcSetup(2, FRECUENCIA, RESOLUCION);
  ledcAttachPin(GPIO_AZUL, 2);

  pinMode(GPIO_ROJO,OUTPUT);
  pinMode(GPIO_VERDE,OUTPUT);
  pinMode(GPIO_AZUL,OUTPUT);   
}

void loop() 
{
 COLOR_ROJO();
 COLOR_VERDE();
 COLOR_AZUL();
 COLOR_AMARILLO(63,16,0);
 COLOR_MORADO(63,0,32);
 COLOR_CIAN(0,63,63);
}

void COLOR_ROJO()
{
 ledcWrite(0,63);
 ledcWrite(1,0);
 ledcWrite(2,0);
 delay(1000);
}

void COLOR_VERDE()
{
 ledcWrite(0,0);
 ledcWrite(1,63);
 ledcWrite(2,0);
 delay(1000);
}

void COLOR_AZUL()
{
 ledcWrite(0,0);
 ledcWrite(1,0);
 ledcWrite(2,63);
 delay(1000);
}

void COLOR_AMARILLO(int ROJO, int VERDE, int AZUL)
{
 ledcWrite(0,ROJO);
 ledcWrite(1,VERDE);
 ledcWrite(2,AZUL);
 delay(1000);
}

void COLOR_MORADO(int ROJO, int VERDE, int AZUL)
{
 ledcWrite(0,ROJO);
 ledcWrite(1,VERDE);
 ledcWrite(2,AZUL);
 delay(1000);
}

void COLOR_CIAN(int ROJO, int VERDE, int AZUL)
{
 ledcWrite(0,ROJO);
 ledcWrite(1,VERDE);
 ledcWrite(2,AZUL);
 delay(1000);
}


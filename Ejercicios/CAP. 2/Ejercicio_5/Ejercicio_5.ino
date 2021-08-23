const int GPIO_27=27, GPIO_14=14, GPIO_12=12, FRECUENCIA_1=100000, RESOLUCION_1=8, FRECUENCIA_2=20000, RESOLUCION_2=10; 
int VALOR_PWM_1=0,VALOR_PWM_2=0;

void setup() 
{
 ledcSetup(0, FRECUENCIA_1, RESOLUCION_1);
 ledcAttachPin(GPIO_27, 0);
 ledcAttachPin(GPIO_14, 0);
 
 ledcSetup(1, FRECUENCIA_2, RESOLUCION_2);
 ledcAttachPin(GPIO_12, 1);
 
 pinMode(GPIO_27,OUTPUT);
 pinMode(GPIO_14,OUTPUT);
 pinMode(GPIO_12,OUTPUT);  
}

void loop() 
{
  for(VALOR_PWM_1=0; VALOR_PWM_1<=255; VALOR_PWM_1++)
  {
    ledcWrite(0, VALOR_PWM_1);
    delay(4);
  }
  for(VALOR_PWM_1=255; VALOR_PWM_1>=0; VALOR_PWM_1--)
  {
    ledcWrite(0, VALOR_PWM_1);
    delay(4);
  }

  for(VALOR_PWM_2=0; VALOR_PWM_2<=1023; VALOR_PWM_2++)
  {
    ledcWrite(1, VALOR_PWM_2);
    delay(4);
  }
  for(VALOR_PWM_2=1023; VALOR_PWM_2>=0; VALOR_PWM_2--)
  {
    ledcWrite(1, VALOR_PWM_2);
    delay(4);
  }

}

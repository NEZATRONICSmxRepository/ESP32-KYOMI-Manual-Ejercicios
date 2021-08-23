const int GPIO_IZQ[6]={32,33,25,26,27,12}, GPIO_DER[11]={23,22,21,19,18,5,17,16,4,0,15}, TOUCH_1=14, TOUCH_2=12; 
int contador_FOR=0, SECUENCIA=0, Valor_touch_1=0, ESTADO_1=0, Valor_touch_2=0, ESTADO_2=0;

void setup() 
{
  for(contador_FOR=0; contador_FOR<=5; contador_FOR++)
  {
    pinMode(GPIO_IZQ[contador_FOR],OUTPUT);
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  for(contador_FOR=0; contador_FOR<=10; contador_FOR++)
  {
    pinMode(GPIO_DER[contador_FOR],OUTPUT);
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  
  pinMode(TOUCH_1,INPUT);
  pinMode(TOUCH_2,INPUT);
  Serial.begin(115200);
}

void loop() 
{ 

  for(contador_FOR=0; contador_FOR<=50; contador_FOR++)
  {
    Valor_touch_1=Valor_touch_1+(100*touchRead(T6));
  }
  Valor_touch_1=Valor_touch_1/50;

  if(Valor_touch_1>=750)
  {
    ESTADO_1=0;
  }
  else
  {
    ESTADO_1=1;
  }

  for(contador_FOR=0; contador_FOR<=50; contador_FOR++)
  {
    Valor_touch_2=Valor_touch_2+(100*touchRead(T5));
  }
  Valor_touch_2=Valor_touch_2/50;

  if(Valor_touch_2>=750)
  {
    ESTADO_2=0;
  }
  else
  {
    ESTADO_2=1;
  }

  if(ESTADO_1==1 && ESTADO_2==0){SECUENCIA=0;}
  if(ESTADO_1==0 && ESTADO_2==1){SECUENCIA=1;}
  
  SECUENCIA=SECUENCIA;
  
  switch(SECUENCIA)
  {
    case 0:
      Serial.println("Secuencia Izquierda"); 
      for(contador_FOR=0; contador_FOR<=4; contador_FOR=contador_FOR+2)
      {
        digitalWrite(GPIO_IZQ[contador_FOR],HIGH);
      }
      for(contador_FOR=1; contador_FOR<=4; contador_FOR=contador_FOR+2)
      {
        digitalWrite(GPIO_IZQ[contador_FOR],LOW);
      }
      delay(80);
      for(contador_FOR=1; contador_FOR<=4; contador_FOR=contador_FOR+2)
      {
        digitalWrite(GPIO_IZQ[contador_FOR],HIGH);
      }
      for(contador_FOR=0; contador_FOR<=4; contador_FOR=contador_FOR+2)
      {
        digitalWrite(GPIO_IZQ[contador_FOR],LOW);
      }
      delay(80);
    break;
    
    case 1:
      Serial.println("Secuencia Derecha"); 
      for(contador_FOR=3; contador_FOR<=7; contador_FOR++)
      {
        digitalWrite(GPIO_DER[contador_FOR],HIGH);
        delay(20);
      }
      
      for(contador_FOR=3; contador_FOR<=7; contador_FOR++)
      {
        digitalWrite(GPIO_DER[contador_FOR],LOW);
        delay(20);
      }
    break;
  }

  for(contador_FOR=0; contador_FOR<=5; contador_FOR++)
  {
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  for(contador_FOR=0; contador_FOR<=10; contador_FOR++)
  {
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
}

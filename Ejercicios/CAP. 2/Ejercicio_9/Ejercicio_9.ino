const int GPIO_IZQ[7]={32,33,25,26,27,12,14}, GPIO_DER[11]={23,22,21,19,18,5,17,16,4,0,15};
int LECTURA_HALL=0, contador_FOR=0, NIVEL=0;

void setup()
{
  for(contador_FOR=0; contador_FOR<=6; contador_FOR++)
  {
    pinMode(GPIO_IZQ[contador_FOR],OUTPUT);
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  
  for(contador_FOR=0; contador_FOR<=10; contador_FOR++)
  {
    pinMode(GPIO_DER[contador_FOR],OUTPUT);
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  
  Serial.begin(115200);
}

void loop()
{
  for(contador_FOR=0;contador_FOR<=100;contador_FOR++)
  {
    LECTURA_HALL=LECTURA_HALL+hallRead();
  }
  LECTURA_HALL=LECTURA_HALL/100;
  Serial.println(LECTURA_HALL);
  
  if(LECTURA_HALL>=20 && LECTURA_HALL<40){NIVEL=1;}
  if(LECTURA_HALL>=40 && LECTURA_HALL<60){NIVEL=2;}
  if(LECTURA_HALL>=60){NIVEL=3;}
  
  if(LECTURA_HALL<=-20 && LECTURA_HALL>-40){NIVEL=-1;}
  if(LECTURA_HALL<=-40 && LECTURA_HALL>-60){NIVEL=-2;}
  if(LECTURA_HALL<=-60){NIVEL=-3;}

  for(contador_FOR=1;contador_FOR<=NIVEL;contador_FOR++)
  {
    digitalWrite(GPIO_IZQ[contador_FOR],HIGH);
    delay(1);
  }
  
  for(contador_FOR=3;contador_FOR<=((NIVEL*-1)+2);contador_FOR++)
  {
    digitalWrite(GPIO_DER[contador_FOR],HIGH);
    delay(1);
  }
  
  NIVEL=0;
  for(contador_FOR=0;contador_FOR<=6;contador_FOR++)
  {
    digitalWrite(GPIO_IZQ[contador_FOR],LOW);
  }
  for(contador_FOR=0;contador_FOR<=11;contador_FOR++)
  {
    digitalWrite(GPIO_DER[contador_FOR],LOW);
  }
}


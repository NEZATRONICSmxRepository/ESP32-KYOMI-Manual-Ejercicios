const int TOUCH=12,LED=14;
int Valor_touch=0,ESTADO=0,contador_FOR=0;

void setup() 
{
 pinMode(TOUCH, INPUT);
 pinMode(LED,OUTPUT);
 Serial.begin(115200);
}
void loop()   
{
 for(contador_FOR=0; contador_FOR<=50; contador_FOR++)
 {
   Valor_touch=Valor_touch+(100*touchRead(T5));
 }
 Valor_touch=Valor_touch/50;

 if(Valor_touch>=750)
 {
  ESTADO=0;
 }
 else
 {
  ESTADO=1;
 }

 if(ESTADO==1)
 {
   digitalWrite(LED,HIGH);
   Serial.println("El led está encendido");
 }
 else
 { 
   digitalWrite(LED,LOW);
   Serial.println("El led está apagado");
 }
}



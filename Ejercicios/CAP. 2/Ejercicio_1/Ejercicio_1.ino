int BOTON=33,LED=32,ESTADO_BOTON=0; 
void setup() 
{
  pinMode(BOTON, INPUT_PULLDOWN);
  pinMode(LED,OUTPUT); 
  Serial.begin(115200);
}
void loop() 
{
  ESTADO_BOTON=digitalRead(BOTON);
  if(ESTADO_BOTON==1)
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


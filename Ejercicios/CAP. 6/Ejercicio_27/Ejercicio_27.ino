int GRADOS=0, SENO=0, COSENO=0, AMPLITUD=127;
TaskHandle_t LECTURA_ADC;

void setup() 
{
  xTaskCreatePinnedToCore(
  LECTURA_Analogica,   
  "ADC",   
  10000,       
  NULL,        
  1,           
  &LECTURA_ADC,      
  0); 
                  
  Serial.begin(250000);
}

void loop() 
{
  for(GRADOS=0; GRADOS<360; GRADOS++)
  {
    SENO=AMPLITUD*sin((GRADOS*PI)/180);
    COSENO=AMPLITUD*cos((GRADOS*PI)/180);
    dacWrite(25,(127+SENO));
    dacWrite(26,(127+COSENO));
    delayMicroseconds(1388);
  }
}

void LECTURA_Analogica(void* pvParameters)
{
  while(true)
  {
    Serial.print(analogRead(32));
    Serial.print("\t");
    Serial.println(analogRead(33));
    delayMicroseconds(4164);
  } 
}

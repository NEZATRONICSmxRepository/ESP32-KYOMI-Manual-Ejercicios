TaskHandle_t TAREA_nucleo_1;
TaskHandle_t TAREA_nucleo_2;

const int GPIO_1_TAREA_1=14, GPIO_2_TAREA_1=12, GPIO_1_TAREA_2=4, GPIO_2_TAREA_2=0;

void setup() 
{
  Serial.begin(115200); 
  pinMode(GPIO_1_TAREA_1, OUTPUT);
  pinMode(GPIO_2_TAREA_1, OUTPUT);
  pinMode(GPIO_1_TAREA_2, OUTPUT);
  pinMode(GPIO_2_TAREA_2, OUTPUT);
  digitalWrite(GPIO_1_TAREA_1, LOW);
  digitalWrite(GPIO_2_TAREA_1, LOW);
  digitalWrite(GPIO_1_TAREA_2, LOW);
  digitalWrite(GPIO_2_TAREA_2, LOW);

  xTaskCreatePinnedToCore(
  TAREA_1,   
  "TAREA_n_1",   
  10000,       
  NULL,        
  1,           
  &TAREA_nucleo_1,      
  0);                           

  xTaskCreatePinnedToCore(
  TAREA_2,   
  "TAREA_n_2",   
  10000,       
  NULL,        
  1,           
  &TAREA_nucleo_2,      
  1);  
}

void TAREA_1(void* pvParameters)
{
  while(true)
  {
    SECUENCIA_NUCLEO_0();
    Serial.print("Esto está corriendo en el núcleo: ");
    Serial.println(xPortGetCoreID());
  } 
}

void TAREA_2(void* pvParameters)
{
  for(;;)
  {
    SECUENCIA_NUCLEO_1();
    Serial.print("Esto está corriendo en el núcleo: ");
    Serial.println(xPortGetCoreID());
  }
}

void SECUENCIA_NUCLEO_0()
{
  digitalWrite(GPIO_1_TAREA_1, HIGH);
  delay(500);
  digitalWrite(GPIO_2_TAREA_1, HIGH);
  delay(500);
  digitalWrite(GPIO_1_TAREA_1, LOW);
  delay(500);
  digitalWrite(GPIO_2_TAREA_1, LOW);
  delay(500);
}

void SECUENCIA_NUCLEO_1()
{
  digitalWrite(GPIO_1_TAREA_2, HIGH);
  delay(250);
  digitalWrite(GPIO_2_TAREA_2, HIGH);
  delay(250);
  digitalWrite(GPIO_1_TAREA_2, LOW);
  delay(250);
  digitalWrite(GPIO_2_TAREA_2, LOW);
  delay(250);
}

void loop()
{
}

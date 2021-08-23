#include <WiFi.h>
const char* ssid = " ";
const char* password = " ";
WiFiServer server(80);


String ENCABEZADO, PETICION_CLIENTE = "";
char CADENA_ENCABEZADO;
String PAGINA_WEB="<!DOCTYPE html> <html> <head> <title>ESP32 KYOMI Web Server</title> <meta name='viewport' content='width=device-width, initialscale=1'> <link rel='icon' href='data:,'> <style> html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; } .BOTON1 { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } .BOTON2 { background-color: #555555; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } </style> </head> <body> <h1>ESP32 KYOMI Web Server</h1> <p>ESTADO GPIO 26</p> <p><a href='/26/on'><button class='BOTON1'>ENCENDIDO</button></a> <a href='/26/off'><button class='BOTON2'>APAGADO</button></a></p> <p>ESTADO GPIO 27</p> <p><a href='/27/on'><button class='BOTON1'>ENCENDIDO</button></a> <a href='/27/off'><button class='BOTON2'>APAGADO</button></a></p> </body> </html>";

const int GPIO26 = 26;
const int GPIO27 = 27;

void setup() 
{
  Serial.begin(115200);
  pinMode(GPIO26, OUTPUT);
  pinMode(GPIO27, OUTPUT);
  digitalWrite(GPIO26, LOW);
  digitalWrite(GPIO27, LOW);

  Serial.print("Conectando a:");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); 
  if(client) 
  {                             
    Serial.println("Cliente conectado");   
    while(client.connected()) 
    { 
      if(client.available()) 
      {            
        CADENA_ENCABEZADO = client.read();           
        Serial.write(CADENA_ENCABEZADO);                   
        ENCABEZADO += CADENA_ENCABEZADO;
        if(CADENA_ENCABEZADO == '\n') 
        {                   
          if(PETICION_CLIENTE.length() == 0) 
          {
            RESPUESTA_NAVEGADOR();
            ACCIONES_HTML(ENCABEZADO);
            client.println(PAGINA_WEB);
            client.println();
            break;
          } 
          else 
          { 
            PETICION_CLIENTE = "";
          }
        } 
        else if(CADENA_ENCABEZADO != '\r') 
        {  
          PETICION_CLIENTE += CADENA_ENCABEZADO; 
        }
      }
    }
    ENCABEZADO = "";
    client.stop();
    Serial.println("Cliente desconectado");
    Serial.println("");
  }
}

void RESPUESTA_NAVEGADOR()
{
  WiFiClient client = server.available(); 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
}

void ACCIONES_HTML(String ENCABEZADO)
{
   if(ENCABEZADO.indexOf("GET /26/on")>=0) 
   {
    Serial.println("GPIO 26 ENCENDIDO");
    digitalWrite(GPIO26, HIGH);
   }  
            
   else if(ENCABEZADO.indexOf("GET /26/off")>=0) 
   {
    Serial.println("GPIO 26 APAGADO");
    digitalWrite(GPIO26, LOW);
   } 
            
   else if(ENCABEZADO.indexOf("GET /27/on")>=0) 
   {
    Serial.println("GPIO 27 ENCENDIDO");
    digitalWrite(GPIO27, HIGH);
   }
   
   else if(ENCABEZADO.indexOf("GET /27/off")>=0) 
   {
    Serial.println("GPIO 27 APAGADO");
    digitalWrite(GPIO27, LOW);
   }
}

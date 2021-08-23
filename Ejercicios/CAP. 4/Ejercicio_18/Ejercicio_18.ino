#include <WiFi.h>
const char* ssid = " ";
const char* password = " ";
WiFiServer server(80);


String ENCABEZADO, PETICION_CLIENTE = "";
char CADENA_ENCABEZADO;

String ESTADO_GPIO26="off",ESTADO_GPIO27="off";

String PAGINA_WEB_SECCION_1="<!DOCTYPE html> <html> <head> <title>ESP32 KYOMI Web Server</title> <meta name='viewport' content='width=device-width, initialscale=1'> <link rel='icon' href='data:,'> <style> html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; } .BOTON1 { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } .BOTON2 { background-color: #555555; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } </style> </head> <body> <h1>ESP32 KYOMI Web Server</h1> <p>ESTADO GPIO 26</p>";
String PAGINA_WEB_SECCION_2="";
String PAGINA_WEB_SECCION_3="<p>ESTADO GPIO 27</p>";
String PAGINA_WEB_SECCION_4="";
String PAGINA_WEB_SECCION_5="</body> </html>";

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
            
            if(ESTADO_GPIO26=="off")
            {
             PAGINA_WEB_SECCION_2="<p><a href='/26/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
            }
            else if(ESTADO_GPIO26=="on") 
            {
             PAGINA_WEB_SECCION_2="<p><a href='/26/off'><button class='BOTON2'>APAGAR</button></a></p>";
            }
            
            if(ESTADO_GPIO27=="off")
            {
             PAGINA_WEB_SECCION_4="<p><a href='/27/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
            }
            else if(ESTADO_GPIO27=="on") 
            {
             PAGINA_WEB_SECCION_4="<p><a href='/27/off'><button class='BOTON2'>APAGAR</button></a></p>";
            }
            
            client.println(PAGINA_WEB_SECCION_1);
            client.println(PAGINA_WEB_SECCION_2);
            client.println(PAGINA_WEB_SECCION_3);
            client.println(PAGINA_WEB_SECCION_4);
            client.println(PAGINA_WEB_SECCION_5);
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
    ESTADO_GPIO26="on";
   }  
            
   else if(ENCABEZADO.indexOf("GET /26/off")>=0) 
   {
    Serial.println("GPIO 26 APAGADO");
    digitalWrite(GPIO26, LOW);
    ESTADO_GPIO26="off";
   } 
            
   else if(ENCABEZADO.indexOf("GET /27/on")>=0) 
   {
    Serial.println("GPIO 27 ENCENDIDO");
    digitalWrite(GPIO27, HIGH);
    ESTADO_GPIO27="on";
   }
   
   else if(ENCABEZADO.indexOf("GET /27/off")>=0) 
   {
    Serial.println("GPIO 27 APAGADO");
    digitalWrite(GPIO27, LOW);
    ESTADO_GPIO27="off";
   }
}

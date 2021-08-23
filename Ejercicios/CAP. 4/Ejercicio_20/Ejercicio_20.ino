#include <WiFi.h>
const char* ssid = " ";
const char* password = " ";
WiFiServer server(80);

String ENCABEZADO, PETICION_CLIENTE = "";
char CADENA_ENCABEZADO;
String ESTADO_RELEVADOR="off; 

String PAGINA_WEB_SECCION_1="<!DOCTYPE html> <html> <head> <title>CONTROL DE RELEVADOR</title> <meta name='viewport' content='width=device-width, initialscale=1'> <link rel='icon' href='data:,'> <style> html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; } .BOTON1 { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } .BOTON2 { background-color: #555555; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } </style> </head> <body> <h1>CONTROL DE RELEVADOR</h1>";
String PAGINA_WEB_SECCION_2="";
String PAGINA_WEB_SECCION_3="</body> </html>";
 
const int GPIO_RELEVADOR = 14;

void setup() 
{
  Serial.begin(115200);
  pinMode(GPIO_RELEVADOR, OUTPUT);
  digitalWrite(GPIO_RELEVADOR, LOW);


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
            if(ENCABEZADO.indexOf("U0VSVklET1I6MTIzNGFiY2Q=") >= 0) 
            {
             RESPUESTA_NAVEGADOR();
             ACCIONES_HTML(ENCABEZADO);
            
             if(ESTADO_RELEVADOR=="off")
             {
              PAGINA_WEB_SECCION_2="<p>Relevador desactivado</p> <p><a href='/14/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
             }
             else if(ESTADO_RELEVADOR=="on") 
             {
              PAGINA_WEB_SECCION_2="<p>Relevador activado</p> <p><a href='/14/off'><button class='BOTON2'>APAGAR</button></a></p>";
             }
            
             client.println(PAGINA_WEB_SECCION_1);
             client.println(PAGINA_WEB_SECCION_2);
             client.println(PAGINA_WEB_SECCION_3);
             client.println();
             break;
            }
            else 
            {
             client.println("HTTP/1.1 401 Unauthorized");
             client.println("WWW-Authenticate: Basic realm=\"Secure\"");
             client.println("Content-Type: text/html");
             client.println();
             client.println("<html>Credenciales incorrectas</html>");
            }
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
   if(ENCABEZADO.indexOf("GET /14/on")>=0) 
   {
    Serial.println("RELEVADOR ENCENDIDO");
    digitalWrite(GPIO_RELEVADOR, HIGH);
    ESTADO_RELEVADOR ="on";
   }         
   else if(ENCABEZADO.indexOf("GET /14/off")>=0) 
   {
    Serial.println("RELEVADOR APAGADO");
    digitalWrite(GPIO_RELEVADOR, LOW);
    ESTADO_RELEVADOR ="off";
   }      
}

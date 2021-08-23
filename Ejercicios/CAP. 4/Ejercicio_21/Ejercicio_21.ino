#include <WiFi.h>
const char* ssid = " ";
const char* password = " ";
WiFiServer server(1000);

String ENCABEZADO, PETICION_CLIENTE = "";
char CADENA_ENCABEZADO;

String ESTADO_GPIO14="off", ESTADO_GPIO27="off", ESTADO_GPIO26="off";

String PAGINA_WEB_SECCION_1="<!DOCTYPE html> <html> <head> <title>CONTROL DE GPIOs </title> <meta name='viewport' content='width=device-width, initialscale=1' http-equiv='Content-Type' content='text/html; charset=UTF-8' /> <link rel='icon' href='data:,'> <style> html { font-family: Corbel; display: inline-block; margin: 0px auto; text-align: center; } body { background-image: url('https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fwallpapercave.com%2Fwp%2FaJ5IFty.jpg&f=1&nofb=1'); background-repeat: no-repeat; background-attachment: fixed; background-size: 100% 100%; } .BOTON1 { background-color: #FF0000; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } .BOTON2 { background-color: #002DCF; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; } </style> </head> <body> <h1>Control GPIOs por internet</h1>";
String PAGINA_WEB_SECCION_2="";
String PAGINA_WEB_SECCION_3="</body> </html>";
String PAGINA_WEB_SECCION_2_BOTON1="", PAGINA_WEB_SECCION_2_BOTON2="", PAGINA_WEB_SECCION_2_BOTON3=""; 

const int GPIO_14=14, GPIO_27=27, GPIO_26=26;
IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 200, 200);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);  
IPAddress secondaryDNS(8, 8, 4, 4);

void setup() 
{
  Serial.begin(115200);
  pinMode(GPIO_14, OUTPUT);
  pinMode(GPIO_27, OUTPUT);
  pinMode(GPIO_26, OUTPUT);
  digitalWrite(GPIO_14, LOW);
  digitalWrite(GPIO_27, LOW);
  digitalWrite(GPIO_26, LOW);

  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

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
             client.println("HTTP/1.1 200 OK");
             client.println("Content-type:text/html");
             client.println("Connection: close");
             client.println();

             ACCIONES_HTML(ENCABEZADO);

             if(ESTADO_GPIO14=="off")
             {
              PAGINA_WEB_SECCION_2_BOTON1="<p>El GPIO14 está apagado</p> <p><a href='/14/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
             }
             else if(ESTADO_GPIO14=="on") 
             {
              PAGINA_WEB_SECCION_2_BOTON1="<p>El GPIO14 está encendido</p> <p><a href='/14/off'><button class='BOTON2'>APAGAR</button></a></p>";
             }

            if(ESTADO_GPIO27=="off")
             {
              PAGINA_WEB_SECCION_2_BOTON2="<p>El GPIO27 está apagado</p> <p><a href='/27/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
             }
             else if(ESTADO_GPIO27=="on") 
             {
              PAGINA_WEB_SECCION_2_BOTON2="<p>El GPIO27 está encendido</p> <p><a href='/27/off'><button class='BOTON2'>APAGAR</button></a></p>";
             }

             if(ESTADO_GPIO26=="off")
             {
              PAGINA_WEB_SECCION_2_BOTON3="<p>El GPIO26 está apagado</p> <p><a href='/26/on'><button class='BOTON1'>ENCENDER</button></a></p>"; 
             }
             else if(ESTADO_GPIO26=="on") 
             {
              PAGINA_WEB_SECCION_2_BOTON3="<p>El GPIO26 está encendido</p> <p><a href='/26/off'><button class='BOTON2'>APAGAR</button></a></p>";
             }
              PAGINA_WEB_SECCION_2=PAGINA_WEB_SECCION_2_BOTON1+PAGINA_WEB_SECCION_2_BOTON2+PAGINA_WEB_SECCION_2_BOTON3;              
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
          else {PETICION_CLIENTE = "";}
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


void ACCIONES_HTML(String ENCABEZADO)
{
   if(ENCABEZADO.indexOf("GET /14/on")>=0) 
   {
    Serial.println("GPIO14 encendido");
    digitalWrite(GPIO_14, HIGH);
    ESTADO_GPIO14="on";
   }           
   else if(ENCABEZADO.indexOf("GET /14/off")>=0) 
   {
    Serial.println("GPIO14 apagado");
    digitalWrite(GPIO_14, LOW);
    ESTADO_GPIO14="off";
   } 

   else if(ENCABEZADO.indexOf("GET /27/on")>=0) 
   {
    Serial.println("GPIO27 encendido");
    digitalWrite(GPIO_27, HIGH);
    ESTADO_GPIO27="on";
   }
   else if(ENCABEZADO.indexOf("GET /27/off")>=0) 
   {
    Serial.println("GPIO27 apagado");
    digitalWrite(GPIO_27, LOW);
    ESTADO_GPIO27="off";
   } 

   else if(ENCABEZADO.indexOf("GET /26/on")>=0) 
   {
    Serial.println("GPIO26 encendido");
    digitalWrite(GPIO_26, HIGH);
    ESTADO_GPIO26="on";
   }
   else if(ENCABEZADO.indexOf("GET /26/off")>=0) 
   {
    Serial.println("GPIO26 apagado");
    digitalWrite(GPIO_26, LOW);
    ESTADO_GPIO26="off";
   }
}

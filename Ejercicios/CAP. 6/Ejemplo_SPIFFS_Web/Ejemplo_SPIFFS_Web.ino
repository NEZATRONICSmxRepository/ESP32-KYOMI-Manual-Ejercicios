#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = " ";
const char* password = " ";
AsyncWebServer server(1000);

IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 200, 200);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);  
IPAddress secondaryDNS(8, 8, 4, 4);

void setup()
{
  Serial.begin(115200);
  if(!SPIFFS.begin(true))
  {
    Serial.println("Ocurrió un error al montar el sistema SPIFFS");
    return;
  }

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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/DOC_HTML.html", String(), false, ENVIAR_DATOS);
  });
  server.on("/DOC_CSS.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/DOC_CSS.css", "text/css");
  });

  server.begin();
}
 
void loop()
{
  
}

String ENVIAR_DATOS(const String& var)
{
  return String();
}

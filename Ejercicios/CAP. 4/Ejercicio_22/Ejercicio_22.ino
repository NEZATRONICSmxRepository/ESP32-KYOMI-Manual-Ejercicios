#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = " ";
const char* password = " ";
AsyncWebServer server(1000);

IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 200, 200);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);  
IPAddress secondaryDNS(8, 8, 4, 4);

const int GPIO_DHT=14;
DHT dht(GPIO_DHT, DHT11);
float temperatura_C=0, temperatura_F=0, humedad=0;

const char PAGINA_WEB[]="<!DOCTYPE HTML> <html> <head> <title>Servidor DHT11</title> <meta name='viewport' content='width=device-width, initialscale=1' http-equiv='Content-Type' content='text/html; charset=UTF-8' /> <link rel='icon' href='data:,'> <style> html { font-family: Corbel; display: inline-block; margin: 0px auto; text-align: center; } body { background-image: url('https://i.pinimg.com/originals/9e/0b/e9/9e0be9abf2f2dfe0399f85cdc32681d2.jpg'); background-repeat: no-repeat; background-attachment: fixed; background-size: 100% 100%; } </style> </head> <body> <h1 style='color:#BAEFFF;'>Servidor de temperatura y Humedad DHT11</h1> <p style='color:#FFE6B3; font-size: 32px;'> <img src='https://image.flaticon.com/icons/png/512/1035/1035618.png' alt='TEMPERATURA' width='80' height='80'> Celsius: <span id='Lectura_temp_C'>%TEMPERATURA_C%</span> °C Fahrenheit: <span id='Lectura_temp_F'>%TEMPERATURA_F%</span> °F </p> <p style='color:#CCD4FF; font-size: 32px;'> <img src='https://image.flaticon.com/icons/png/512/777/777610.png' alt='HUMEDAD' width='80' height='80'> <span id='Lectura_humedad'>%HUMEDAD%</span> % </p> </body> <script> setInterval(function() { var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { document.getElementById('Lectura_temp_C').innerHTML = this.responseText; } }; xhttp.open('GET','/Temperatura-En-C', true); xhttp.send(); },2000); setInterval(function() { var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { document.getElementById('Lectura_temp_F').innerHTML = this.responseText; } }; xhttp.open('GET','/Temperatura-En-F', true); xhttp.send(); },2000); setInterval(function() { var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { document.getElementById('Lectura_humedad').innerHTML = this.responseText; } }; xhttp.open('GET', '/Humedad', true); xhttp.send(); },2000); </script> </html>";

void setup()
{
  Serial.begin(115200);
  pinMode(GPIO_DHT,INPUT);
  dht.begin();
  
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
    request->send_P(200, "text/html", PAGINA_WEB, ENVIAR_DATOS);
  });
  
  server.on("/Temperatura-En-C", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", TEMPERATURA_DHT_C().c_str());
  });

  server.on("/Temperatura-En-F", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", TEMPERATURA_DHT_F().c_str());
  });
  
  server.on("/Humedad", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", HUMEDAD_DHT().c_str());
  });

  server.begin();
}
 
void loop()
{
  
}

String ENVIAR_DATOS(const String& var)
{
  if(var == "TEMPERATURA_C")
  {
    return TEMPERATURA_DHT_C();
  }
  else if(var == "TEMPERATURA_F")
  {
    return TEMPERATURA_DHT_F();
  }
  else if(var == "HUMEDAD")
  {
    return HUMEDAD_DHT();
  }
  return String();
}

String TEMPERATURA_DHT_C() 
{
  temperatura_C = dht.readTemperature();
  if (isnan(temperatura_C)) 
  {    
    Serial.println("Lectura errónea de temp. Celsius");
    return "--";
  }
  else 
  {
    Serial.println(temperatura_C);
    return String(temperatura_C);
  }
}

String TEMPERATURA_DHT_F() 
{
  temperatura_F = dht.readTemperature(true);
  if (isnan(temperatura_F)) 
  {    
    Serial.println("Lectura errónea de temp. Farenheit");
    return "--";
  }
  else 
  {
    Serial.println(temperatura_F);
    return String(temperatura_F);
  }
}

String HUMEDAD_DHT() 
{
  humedad = dht.readHumidity();
  if (isnan(humedad)) 
  {
    Serial.println("Lectura errónea de humedad");
    return "--";
  }
  else 
  {
    Serial.println(humedad);
    return String(humedad);
  }
}

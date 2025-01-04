//Andrés Romano CI:4.760.801-9 Actividad Control Servo Int.Sist.Cont 2021
#include <ESP8266WiFi.h>
#include <Servo.h>

String ssid     = "";
String password = "";
WiFiServer server(80); //objeto de la clase WiFiServer
int estado = 0;
Servo servoMotor;

void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");

  servoMotor.attach(D4, 500, 2400);
  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED ) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("********************************************");
  Serial.print("Conectado a la red WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("macAdress: ");
  Serial.println(WiFi.macAddress());
  Serial.println("*********************************************");
  
  server.begin(); //begin() levantamos el servidor
  servoMotor.write(90); 
}

void loop() {
  
  WiFiClient client = server.available(); //objeto de la clase WiFiClient
  // avalaible() detecta un cliente nuevo del objeto de la clase WifiServer
  if(!client){
    return;
  }
  
  Serial.println("Nuevo cliente...");
  while(!client.available()){ //espera a un cliente diponible
    delay(1);
  }

  String peticion = client.readStringUntil('\r'); //lee la peticion del cliente
  Serial.println(peticion);
  client.flush(); //limpia la peticion del cliente

  if(peticion.indexOf("Servo=180") != -1)
  {
    estado=180;
    Serial.print("Angulo:  ");
    Serial.println(estado);
  }
  if(peticion.indexOf("Servo=0") != -1)
  {
    estado=0;
    Serial.print("Angulo:  ");
    Serial.println(estado);
  }

  servoMotor.write(estado);

  
  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println(""); 

    //INICIA LA PAGINA

client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>");
client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
client.println("<title>ServoMotor</title></head>");
client.println("<body style='font-family: Century gothic; width: 800;'><center>");
client.println("<div style='box-shadow: 0px 0px 20px 8px rgba(0,0,0,0.22); padding: 20px; width: 300px; display: inline-block; margin: 30px;'> ");
client.println("<h1>Servo 1</h1>");

if(estado==0)
  client.println("<h2>El servo motor está a la derecha</h2>");
else
  client.println("<h2>El servo motor está a la izquierda</h2>");
        
client.println("<button style='background-color:red;  color:white; border-radius: 10px; border-color: rgb(255, 0, 0);' ");
client.println("type='button' onClick=location.href='/Servo=0'><h2>GiroHorario</h2>");
client.println("</button> <button style='background-color:blue; color:white; border-radius: 10px; border-color: rgb(25, 255, 4);' ");
client.println("type='button' onClick=location.href='/Servo=180'><h2>GiroAntiHorario</h2>");
client.println("</button></div></center></body></html>");

    //FIN DE LA PAGINA

  delay(20);
  Serial.println("Peticion finalizada");
  Serial.println("");  
}

//Eugenio Perdomo, Germán Torres,  Andrés Romano
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <Servo.h>

#define MAX_ITEMS 7 //fecha + 6 servos
#define WAIT_TIME 30000

//----------------------------------------------------------------------------

// Sustituir por los datos de vuestro WiFi
const char* ssid = "Abierta";; // Rellena con el nombre de tu red WiFi
const char* password = ""; // Rellena con la contraseña de la red WiFi
String url = "http://tecnube.online/ti/andres.romano/status.info";//URL host

HTTPClient http;
WiFiClient client;

String line, d_info;
Servo servo1, servo2, servo3, servo4, servo5, servo6;
int servoPosIni;

void setup() 
{
  Serial.begin(115200);

  servo1.attach(D3, 500, 2400);
  servo2.attach(D4, 500, 2400);
  servo3.attach(D5, 500, 2400);
  servo4.attach(D6, 500, 2400);
  servo5.attach(D7, 500, 2400);
  servo6.attach(D8, 500, 2400);
  delay(10);

  // Conectar a la red WiFi
  /* Configura el ESP8266 como cliente WiFi. Si no se hace 
     se configura como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA); // Modo cliente WiFi
  WiFi.begin(ssid, password);

  // Espera a estar conectado a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectandose a: ");
  Serial.println(ssid);
  Serial.println("");
  Serial.println("WiFi conectado"); 
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP()); // Mostrar la direccion IP
  servoPosIni = 90;
  servo1.write(servoPosIni);
  servo2.write(servoPosIni);
  servo3.write(servoPosIni);
  servo4.write(servoPosIni);
  servo5.write(servoPosIni);
  servo6.write(servoPosIni);
}
//****************************************************************************
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, 0};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if( (data.charAt(i)==separator) || (i==maxIndex) ){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
//****************************************************************************

void loop() {
  Serial.print("conectando a ");
  Serial.println(url);
  http.begin(client, url); // <1KB payload

  int httpCode = http.GET();  // Realizar petición
  String payload = http.getString();  // Obtener respuesta

  Serial.printf("[HTTP] GET... code: %d\n", httpCode);   //Print HTTP return code
  Serial.println("Mostrando el contenido de Status.info: ");
  Serial.println(payload);    // Mostrar respuesta por serial

  http.end();  //Close connection

  // Consutar la memoria libre
  Serial.printf("\nMemoria libre en el ESP8266: %d Bytes\n\n",ESP.getFreeHeap());
  Serial.println("------");
  // Procesar la info recibida
  for (int i=0; i < MAX_ITEMS; i++){
    d_info = getValue(payload,';',i);
    
    if (i==0) {
      Serial.print("Fecha y hora: "); Serial.println(d_info);
    }    
    if (i==1) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo1.write(d_info.toInt());
      delay(3000);
    }
    if (i==2) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo2.write(d_info.toInt());
      delay(3000);
    }
    if (i==3) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo3.write(d_info.toInt());
      delay(3000);
    }
    if (i==4) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo4.write(d_info.toInt());
      delay(3000);
    }
    if (i==5) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo5.write(d_info.toInt());
      delay(3000);
    }
    if (i==6) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo6.write(d_info.toInt());
      delay(3000);
    }
  }
  delay(WAIT_TIME);
}

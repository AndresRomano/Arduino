//Eugenio Perdomo, Germán Torres,  Andrés Romano
#include <ESP8266WiFi.h> 
#include <Servo.h>

#define MAX_ITEMS 7 //fecha + 6 servos
#define WAIT_TIME 20000

//----------------------------------------------------------------------------

const char* ssid = "";; // Rellena con el nombre de tu red WiFi
const char* password = ""; // Rellena con la contraseña de la red WiFi

const char* host = "192.168.1.6"; // IP del host
const char* url_test = "https://192.168.1.6/misphp/Status.info"; //Ruta de status.info
String peticionHTTP= "GET /misphp/Status.info"; //comando de la petición 

String line, d_info;
Servo servo1, servo2, servo3, servo4, servo5, servo6;
int servoPosIni;
//****************************************************************************
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

  Serial.println();
  Serial.println();
  Serial.print("Conectandose a: ");
  Serial.println(ssid);
 
  /* Configura el ESP8266 como cliente WiFi. Si no se hace 
     se configura como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA); // Modo cliente WiFi
  WiFi.begin(ssid, password);

  // Espera a estar conectado a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

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
// Para obtener valores de una cadena con separadores
// Ejemplo de uso: 
// String p01 = getValue(data,';',0);
// String p02 = getValue(data,';',1);
// String p03 = getValue(data,';',2);
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

void loop() 
{
  Serial.print("conectando a ");
  Serial.println(host);
 
  // Crear el cliente
  WiFiClient client;
  const int httpPort = 80; // Puerto HTTP
  if (!client.connect(host, httpPort)) {  // Si hay error al conectar
    Serial.println("Ha fallado la conexión, todo mal che !");
    return;
  }
 
  // Crear la URL para la petición 
  Serial.print("URL de la petición: ");
  Serial.print(host); Serial.print(":"); Serial.print(httpPort);
  Serial.println(url_test);
 
  // Enviar la peticion
  client.println(peticionHTTP);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Superado el tiempo de espera !");
      client.stop();
      return;
    }
  }

  // Consutar la memoria libre --- Quedan un poco mas de 40 kB
  Serial.printf("\nMemoria libre en el ESP8266: %d Bytes\n\n",ESP.getFreeHeap());
  
  Serial.println("Mostrando el contenido de Status.info: "); 
  // Leer la respuesta y enviar al monitor serie
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.println(line);    
  }
  Serial.println("------");
  
  // Procesar la info recibida
  for (int i=0; i < MAX_ITEMS; i++){
    d_info = getValue(line,';',i);
    
    if (i==0) {
      Serial.print("Fecha y hora: "); Serial.println(d_info);
    }    
    if (i==1) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo1.write(d_info.toInt());
    }
    if (i==2) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo2.write(d_info.toInt());
    }
    if (i==3) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo3.write(d_info.toInt());
    }
    if (i==4) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo4.write(d_info.toInt());
    }
    if (i==5) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo5.write(d_info.toInt());
    }
    if (i==6) {
      Serial.print("Servo"); Serial.print(i); Serial.print(" = "); Serial.println(d_info.toInt());
      servo6.write(d_info.toInt());
    }
  }
  delay(WAIT_TIME);
  
}
//****************************************************************************

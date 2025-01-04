//Germán Torres, Andrés Romano
// Esta es la librería para utilizar las funciones de red del ESP8266
#include <ESP8266WiFi.h> 
#include <stdio.h>
#include <iostream>
#include <string>

#define ledPin1 D5
#define ledPin2 D6
#define ledPin3 D7
#define ledPin4 D8

const char* ssid = "";; // Rellena con el nombre de tu red WiFi
const char* password = ""; // Rellena con la contraseña de la red WiFi

const char* host = "192.168.1.6";
const char* url_test = "https://192.168.1.6/misphp/Status.info";

String line;
String Led1;
String Led2;
String Led3;
String Led4;
String uno = "1";

void setup() 
{
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT); // Se declara este LED y los siguientes
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin1, LOW); // Apaga los LEDs  
  digitalWrite(ledPin2, LOW); 
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  delay(10);
  // Conectamos a la red WiFi
  Serial.println(url_test); 
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a: ");
  Serial.println(ssid);
 
  /* Configuramos el ESP8266 como cliente WiFi. Si no lo hacemos 
     se configurará como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA); // Modo cliente WiFi
  WiFi.begin(ssid, password);

  // Esperamos a que estemos conectados a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado"); 
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP()); // Mostramos la IP
  Serial.println("//---------------------------------------------------------");
}

void loop() {
  Serial.print("conectando a ");
  Serial.println(host);
  // Creamos el cliente
  WiFiClient client;
  const int httpPort = 80; // Puerto HTTP
  
  if (!client.connect(host, httpPort)) {
    // ¿hay algún error al conectar?
    Serial.println("Ha fallado la conexión, todo mal che !");
    return;
  }
  
  Serial.print("URL de la petición: ");
  Serial.print(host);
  Serial.print(":");
  Serial.print(httpPort);
  Serial.println(url_test);
  
  Serial.println("//---------------------------------------------------------");   
  // Enviamos la petición 
  String peticionHTTP= "GET /misphp/Status.info";
  client.println(peticionHTTP);        
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Superado el tiempo de espera !");
      client.stop();
      return;
    }
  }
  Serial.println("Mostrando el contenido de Status.info: ");
 
  // Leemos la respuesta y la enviamos al monitor serie
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("//---------------------------------------------------------");
  Serial.print("Este será el estado del led 1: ");
  Led1=line[0];
  Serial.println(Led1);
  Serial.print("Este será el estado del led 2: ");
  Led2=line[1];
  Serial.println(Led2);
  Serial.print("Este será el estado del led 3: ");
  Led3=line[2];
  Serial.println(Led3);
  Serial.print("Este será el estado del led 4: ");
  Led4=line[3];
  Serial.println(Led4);

  if (Led1.compareTo(uno) == 0) { 
   Serial.println("Se prende LED 1");
     digitalWrite(ledPin1, HIGH);
  } else { 
    Serial.println("Se apaga LED 1");
    digitalWrite(ledPin1, LOW); 
  }

  if (Led2.compareTo(uno) == 0) { 
    Serial.println("Se prende LED 2");
    digitalWrite(ledPin2, HIGH);
  } else { 
    Serial.println("Se apaga LED 2");
    digitalWrite(ledPin2, LOW); 
  }

  if (Led3.compareTo(uno) == 0) { 
    Serial.println("Se prende LED 3");
    digitalWrite(ledPin3, HIGH);
  } else { 
    Serial.println("Se apaga LED 3");
    digitalWrite(ledPin3, LOW); 
  }

  if (Led4.compareTo(uno) == 0) { 
    Serial.println("Se prende LED 4");
    digitalWrite(ledPin4, HIGH);
  } else { 
    Serial.println("Se apaga LED 4");
    digitalWrite(ledPin4, LOW); 
  } 
  Serial.println("Próxima revisión en 60s.");
  Serial.println("//---------------------------------------------------------");
  delay(60000);
}

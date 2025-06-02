#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "LabTi";
const char* password = "10203040";

// IP fixo (ajuste conforme sua rede)
IPAddress local_IP(192, 168, 253, 176);        // IP desejado para o ESP32
IPAddress gateway(192, 168, 253, 200);         // IP do roteador
IPAddress subnet(255, 255, 254, 0);            // Máscara de sub-rede
IPAddress primaryDNS(8, 8, 8, 8);              // DNS (opcional)
IPAddress secondaryDNS(8, 8, 4, 4);            // DNS (opcional)

WebServer server(80);

// Função que envia o comando e responde via Web
void enviarComando(String comando) {
  if (comando == "LIGAR" || comando == "DESLIGAR") {
    Serial.println(comando);
    server.send(200, "text/plain", "Comando enviado: " + comando);
  } else {
    server.send(400, "text/plain", "Comando inválido.");
  }
}

// Função que configura todas as rotas
void configurarRotas() {
  server.on("/desligar", []() {
    enviarComando("DESLIGAR");
  });
  
  server.on("/ligar", []() {
    enviarComando("LIGAR");
  });
  
}

void setup() {
  Serial.begin(9600);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Falha ao configurar IP estático.");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  configurarRotas(); // <- Chamada correta aqui
  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  server.handleClient();
}

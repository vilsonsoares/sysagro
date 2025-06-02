int rele = 7;

void setup() {
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    Serial.print("Comando recebido: [");
    Serial.print(comando);
    Serial.println("]");

    if (comando == "LIGAR") {
      digitalWrite(rele, LOW);
    } else if (comando == "DESLIGAR") {
      digitalWrite(rele, HIGH);
    } else {
      Serial.println("Comando desconhecido");
    }
  }
}

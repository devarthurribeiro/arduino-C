const int trava =  8;
const int sensor =  12;

void setup() {
  Serial.begin(9600);
  pinMode(trava, OUTPUT);
  digitalWrite(trava, LOW);
}

char lerStringSerial(){
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }

  Serial.print("Recebi: ");
  Serial.println(conteudo);

  return conteudo;
}

void loop() {
  char dado;
  int aux;
  if(Serial.available() > 0){
    dado = lerStringSerial();
    if (dado == 'a'){
      Serial.println("Comando recebido");
      digitalWrite(trava, HIGH);
      delay(2000);
      aux = digitalRead(sensor);
      if(aux == 1) Serial.print(aux);
      else Serial.print(aux);
    }
  }
}

const int trava =  8;
const int sensor =  12;

void setup() {
  Serial.begin(9600);
  pinMode(trava, OUTPUT);
  digitalWrite(trava, LOW);
}
void loop() {
  char dado;
  int aux;
  if(Serial.available()){
    dado = Serial.read();
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

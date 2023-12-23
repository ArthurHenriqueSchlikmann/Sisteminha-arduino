#define ledR 2
#define ledG 3
#define ledB 4
#define x A3
#define y A4
#define potenciometro A1
#define audio A2
#define lcr A0
#define rele 7
#define segA 8
#define segB 9
#define segC 5
#define segD 13
#define segE 1
#define segF 10
#define segG 11
#define agua A5

int ligado = LOW;
int led = LOW;
int recebido = 0;
int atualizar = LOW;
int ativado = 0;
int relea = LOW;
int botaolig = LOW;
int num [10][7] {
  {segA, segB, segC, segD, segE, segF}, //zero
  {segB, segC}, //um
  {segA, segB, segE, segD, segG}, //dois
  {segA, segB, segC, segD, segG}, //três
  {segB, segC, segF, segG}, //quatro
  {segA, segC, segD, segF, segG}, //cinco
  {segA, segC, segD, segE, segF, segG}, //seis
  {segA, segB, segC}, //sete
  {segA, segB, segC, segE, segF, segG}, //oito
  {segA, segB, segC, segF, segG}, //nove
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
  Serial.println("Iniciando");
  pinMode(segD, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(12, INPUT);
  apaga();
}

void loop() {
  // put your main code here, to run repeatedly:  
  botaolig = digitalRead(12);
  switch(botaolig) {
    case 1:
      if(relea == HIGH) {relea = LOW;} else {relea = HIGH;}
      digitalWrite(rele, relea);
    break;
  }
  if(analogRead(x) >= 800) {
    if(led == HIGH) {led = LOW;} else {led = HIGH;}
    digitalWrite(ledB, led);
  }
  if(analogRead(x) <= 200) {
    if(analogRead(audio) >= 10) {
      digitalWrite(ledG, HIGH); 
    }
  } else {
    digitalWrite(ledG, LOW);
    apaga();
    numero(analogRead(audio));    
  }
  if(analogRead(y) <= 90) {
    Serial.println("0 no serial para acender a luz azul");
    Serial.println("1 no serial para acender ou apagar o led azul");
    Serial.println("2 no serial para ligar ou desligar todos os modulos");
    Serial.println("girar o joystic para a direita o mesmo que 1");
    Serial.println("girar o joystic para a esquerda acendera a luz verde se o som for mais que 10");
    Serial.println("girar o joystic para cima para exibir este menu");
    Serial.println("-----------------------------------------------------------------------------");
  }
  if(analogRead(y) >= 800) {
    apaga();
    numero(relea);
    delay(5000);
    apaga();
    numero(led);
    delay(5000);
    apaga();
    numero(recebido);
    delay(5000);
    apaga();
    numero(Serial.available());
    delay(5000);
    apaga();
    numero(agua);
    delay(5000);
    apaga();
  }
  if(Serial.available() > 0) {
    recebido = Serial.read();
    switch(recebido) {
        case '0':
        digitalWrite(ledB, HIGH);
        delay(5000);
        digitalWrite(ledB, LOW);
        break;
        case '1':
        if(led == LOW) {led = HIGH;} else {led = LOW;}
        digitalWrite(ledB, led);
        break;
        case '2':
          if(relea == HIGH) {relea = LOW;} else {relea = HIGH;}
          digitalWrite(rele, relea);
        break;
        }
  }
  Serial.print("temperatura ");
  Serial.println(analogRead(potenciometro));
  Serial.print("modulo joystic x ");
  Serial.println(analogRead(x));
  Serial.print("modulo joystic y ");
  Serial.println(analogRead(y));
  Serial.print("sensor de som ");
  Serial.println(analogRead(audio));
  Serial.print("luz ambiente ");
  Serial.println(analogRead(lcr));
  Serial.print("Ventuinha ");
  Serial.println(ligado);
  Serial.print("Rele ");
  Serial.println(relea);
  Serial.print("detector de agua ");
  Serial.println(agua);
  Serial.println("---------------------------------");
}

void rgb(int r, int g, int b) {
  analogWrite(ledR, r);
  analogWrite(ledG, g);
  analogWrite(ledB, b);
}

void apaga() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void numero(int n) {
  for(int i=0; i<7; i++) {
    digitalWrite(num[n][i], HIGH);
  }
}

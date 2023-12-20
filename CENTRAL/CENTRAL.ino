int ligado = LOW;
int led = LOW;
int recebido = 0;
int atualizar = LOW;
int ativado = 0;
int relea = LOW;
int botaolig = LOW;

#define ledR 2
#define ledG 3
#define ledB 4
#define buzzer 10
#define x A3
#define y A4
#define potenciometro A1
#define audio A2
#define lcr A0
#define rele 7
#define botao 13
#define clock_ 5
#define atualizacao 8
#define btnld 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
  Serial.println("Iniciando");
  pinMode(buzzer, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(clock_, OUTPUT);
  pinMode(atualizacao, OUTPUT);
  pinMode(botao, INPUT);
  pinMode(btnld, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:  
  botaolig = digitalRead(btnld);
  switch(botaolig) {
    case 1:
      if(relea == HIGH) {relea = LOW;} else {relea = HIGH;}
      digitalWrite(rele, relea);
    break;
  }
  if(analogRead(x) >= 900) {
     analogWrite(buzzer, analogRead(potenciometro));
     digitalWrite(ledR, HIGH);
     delay(5000);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledR, LOW);
    delay(5000);
  }
  if(analogRead(x) <= 200) {
    if(analogRead(A2) >= 20) {
      digitalWrite(ledG, HIGH); 
    }
  } else {
    digitalWrite(ledG, LOW);
  }
  if(analogRead(y) <= 90) {
    Serial.println("0 no serial para acender a luz azul");
    Serial.println("1 no serial para o buzzer na frequencia do potenciometro");
    Serial.println("2 no serial para acender ou apagar os led azul");
    Serial.println("3 no serial para usar o registrador de deslocamento");
    Serial.println("4 no serial para ligar ou desligar todos os modulos");
    Serial.println("girar o joystic para a direita o mesmo que 1");
    Serial.println("girar o joystic para a esquerda acendera a luz verde se o som for mais que 20");
    Serial.println("-----------------------------------------------------------------------------");
  }
  if(Serial.available() > 0) {
    recebido = Serial.read();
    switch(recebido) {
      case '1':
        if(ativado == 0) {
          analogWrite(buzzer, analogRead(potenciometro));
          digitalWrite(ledR, HIGH);
          delay(5000);
          ativado = 0;
          digitalWrite(buzzer, LOW);
          digitalWrite(ledR, LOW);
        }
        break;
        case '0':
        digitalWrite(ledB, HIGH);
        delay(5000);
        digitalWrite(ledB, LOW);
        break;
        case '2':
        if(led == LOW) {led = HIGH;} else {led = LOW;}
        digitalWrite(ledB, led);
        break;
        case '3':
        if(atualizar == LOW) {atualizar = HIGH;} else {atualizar = LOW;}
        if(atualizar == LOW) {led = LOW;} else {led = HIGH;}
        digitalWrite(ledG, led);
        digitalWrite(atualizacao, atualizar);
        break;
        case '4':
          if(relea == HIGH) {relea = LOW;} else {relea = HIGH;}
          digitalWrite(rele, relea);
        break;
        }
  }
  Serial.print("potenciometro ");
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
  Serial.print("Relé ");
  Serial.println(relea);
  Serial.println("---------------------------------");
}

void rgb(int r, int g, int b) {
  analogWrite(ledR, r);
  analogWrite(ledG, g);
  analogWrite(ledB, b);
}

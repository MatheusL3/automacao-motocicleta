#include <Servo.h>

//Entradas
int btn_escape          = 05;    //D1 - 05  botão escape
int sinal_seta          = 15;    //D8 - 15 setas
int sinal_pos_ignicao   = 14;    //D5 - 14  pós-ignição
int sinal_freio         = 04;    //D2 - 04 freio


//Saidas
int farol_milha       = 16;   //D0 - 16  farol de milha
int freio             = 00;   //D3 - 00   // freio
int servo_escape      = 02;   //D4 - 02   // escape motor
//int ligar_ignicao   = 13;   //D7 - 13   // chave ignição
//int acionar_partida = 12;   //06 - 12     // acionar partida

Servo servo;
int escape_status = 0; //0:fechado; 1:aberto; 2:Personalizado;

void setup()
{
  pinMode(btn_escape,         INPUT);
  pinMode(sinal_seta,         INPUT);
  pinMode(sinal_freio,        INPUT);
  pinMode(sinal_pos_ignicao,  INPUT);

  pinMode(farol_milha,        OUTPUT);
  pinMode(freio,              OUTPUT);
  pinMode(servo_escape,       OUTPUT);
  //pinMode(ligar_ignicao,      OUTPUT);
  //pinMode(acionar_partida,    OUTPUT);

  servo.attach(servo_escape);

  Serial.begin(9400);
  //colocar delay após cada comando.
}

void loop()
{
  //luz de freio
  byte byte_sinal_freio = digitalRead(sinal_freio);
  if ( byte_sinal_freio == HIGH) {/*Serial.print("freio acionado: "); Serial.println(byte_sinal_freio);*/
    digitalWrite(freio, HIGH); delay(100); digitalWrite(freio, LOW); delay(100); digitalWrite(freio, HIGH); delay(100); digitalWrite(freio, LOW); delay(100);
    digitalWrite(freio, HIGH); delay(100); digitalWrite(freio, LOW); delay(100); digitalWrite(freio, HIGH); delay(100); digitalWrite(freio, LOW); delay(100); digitalWrite(freio, HIGH); delay(15);
    while ( byte_sinal_freio  == HIGH) {
      byte_sinal_freio = digitalRead(sinal_freio); delay(15);
    }
    digitalWrite(freio, LOW); delay(15);
  }

  //faróis de milha
  byte byte_sinal_pos_ignicao = digitalRead(sinal_pos_ignicao);   /* Serial.print("pós ig: "); Serial.print(byte_sinal_pos_ignicao);*/
  byte byte_sinal_seta = digitalRead(sinal_seta);                 /* Serial.print(" seta: ");   Serial.println(byte_sinal_seta);*/
  if ( byte_sinal_pos_ignicao == LOW and byte_sinal_seta == HIGH ) {  /*Serial.print("acionou faróis: "); */
    digitalWrite(farol_milha, HIGH); delay(10000); digitalWrite(farol_milha, LOW); delay(15);
  }


  //escape
  byte byte_btn_escape = digitalRead(btn_escape); /*high abrir, low fechar*/    Serial.print("byte_btn_escape: "); Serial.println(byte_btn_escape);
  if ( byte_btn_escape == LOW and ( escape_status == 1 or escape_status == 2) ) {
    //fechar escapamento.
    int posicao=map(0, 0, 100, 0, 180);
    escape_status = 0;
    servo.write(posicao);
    delay(15);
  } 
  if ( byte_btn_escape == HIGH and ( escape_status == 0)) {
    //abrir escapamento
    int posicao=map(100, 0, 100, 0, 180);
    escape_status = 1;
    servo.write(posicao);
    delay(15);
  }
}







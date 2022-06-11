/*Autor: Gabriel Dargas
 * Versão 1.0
 */

#define pinSensorFora 13
#define pinSensorDentro 12
#define laser1 A1
#define laser2 A2
#define ESPERA 0
#define ENTRANDO 1
#define SAINDO 2

int pessoasTotal = 0;
int pessoasSala = 0;
int modo = ESPERA;


// Configuracao do display LCD
#include <LiquidCrystal.h> 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup() {
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  Serial.begin(9600);
  pinMode(pinSensorFora, INPUT);
  pinMode(pinSensorDentro, INPUT);
  // Informacoes iniciais do display
  lcd.begin(16, 2);
  lcd.setCursor(0,0);            
  lcd.print("Pessoas: 0 ");          
  lcd.setCursor(0,1);
  lcd.print("Total: 0");
}

  void sendState(){
    Serial.print(pessoasTotal);
    Serial.println("");
    }


void loop() {
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);

  bool estadoSensorFora   = digitalRead(pinSensorFora );
  bool estadoSensorDentro = digitalRead(pinSensorDentro );


 //se o sensor de fora for desligado, invocar a funcao entrando
 if(modo == ESPERA){
  if(estadoSensorFora == 1){
    modo = ENTRANDO;
  }
 }

 //se o sensor de dentro for desligado, invocar a funcao saindo
  if(modo == ESPERA){
  if(estadoSensorDentro == 1){
    modo = SAINDO;
  }
 }

if(modo == ENTRANDO){
  //se ambos sensores estiverem desligados, deve contabilizar
  if(estadoSensorFora == 1 && estadoSensorDentro == 1){
    pessoasSala = pessoasSala + 1;
    lcd.setCursor(9,0);
    lcd.print("");
    lcd.setCursor(9,0);
    lcd.print(pessoasSala);
    pessoasTotal = pessoasTotal +1;
    lcd.setCursor(7,1);
    lcd.print(pessoasTotal);
    sendState();
    delay(500);
    modo = ESPERA;

  }
}

if(modo == SAINDO){
  //se ambos sensores estiverem desligados, deve contabilizar
  if(estadoSensorFora == 1 && estadoSensorDentro == 1){
    pessoasSala = pessoasSala - 1;
    lcd.setCursor(9,0); 
    lcd.print("");
    lcd.setCursor(9,0); 
    lcd.print(pessoasSala);
    sendState();
    delay(500);
    modo = ESPERA;
  }
}

}

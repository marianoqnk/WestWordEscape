#include <Arduino.h>
#include "Pines.h"
#include "Config.h"
#include "Snake.h"
#include "Simon.h"

void setup()
{


  Serial.begin(115000);
  char mensajeInicial[]="MAQUINA PARA DOS OPERADORES: UNO COMBINA Y OTRO SECUENCIA";
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  setupSnake();
  setupSimon();
  //scrollMensaje(mensajeInicial);
  tone(PIN_ALTAVOZ,1000,500);
}
void loop()
{
  lazoSerpiente();
  loopSimon();
  //tone(3,1000,100);
  //delay(100);
}

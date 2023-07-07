#include <Arduino.h>
#include "Config.h"
#include "Snake.h"
#include "Simon.h"
void iniMatriz8x8(void)
{
  matrix.begin(0x70); // direccion I2C display
  matrix.setRotation(1);
  matrix.setTextSize(1);
  matrix.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
}
void setup()
{

  Serial.begin(115000);
  char mensajeInicial[] = MENSAJE_INICIAL;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  iniMatriz8x8();
  //scrollMensaje(mensajeInicial);
  setupSnake();
  setupSimon();
  tone(PIN_ALTAVOZ, NOTA_DO, 500);
}
void loop()
{
  lazoSerpiente();
  loopSimon();
}

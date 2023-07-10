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
  // char mensajeInicial[] = MENSAJE_INICIAL;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  iniMatriz8x8();
  // scrollMensaje(mensajeInicial);
  setupSnake();
  setupSimon();
  tone(PIN_ALTAVOZ, NOTA_DO, 500);
}
void loop()
{
  Serial.println("LAZO");
  iniSnake();
  lazoSerpiente();
  if (loopSimon())
  {
    Serial.println("WIN");
    hasGanado();
    delay(1000);
    goToLowPower();
  }
  else
  {
    hasPerdido();
    Serial.println("LOSS");
    if ((millis()-tickApagar) > TIEMPO_APAGADO_SIN_PULSAR_TECLA)
      goToLowPower();
  }
}

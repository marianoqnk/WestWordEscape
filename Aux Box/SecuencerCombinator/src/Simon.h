#include <Arduino.h>
#include <LowPower.h>
#include "Config.h"
int secuencia[INTENTOS];

bool delayOn = false;

void delayLowPower(unsigned long tiempo)
{
  unsigned long tick = millis();
  while ((millis() - tick) < tiempo && !lazoSerpiente())
  {
    delay(10);
  }
}
void enciendeLedAndPita(int n)
{
  tone(PIN_ALTAVOZ, notas[n], 100);
  digitalWrite(led[n], LOW);
  delayLowPower(TIEMPO_ON);
  digitalWrite(led[n], HIGH);
}
boolean leePulsador(int cual)
{
  int tiempo = TIEMPO_PULSAR / 10;
  for (int k = 0; k < tiempo; k++)
    for (int n = 0; n < BOTONES; n++)
    {
      if (serpienteMuerta)
        return false;
      if (!digitalRead(led[n]))
      {
        tickApagar = millis();
        enciendeLedAndPita(n);
        if (n == cual)
          return true;
        else
          return false;
      }
      delayLowPower(10);
    }
  return false;
}

void todosLeds(boolean encendidos)
{

  for (int n = 0; n < BOTONES; n++)
    digitalWrite(led[n], encendidos);
}

void lucesFinal()
{
  // azul,rojo,verde

  for (byte n = 0; n < 5; n++)
  {
    enciendeLedAndPita(0); // azul
    delayLowPower(TIEMPO_OFF);
  }
  for (byte n = 0; n < 7; n++)
  {
    enciendeLedAndPita(1); // rojo
    delayLowPower(TIEMPO_OFF);
  }
  for (byte n = 0; n < 4; n++)
  {
    enciendeLedAndPita(2); // Verde
    delayLowPower(TIEMPO_OFF);
  }
  delayLowPower(1000);
}

void ledsInicio()
{

  for (int n = 0; n < INTENTOS; n++)
  {
    secuencia[n] = random(BOTONES); // para eso utiliza randon
  }

  for (int k = 0; k < VECES_INTERMITENTE; k++)
  {
    for (int n = 0; n < BOTONES; n++)
      digitalWrite(led[n], !(n % 2));
    delayLowPower(TIEMPO_OFF);
    for (int n = 0; n < BOTONES; n++)
      digitalWrite(led[n], (n % 2));
    delayLowPower(TIEMPO_OFF);
  }
  todosLeds(HIGH);
  delayLowPower(TIEMPO_ON);
}

void ledsError()
{

  for (int k = 0; k < VECES_INTERMITENTE; k++)
  {
    todosLeds(LOW);
    delayLowPower(TIEMPO_ON);
    todosLeds(HIGH);
    delayLowPower(TIEMPO_OFF);
  }
}
void setupSimon()
{

  randomSeed(analogRead(A0)); // inicia el array con los numeros aleatorios
  for (int n = 0; n < BOTONES; n++)
  {
    pinMode(led[n], OUTPUT);
  }
  tickApagar = millis();
}
void secuenciaCorrecta()
{
  todosLeds(LOW);
  delayLowPower(TIEMPO_ON);
  todosLeds(HIGH);
  delayLowPower(TIEMPO_OFF);
}
bool loopSimon() // true win false loss
{

  ledsInicio();
  for (int k = 1; k < (INTENTOS + 1); k++)
  {

    while (hayFruta && !lazoSerpiente())
      ;
    if (serpienteMuerta)
      return false;
    hayCombinacion = false;
    // muestra secuencia
    for (int n = 0; n < k; n++)
    {
      enciendeLedAndPita(secuencia[n]);
      delayLowPower(TIEMPO_ON);
    }
    // Comprueba secuencia
    if (serpienteMuerta)
      return false;
    for (int n = 0; n < k; n++)
    {
      if (!leePulsador(secuencia[n]))
      {
        return false;
      }
      else
        hayCombinacion = true;
    }
    if (serpienteMuerta)
      return false;
    secuenciaCorrecta();
  }
  while (hayFruta && !lazoSerpiente())
    ;
  if (serpienteMuerta)
    return false;
  return true;
}
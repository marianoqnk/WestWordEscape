#include <Arduino.h>
#include <LowPower.h>
#include "Config.h"
int secuencia[INTENTOS];


bool delayOn = false;



void delayLowPower(unsigned long tiempo)
{
  // aqui deberia de salir y hacer funcionar el simon
  // LowPower.powerDown(tiempo, ADC_OFF, BOD_OFF);
  // delayOn=true;
  // int tiempo=500;
  unsigned long tick = millis();
  while ((millis() - tick) < tiempo)
  {
    lazoSerpiente();
    delay(10);
  }
  // delay(500);
}
void enciendeLed(int n)
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
      if (!digitalRead(led[n]))
      {
        tickApagar=millis();
        enciendeLed(n);
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
/*void escribeCadena(char *cadena)
{
  int n = 0;
  int k[8];
  int c;
  boolean punto = false;
  while (cadena[n] != 0)
  {
    c = cadena[n];
    if (c == 32)c = 12; else c -= 48;
    if (cadena[n + 1] == '.') {
      punto = true;
      n++;
    } else punto = false ;

    n++;
  }
}
*/
void lucesFinal()
{
  // azul,rojo,verde

  for (byte n = 0; n < 5; n++)
  {
    enciendeLed(0); // azul
    delayLowPower(TIEMPO_OFF);
  }
  for (byte n = 0; n < 7; n++)
  {
    enciendeLed(1); // rojo
    delayLowPower(TIEMPO_OFF);
  }
  for (byte n = 0; n < 4; n++)
  {
    enciendeLed(2); // Verde
    delayLowPower(TIEMPO_OFF);
  }
  delayLowPower(1000);
}

void ledsInicio()
{

  for (int n = 0; n < INTENTOS; n++)
  {
    secuencia[n] = random(BOTONES); // para eso utiliza randon
    Serial.print(secuencia[n]);
  }
  Serial.println();

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

  // put your setup code here, to n once:
  // Serial.begin(115000);
  randomSeed(analogRead(A0)); // inicia el array con los numeros aleatorios
  for (int n = 0; n < BOTONES; n++)
  {
    pinMode(led[n], OUTPUT);
  }
  tickApagar=millis();
}

void loopSimon()
{
  // put your main code here, to run repeatedly:
  errorSecuencia = false;
  ledsInicio();
  for (int k = 0; k < INTENTOS; k++)
  {
    while (hayFruta)
      lazoSerpiente();
    for (int n = 0; n < k; n++)
    { // muestra secuencia
      enciendeLed(secuencia[n]);
      delayLowPower(TIEMPO_ON);
    }
    for (int n = 0; n < k; n++)
    {
      if (!leePulsador(secuencia[n]))
      {
        tone(PIN_ALTAVOZ,NOTA_MAL,500);
        finSerpiente();
        ledsError();
        errorSecuencia = true;
        break;
      }
      else
        hayCombinacion = true;
    }
    if (errorSecuencia)
    {

      
      break;
    }
    todosLeds(LOW);
    delayLowPower(TIEMPO_ON);
    todosLeds(HIGH);
    delayLowPower(TIEMPO_OFF);
  }
  if (!errorSecuencia) //sale sin error has ganado
  {
    // for (byte n = 0; n < 3; n++)

    //lucesFinal();
  while(!finSerpienteFlag)lazoSerpiente();
    // for (int n = 0; n < BOTONES; n++)      pinMode(led[n], INPUT);
  }

  /*
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), wakeUp, HIGH);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(digitalPinToInterrupt(2));
  detachInterrupt(digitalPinToInterrupt(3));
  for (int n = 0; n < BOTONES; n++) pinMode(led[n], OUTPUT);*/
}
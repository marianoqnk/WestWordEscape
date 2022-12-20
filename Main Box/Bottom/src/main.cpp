#include <Arduino.h>
#include <Wire.h>
#include <LowPower.h>
#include <Pines.h>
#include <PruebaFusibles.h>
#include <PruebaPuentes.h>
// #include "Neopixel.h"
#include "Organo.h"
#include "PruebaInterruptores.h"

enum Fases
{
  Inicial,
  Nfc,
  Fusibles,
  Puentes,
  Organo,
  Organo2,
  Interruptores,
  Teclado,
  Fin,
  Standby = 225
};
int x;
int value = 0;
Fases fase;
bool pruebaActualPasada = false;
void iniPruebaActual(Fases k)
{
  switch (k)
  {

  case Fusibles:
    iniPruebaFusibles();
    break;
  case Puentes:
    iniPruebaPuente();
    break;
  case Interruptores:
    setupInterruptores();
    break;
  case Organo:
    setupOrgano();
    break;
    /* case Standby:
       LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
       break;
     case Inicial:

     default:
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
       break;*/
  default:
    break;
  }
}
void receiveEvent()
{
  /*while ( Wire.available()) { // loop through all but the last
     char c = Wire.read();       // receive byte as a character
     Serial.print(c);         // print the character
   }*/
  // x = Wire.read();    // receive byte as an integer
  char c = Wire.read();
  switch (c)
  {
  case 'T':
    fase = (Fases)(Wire.read() - '0');
    // Serial.print("FASE:" + String(fase));
    pruebaActualPasada = false;
    iniPruebaActual(fase);
    break;
  }
  // Serial.println(); // print the integer
}

// function that executes whenever data is requested by master
void requestEvent()
{
  // Serial.println("RQ");
  Wire.write(pruebaActualPasada); // respond with message of 1 byte
  // Serial.println("RequestEvent:"+String(value));
  //  as expected by master
}

void setup()
{

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  // Serial.begin(115000);           // start serial for output
  iniPruebaFusibles();
  iniPruebaPuente();
  setupOrgano();
  // setupNeopixel();
  pinMode(9, OUTPUT);
  // Serial.println("iniciado");
  /*for(byte n=0;n< 9;n++)
  {
    tone(PIN_ALTAVOZ ,partitura1[n].nota/2,partitura1[n].tempo);
    delay(partitura1[n].tempo);

  }
  delay(1000);


    for(byte n=0;n< 9;n++)
  {
    tone(PIN_ALTAVOZ ,partitura2[n].nota/2,partitura2[n].tempo);
    delay(partitura2[n].tempo);

  }*/
  setupOrgano();
  setupInterruptores();
  fase = Inicial;
}

void loop()
{

  switch (fase)
  {

  case Fusibles:
    // Serial.println("FUS");
    if (PruebaFusibles())
    {
      pruebaActualPasada = true;
    }
    break;
  case Puentes:
    if (PruebaPuentes())
    {
      pruebaActualPasada = true;
    }
    break;
  case Interruptores:
    if (loopInterruptores())
    {
      pruebaActualPasada = true;
    }
    break;
  case Organo:
    if (loopOrgano())
    {
      pruebaActualPasada = true;
      fase = Inicial;
    }
    break;
    case Organo2:
    if (loopOrgano())
    {
      pruebaActualPasada = true;
      fase = Inicial;
    }
    break;
  case Standby:
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    break;
  case Inicial:

  default:
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    break;
  }
  // loopNeopixel();
  //  loopOrgano();
  delay(100);
}

#include <Arduino.h>
#include "Pines.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>
#include "mp3.h"
#include <LCDi2c.h>
#include "Displays.h"
#include "PruebaNfc.h"
#include "Teclado.h"
#include "Comunicacion.h"
#include "Dialogos.h"
#include <TimerOne.h>
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
  EsperaFin
};

int tiempoRestante = DURACION_JUEGO;
bool timeRun = false;
unsigned long tic = millis();
Fases Estado = Nfc;

int posicion = 0;
int posicionAnt = 0;
void enviaI2cEstado(Fases estado)
{
  String data('T' + String(Estado));
  Serial.println(data);
  Wire.beginTransmission(8);
  Wire.write(data.c_str());
  Wire.endTransmission();
}
void checkEntradaSerie()
{
  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case 'n':
      Estado = Nfc;
      break;
    case 'f':
      Estado = Fusibles;
      break;
    case 'p':
      Estado = Puentes;
      break;
    case 'o':
      Estado = Organo;
      break;
    case 'i':
      Estado = Interruptores;
      break;
    case 't':
      Estado = Teclado;
      break;
    case 'k':
      Estado = Fin;
      break;
    }
    enviaI2cEstado(Estado);
    lcd.display(BACKLIGHT_ON);
    lcd.display(DISPLAY_ON);
    Serial.println(Estado);
  }
}
void ISR_reloj()
{

  if (timeRun)
  {
    tiempoRestante--;
    // if (tiempoRestante == 0)
    //   juegoNoPasado();
    int minutos = tiempoRestante / 60;
    int segundos = tiempoRestante % 60;
    display.showNumberDecEx(minutos * 100 + segundos, (0b01000000), true);
    if (tiempoRestante == 0)
    {
      timeRun = false;
      Estado = Fin;
    }
  }
  // dfmp3.loop();
}
void setup(void)
{

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  iniDisplays();
  iniDFPlayer();
  iniPruebaNfc();
  setupTeclado();
  setupComunicacion();
  delay(100);
  hayDatosNfc = false;
  enviaI2cEstado(Estado);
  Timer1.initialize(1000000); // Dispara cada 250 ms
  Timer1.attachInterrupt(ISR_reloj);
}
void siguienteEstado()
{
  int n = Estado;
  Estado = (Fases)++n;
  enviaI2cEstado(Estado);
};
bool checkPruebaSuperada()
{
  if (Wire.requestFrom(8, 1))
    return (Wire.read());
  else
    return false;
}

void hasPerdido()
{
  funcionToMensajeActual = dialogoHasPerdido;
}
void hasGanado()
{
  timeRun = false;
  Serial.println(F("HAS GANADO"));
  dfmp3.playMp3FolderTrack(8);
  delay(5000);
  funcionToMensajeActual=dialogoFinal;
  while (1)
  {
    if ((millis() - tic) > 2000)
  {
    funcionToMensajeActual();
    tic = millis();
  }
  }
    ;
}
void claveAbrirCandado()
{
  for (byte n = 0; n < CLAVE_CANDADO1; n++)
  {
    dfmp3.playAdvertisement(4);
    delay(1100);
    dfmp3.loop();
  }
  delay(2000);
  for (byte n = 0; n < CLAVE_CANDADO2; n++)
  {
    dfmp3.playAdvertisement(4);
    delay(1100);
    dfmp3.loop();
  }
  delay(2000);
  for (byte n = 0; n < CLAVE_CANDADO3; n++)
  {
    dfmp3.playAdvertisement(4);
    delay(1100);
    dfmp3.loop();
  }
}
void loop(void)
{
  // loopTeclado();
  loopComunicacion();
  switch (Estado)
  {
  case Nfc:
    if (PruebaNfc())
    {
      dfmp3.loop();
      delay(500);
      musicaSonando = true;
      dfmp3.playAdvertisement(5);
      while (musicaSonando)
        dfmp3.loop();
      dfmp3.playAdvertisement(4);
      claveAbrirCandado();
      delay(4000);
      claveAbrirCandado();
      siguienteEstado();
      Serial.println(Estado);
    }
    break;
  case Fusibles:
    if (checkPruebaSuperada())
    {
      siguienteEstado();
      dfmp3.playAdvertisement(5);
      delay(5000);
      // dfmp3.setVolume(18);
      delay(500);
      // Serial.println("Volumen:" + String(dfmp3.getVolume()));
      delay(1000);
      simulaEncendidoDisplay();
      tiempoRestante = DURACION_JUEGO;
      timeRun = true;
      Serial.println(Estado);
      cadenaActual = 0;
      funcionToMensajeActual = dialogoPuentes;
    }
    break;
  case Puentes:
    if (checkPruebaSuperada())
    {
      dfmp3.playAdvertisement(5);
      siguienteEstado();
      cadenaActual = 0;
      funcionToMensajeActual = dialogoOrgano;
    }
    break;
  case Organo:
    if (checkPruebaSuperada())
    {
      dfmp3.playAdvertisement(5);
      siguienteEstado();
      lcd.cls();
      cadenaActual = 0;
      funcionToMensajeActual = dialogoOrgano2;
    }
    break;
  case Organo2:
    if (checkPruebaSuperada())
    {
      dfmp3.playAdvertisement(5);
      siguienteEstado();
      lcd.cls();
      cadenaActual = 0;
      funcionToMensajeActual = dialogoInterruptores;
    }
    break;
  case Interruptores:
    if (checkPruebaSuperada())
    {
      dfmp3.playAdvertisement(5);
      siguienteEstado();
      lcd.cls();
      cadenaActual = 0;
      funcionToMensajeActual = dialogoTeclado;
    }
    break;
  case Teclado:
    if (loopTeclado())
    {
      funcionToMensajeActual = martir;
      dfmp3.playAdvertisement(5);
      Serial.println(F("HAS GANADO"));
      delay(1000);
      hasGanado();
    }
    break;

  case Fin:
    if (timeRun)
      hasGanado();
    else
      hasPerdido();
    break;

  default:
    break;
  };

  dfmp3.loop();
  if ((millis() - tic) > 2000)
  {
    funcionToMensajeActual();
    tic = millis();
  }
  checkEntradaSerie();
}

#include <Adafruit_LEDBackpack.h>
#include <Wire.h> //libreria I2C
#include <Adafruit_GFX.h>
#include <LowPower.h>
#include "Config.h"

#define STEPVEL (VMAX - VMIN) / LONG_MAX
boolean hayCombinacion = false;
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
struct
{
  char fila;
  char columna;
} serpiente[LONG_MAX], movimiento, fruta;
enum
{
  Up = 1,
  Down = 2,
  Right = 4,
  Left = 8
} direccion;
boolean hayFruta = false;
//int intervaloFrutaActual;
char longActual = 1;
int velocidad = VMAX; // 250
char coordenadas[] = "N40 39.959  E03 38.179  GAME OVER";

static const uint8_t PROGMEM
    smile_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10100101,
         B10011001,
         B01000010,
         B00111100},
    neutral_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10111101,
         B10000001,
         B01000010,
         B00111100},
    frown_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10011001,
         B10100101,
         B01000010,
         B00111100};
/*#define DOWN 0x02
#define UP 0X01
#define RIGHT 0x04
#define LEFT 0x08*/
volatile byte wakeupSource;
void wakeUp(void)
{
  wakeupSource = 1;
}
byte leeJoystick()
{
  byte out = 0;
  static byte anterior = 0;
  int x = analogRead(JOYCTICK_PIN_X);
  int y = analogRead(JOYCTICK_PIN_Y);

  if (x > 600)
    out |= Up;
  else if (x < 400)
    out |= Down;

  if (y > 600)
    out |= Right;
  else if (y < 400)
    out |= Left;
  Serial.println(out, HEX);
  if (out == anterior)
    return 0;

  anterior = out;
  return out;
}
void iniJuego()
{
  finSerpienteFlag = false;
  serpiente[0].fila = serpiente[0].columna = 4;
  direccion = Up;
  movimiento.fila = 1;
  movimiento.columna = 0;
  longActual = 1;
  hayFruta = false;
  finSerpienteFlag = false;
  velocidad = VMAX;
}

void setupSnake() // Comienzo del juego
{
  // Serial.println("Ini Juego");
  matrix.begin(0x70); // direccion I2C display
  pinMode(DERECHA_PIN, INPUT_PULLUP);
  pinMode(IZQUIERDA_PIN, INPUT_PULLUP);
  pinMode(LEDD, OUTPUT);
  pinMode(LEDI, OUTPUT);
  digitalWrite(LEDD, HIGH);
  digitalWrite(LEDI, HIGH);
  randomSeed(analogRead(A1));
  matrix.setRotation(1);
  matrix.setTextSize(1);
  matrix.setTextWrap(false); // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  /*scrollMensaje("Bienvenido a ARDUINO GAMES I");
    scrollMensaje("SNAKE ");
    scrollMensaje("Tienes que comerte al menos 10 manzanas");
    scrollMensaje("GO");*/
  // escribe();
  iniJuego();
}

inline void dibujaSerpiente() // pinta la serpiente
{
  // Serial.println("Dibuja");
  matrix.clear(); // clear display
  for (byte n = 0; n < longActual; n++)
    matrix.drawPixel(serpiente[n].fila, serpiente[n].columna, LED_ON);
  if (hayFruta)
    matrix.drawPixel(fruta.fila, fruta.columna, LED_ON); // dibuja fruta
  matrix.writeDisplay();
}

inline boolean estaEnSerpiente(char fila, char columna, char inicio) // true si el punto esta dentro de la serpiente inicio=0 incluye cabeza 1 sin cabeza
{
  for (byte n = inicio; n < longActual; n++)
    if ((serpiente[n].fila == fila) && (serpiente[n].columna == columna))
      return true;
  return (false);
}

inline boolean fueraTablero() // true si el punto esta fuera del tablero
{
  return (serpiente[0].columna > 7) || (serpiente[0].columna < 0) || (serpiente[0].fila > 7) || (serpiente[0].fila < 0);
}

void scrollMensaje(char mensaje[])
{
  int longitud = 0;
  while (mensaje[longitud])
    longitud++;
  int lineas = longitud * 6;
  for (int x = 0; x >= -lineas; x--)
  {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print(mensaje);
    matrix.writeDisplay();
    delay(100);
  }
}
void goToLowPower()
{
  for (int n = 0; n < BOTONES; n++)
    pinMode(led[n], INPUT);
  pinMode(PIN_ALTAVOZ, INPUT);
  // pinMode(LED_BUILTIN, INPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(13, LOW);
  Wire.beginTransmission(0x70);
  Wire.write(0x20); // turn off oscillator, puts HT16K33 into standby mode
  Wire.endTransmission();
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), wakeUp, HIGH);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(digitalPinToInterrupt(2));
  detachInterrupt(digitalPinToInterrupt(3));
  for (int n = 0; n < BOTONES; n++)
    pinMode(led[n], OUTPUT);
  pinMode(PIN_ALTAVOZ, OUTPUT);
  matrix.begin(0x70);
  tickApagar=millis();
  iniJuego();
}
inline void hasGanado() // Funcion cuando has ganado la  partida sonrie y saca coordenadas
{
  finSerpienteFlag = true;
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);
  for (byte n = 0; n < 2; n++)
    scrollMensaje(coordenadas);
  goToLowPower();
}
void escribe()
{
  char nombre[] = "AAAAAA";
  byte n = 0;
  char letra = 65;
  while (1)
  {
    matrix.clear();
    matrix.setCursor(0, 0);
    matrix.write(letra);
    matrix.writeDisplay();
    while ((digitalRead(DERECHA_PIN)) && (digitalRead(IZQUIERDA_PIN)))
      ;
    if (digitalRead(IZQUIERDA_PIN))
    { // Siguiente letra
      if (letra == 91)
        n--; // vuelta a empezar
      nombre[n] = letra;
      n++;
      if (n == 6)
        break;
    }
    else
    {
      letra++;
      if (letra == 92)
        letra = 65;
    }
    delay(500);
  }
  nombre[6] = 0;
  while (1)
    scrollMensaje(nombre);
  while ((digitalRead(DERECHA_PIN)) && (digitalRead(IZQUIERDA_PIN)))
    ;
  if (digitalRead(IZQUIERDA_PIN))
    n = 6;
  else
    n = 9;
  // 65 a 93
}

inline void frutas() // Se encarga de ir sacando las frutas
{

  if (hayFruta)
  {
    if ((serpiente[0].fila == fruta.fila) && (serpiente[0].columna == fruta.columna))
    {
      longActual++; // si se la ha comido crece la serpiente
      velocidad -= STEPVEL;
      if (longActual == LONG_MAX)
        hasGanado(); // Si es lo suficientemente grande se acabo el juego
      hayFruta = false;
    }
  }
  else
  {
    if (hayCombinacion)
    {
      do
      {
        fruta.fila = random(8);
        fruta.columna = random(8);
      } while (estaEnSerpiente(fruta.fila, fruta.columna, 0));
      hayFruta = true;
      hayCombinacion = false;
    }
  }
}
void finSerpiente()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);
  errorSecuencia = true;
  iniJuego();
}
inline void mueve() // Mueve la serpiente
{
  // Serial.println("mueve" + String ((int)longActual));
  // Serial.println ("fila:" + String((int)serpiente[0].fila) + " Col:" + String((int)serpiente[0].columna));
  for (byte n = longActual; n >= 1; n--)
    serpiente[n] = serpiente[n - 1];
  serpiente[0].columna += (direccion == Up || direccion == Down) ? ((direccion == Down) ? 1 : -1) : 0;
  serpiente[0].fila += (direccion == Right || direccion == Left) ? ((direccion == Right) ? 1 : -1) : 0;
  if (fueraTablero() || estaEnSerpiente(serpiente[0].fila, serpiente[0].columna, 1)) // si se sale o choca se acaba
  {
    finSerpiente();
  }
}
void lazoSerpiente()
{
  // LEER 250MSG

  static unsigned long tiempo = millis();
  // Serial.println(tiempo);
  // boolean teclaDer,teclaIzda;
  byte joystickValue = leeJoystick();
  if (((millis() - tiempo) > (unsigned long)velocidad) || joystickValue)
  {
    if ((millis() - tickApagar) > TIEMPO_APAGADO_SIN_PULSAR_TECLA)
      goToLowPower();
    if (joystickValue)
    {
      if (direccion == Right || direccion == Left)
      {
        if (joystickValue & Up)
          direccion = Up;
        else if (joystickValue & Down)
          direccion = Down;
      }
      else
      {
        if (joystickValue & Right)
          direccion = Right;
        else if (joystickValue & Left)
          direccion = Left;
      }
    }
    // Serial.println("DIR:"+String(direccion));

    mueve();
    dibujaSerpiente();
    frutas();
    // int resto = velocidad - (millis() - tiempo);
    delay(2);          // delay((resto>20)?resto:20);//conviene esperar al resto o vale con soltar
    tiempo = millis(); // espera a soltar
    delay(1);
  }
}

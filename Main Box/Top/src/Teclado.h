#include <Keypad.h>
#include "Pines.h"

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {COL1_PIN, COL2_PIN, COL3_PIN};           // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setupTeclado()
{
}

bool loopTeclado()
{
  char key = keypad.getKey();
  static char claveIntro[sizeof(claveTeclado)];
  static byte posActual = 0;

  if (key)
  {
    dfmp3.playAdvertisement(2);
    if (key == '#')
    {
      Serial.println(claveIntro);
      Serial.println(claveTeclado);
      posActual = 0;
      if (!strncmp(claveTeclado,claveIntro,sizeof(claveTeclado)-1))
      {
        Serial.print(F("TECLADO PASS"));
        lcd.cls();
        lcd.print(F("TECLADO PASS"));
        return true;
      }
      lcd.print(F("ERROR DE CLAVE"));
      dfmp3.playAdvertisement(8);
      delay(1000);
      
    }
    else
    {
      if (posActual < sizeof(claveTeclado))
      {
        claveIntro[posActual++] = key;
      }
    }

    Serial.println(key);
  }
  return false;
}

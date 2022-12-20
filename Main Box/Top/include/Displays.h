#include <Arduino.h>
#include "Pines.h"
#include <TM1637Display.h>

// Module connection pins (Digital Pins)

// The amount of time (in milliseconds) between tests
#define TEST_DELAY 2000

#define LCD_CHARS 16
#define LCD_LINES 2
const uint8_t SEG_DONE[] = {
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,         // d
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
    SEG_C | SEG_E | SEG_G,                         // n
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G          // E
};

TM1637Display display(PIN_RELOJ_CLK, PIN_RELOJ_DIO);
LCDi2c lcd(0x3F); // I2C address
void iniClock()
{
  // display.setBrightness(0x0f,false);
  display.setBrightness(0x0f, false);
  Serial.println("IniClock");
}

void testDisplay()
{

  // special chars
  uint8_t upArrow[8] = {
      0b00100,
      0b01010,
      0b10001,
      0b00100,
      0b00100,
      0b00100,
      0b00000,
  };

  uint8_t downArrow[8] = {
      0b00000,
      0b00100,
      0b00100,
      0b00100,
      0b10001,
      0b01010,
      0b00100,
  };

  uint8_t rightArrow[8] = {
      0b00000,
      0b00100,
      0b00010,
      0b11001,
      0b00010,
      0b00100,
      0b00000,
  };

  uint8_t leftArrow[8] = {
      0b00000,
      0b00100,
      0b01000,
      0b10011,
      0b01000,
      0b00100,
      0b00000,
  };

  float data = 0.1f;

  // LCDi2c lcd(0x27); // I2C address

  // lcd.begin(LCD_CHARS, LCD_LINES);
  lcd.create(0, downArrow);
  lcd.create(1, upArrow);
  lcd.create(2, rightArrow);
  lcd.create(3, leftArrow);

  lcd.cls();
  lcd.locate(0, 0);
  lcd.printf("hello world %f", data);
  // print user chars
  lcd.character(0, 1, 0);
  lcd.character(2, 1, 1);
  lcd.character(4, 1, 2);
  lcd.character(6, 1, 3);

  delay(2000);
  lcd.display(DISPLAY_OFF);
  delay(2000);
  lcd.display(DISPLAY_ON);
  delay(2000);
  lcd.display(BACKLIGHT_OFF);
  delay(2000);
  lcd.display(BACKLIGHT_ON);
  delay(2000);
  lcd.display(CURSOR_ON);
  delay(2000);
  lcd.display(BLINK_ON);
  delay(2000);
  lcd.display(BLINK_OFF);
  delay(2000);
  lcd.display(CURSOR_OFF);
  delay(2000);

  for (uint8_t pos = 0; pos < 13; pos++)
  {
    // scroll one position to left
    lcd.display(SCROLL_LEFT);
    // step time
    delay(500);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right
  for (uint8_t pos = 0; pos < 29; pos++)
  {
    // scroll one position to right
    lcd.display(SCROLL_RIGHT);
    // step time
    delay(500);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center
  for (uint8_t pos = 0; pos < 16; pos++)
  {
    // scroll one position to left
    lcd.display(SCROLL_LEFT);
    // step time
    delay(500);
  }

  delay(1000);
}

void simulaEncendidoDisplay()
{

  char p[] = "$%&/())=3$%&/()(/&%=!·?¿=))/&!!$%&/";
  lcd.display(BACKLIGHT_ON);
  lcd.display(DISPLAY_ON);
  display.showNumberDec(8888);
  lcd.display(AUTOSCROLL_OFF);
  lcd.print(p);
  dfmp3.playAdvertisement(7);
  for (byte n = 0; n < 10; n++)
  {
    lcd.display(BACKLIGHT_ON);
    display.setBrightness(0x0f, true);
    display.showNumberDec(8888);
    delay(random(1000));
    lcd.display(BACKLIGHT_OFF);
    display.setBrightness(0x0f, false);
    display.showNumberDec(8888);
    delay(random(1000));
  }
  lcd.display(BACKLIGHT_ON);
  for (byte n = 0; n < 8; n++)
  {
    display.setBrightness(n);
    display.showNumberDec(8888);

    lcd.print(p);
    delay(1000);
  }

  display.setBrightness(0x0f, true);
  // lcd.display(SCROLL_LEFT);
  lcd.display(AUTOSCROLL_OFF);
  lcd.cls();
  lcd.print(F("BIENVENIDOS "));
  lcd.locate(0, 1);
  lcd.print(F("A WESTWOLD"));
  delay(1500);
  lcd.cls();
  lcd.print(F("INICIANDO SISTEMA"));
 /* for (byte n = 0; n < 19; n++)
  {
    lcd.display(SCROLL_LEFT);
    delay(500);
  }*/
  // byte delay(1500);
  //  lcd.display(AUTOSCROLL_ON);
  //lcd.display(AUTOSCROLL_OFF);
   delay(1500);
  lcd.cls();
 
  // lcd.home();
  lcd.print("CHECKING ");
  lcd.locate(0, 1);
  lcd.print("BATTERIES...");
  delay(1500);
  //dfmp3.playAdvertisement(6);
  // lcd.print("BIENVENIDOS A WESTWOLD");
  for (int n = 0; n < DURACION_JUEGO * 5 / 3; n += 5)
  {
    display.showNumberDec(n);
    delay(5);
    if(!(n%200))dfmp3.playAdvertisement(6);
  }
  lcd.cls();
  lcd.print(F("TIENES ENERGIA "));
  lcd.locate(0, 1);
  lcd.print(F("PARA 20 MINUTOS"));
  delay(1500);
}

void iniDisplays()
{
  iniClock();
  lcd.begin(LCD_CHARS, LCD_LINES);
  lcd.display(BACKLIGHT_OFF);
  lcd.display(DISPLAY_OFF);
  lcd.cls();
  lcd.locate(0, 0);
  lcd.print("ESCAPEBOX");
  Serial.println("IniDisplays");
}
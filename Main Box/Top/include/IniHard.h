#pragma once
#include <Arduino.h>
#include "Pines.h"
#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_PN532.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "SoftwareSerial.h"
#include <DFMiniMp3.h>
#include <Keypad.h>
//#include <Encoder.h>
//#include <Servo.h>
#include <LCDi2c.h>
int pos = 0; // variable to store the servo position
// Encoder myEnc(2, 3);
long oldPosition = -999;




#define LCD_CHARS 16
#define LCD_LINES 2

#define LCD_RS 2
#define LCD_ENABLE 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define DURACION_JUEGO 3600
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
// special chars

float data = 0.1f;




void scanI2C();
void iniAlfaNum();
int tiempoRestante = DURACION_JUEGO;
unsigned long tic = millis();



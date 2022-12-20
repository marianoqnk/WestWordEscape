#pragma once
#define TECLADO
#define PIN_FUSIBLES 5
//MP3
#define PIN_MP3_RX 8
#define PIN_MP3_TX 9
//NFC
#define PIN_PN532_IRQ (2)
#define PIN_PN532_RESET (3) // Not connected by default on the NFC Shield
#define PIN_SERVO_PUERTA (10)
#define TIEMPO_ENTRE_TARJETAS 500
#define CLAVE_CANDADO1 5
#define CLAVE_CANDADO2 3
#define CLAVE_CANDADO3 6

//Reloj
#define PIN_RELOJ_CLK 4
#define PIN_RELOJ_DIO 5
//Teclado
#define ROW1_PIN A1 
#define ROW2_PIN A3
#define ROW3_PIN A2
#define ROW4_PIN A0 
#define COL1_PIN 10
#define COL2_PIN 11
#define COL3_PIN 12
//CABLES
 //byte pinesCablesFilaSup[5]={A0,A1,A2,A3,A4};
 //byte pinesCablesFilaInf[5]={10,11,12,13,5};
 #define DURACION_JUEGO 1200

 char claveTeclado[]={"9654"};
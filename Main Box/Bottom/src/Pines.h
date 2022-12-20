#pragma once
#define PIN_FUSIBLES A3
#define PIN_ALTAVOZ 3
#define PIN_NEOPIXEL 2

// CABLES
byte pinesCablesFilaSup[5] = {6, 5, 4, 0, 1};
byte pinesCablesFilaInf[5] = {13, 12, 11, 10, 9};
// ORGANO
byte pinesOrgano[7] = {13, 12, 11, 10, 9, 8, 7};
#define PIN_ORGANO_COMUN A0
#define DELAY_PULSAR_NOTAS 1500
#define REINTENTOS_ORGANO_SOLO 5
// INTERRUPTORES
#define PIN_INTERRUPTOR1 A1
#define PIN_INTERRUPTOR2 A2

// NOTAS
// #define BOTONES 4
#define NOTA_DO 1046
#define NOTA_RE 1174
#define NOTA_MI 1318
#define NOTA_FA 1396
#define NOTA_SOL (1567/2)
#define NOTA_LA (1760/2)
#define NOTA_SI 1975
#define TEMPO 600
#define SEMICORCHEA TEMPO / 4
#define CORCHEA TEMPO / 2
#define NEGRA TEMPO * 1
#define REDONDA TEMPO * 4
struct notaCompleta
{
  int nota;
  int tempo;
};
int escala[7] = {NOTA_DO, NOTA_RE, NOTA_MI, NOTA_FA, NOTA_SOL, NOTA_LA, NOTA_SI};
notaCompleta partitura1[] = {
    {NOTA_MI, NEGRA}, {NOTA_FA, CORCHEA}, {NOTA_MI, NEGRA}, {NOTA_FA, CORCHEA}, //
    {NOTA_MI, SEMICORCHEA},
    {NOTA_RE, SEMICORCHEA},
    {NOTA_DO, SEMICORCHEA},
    {NOTA_DO, NEGRA},
    {NOTA_RE, REDONDA},
    {NOTA_RE, NEGRA},
    {NOTA_MI, CORCHEA},
    {NOTA_RE, NEGRA},
    {NOTA_MI, CORCHEA},
    {NOTA_RE, SEMICORCHEA},
    {NOTA_DO, SEMICORCHEA},
    {NOTA_SOL , SEMICORCHEA},
    {NOTA_SOL , NEGRA},
    {NOTA_LA , REDONDA}};
    byte partituraTeclas[]={2,3,2,3,2,1,0,0,1,1,2,1,2,1,0,4,4,5};

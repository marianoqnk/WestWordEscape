#pragma once
bool errorSecuencia = false;
bool finSerpienteFlag=false;
unsigned long tickApagar;
#define INTENTOS 11 //combinaciones
#define LONG_MAX INTENTOS+1      // maxima longitud de la serpiente
#define DERECHA_PIN A2  // pin de la tecla derecha
#define IZQUIERDA_PIN 2 // pin de la tecla izquierda
#define JOYCTICK_PIN_X A0
#define JOYCTICK_PIN_Y A1
#define JOYCTICK_PIN_PULSADOR A3

#define LEDD 4
#define LEDI 3
#define VMAX 650.0 // Velocidad máxima de la serpiente
#define VMIN 180.0 // velocidad mínima

#define PIN_ALTAVOZ 6
#define TIME_INTERMITENTE SLEEP_500MS
#define VECES_INTERMITENTE 3
#define TIEMPO_ON 250  // SLEEP_250MS
#define TIEMPO_OFF 500 // SLEEP_500MS
#define TIEMPO_PULSAR 1000
#define TIEMPO_APAGADO_SIN_PULSAR_TECLA 30000
#define LAT "40 39.959"
#define LONG "03 38.179"


#define BOTONES 4
#define NOTA_DO 1046
#define NOTA_RE 1174   
#define NOTA_MI 1318
#define NOTA_FA 1396
#define NOTA_SOL 1567
#define NOTA_LA 1760
#define NOTA_SI 1975
int escala[7]={NOTA_DO,NOTA_RE,NOTA_MI,NOTA_FA,NOTA_SOL,NOTA_LA,NOTA_SI};
int partitura1[]={NOTA_LA,NOTA_SI,NOTA_LA,NOTA_SI,NOTA_LA,NOTA_SOL,NOTA_FA,NOTA_FA,NOTA_SOL};
int partitura2[]={NOTA_SOL,NOTA_LA,NOTA_SOL,NOTA_LA,NOTA_SOL,NOTA_MI,NOTA_RE,NOTA_RE,NOTA_MI};
#define NOTA_MAL 500

enum colores
{
  azul = 1,
  rojo = 2,
  verde = 3,
  naranja = 4
};
const int led[BOTONES] = {2, 3, 11, 10};
const int notas[BOTONES] = {NOTA_DO, NOTA_RE, NOTA_MI, NOTA_FA};
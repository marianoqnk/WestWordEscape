#include <Arduino.h>
#include "Pines.h"
// #include "Neopixel.h"
#include <NeoPixelBus.h>

const uint16_t PixelCount = 35;        // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = PIN_NEOPIXEL; // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor azul(0, 0, colorSaturation);
RgbColor rojo(colorSaturation, 0, 0);
RgbColor naranja(colorSaturation, colorSaturation / 2, 0);
RgbColor amarillo(colorSaturation, colorSaturation, 0);
RgbColor verde(0, colorSaturation, 0);
RgbColor blanco(colorSaturation, colorSaturation, colorSaturation);
RgbColor negro(0, 0, 0);
RgbColor black(0);
RgbColor notasColores[] = {blanco, azul, rojo, naranja, amarillo, verde, negro};
void setupOrgano()
{
    for (byte n = 0; n < 7; n++)
        pinMode(pinesOrgano[n], INPUT_PULLUP);
    pinMode(PIN_ORGANO_COMUN, OUTPUT);
    strip.Begin();
    strip.Show();
}
void tocaMelodiaEntera()
{
    for (byte k = 0; k < PixelCount; k++)
        strip.SetPixelColor(k, black);
    for (byte n = 0; n < 18; n++)
    {
        strip.SetPixelColor(n, notasColores[partituraTeclas[n]]);
        strip.Show();
        tone(PIN_ALTAVOZ, partitura1[n].nota / 2, partitura1[n].tempo);
        delay(partitura1[n].tempo);
    }
}
byte leeTeclas()
{
    byte tecla = 8;
    digitalWrite(PIN_ORGANO_COMUN, LOW);
    delay(1);
    for (byte n = 0; n < 7; n++)
    {
        if (!digitalRead(pinesOrgano[n]))
        {
            tecla = n;
            break;
        }
        /*{
            tone(PIN_ALTAVOZ, escala[n], 100);
            break;
        }*/
    }
    digitalWrite(PIN_ORGANO_COMUN, HIGH);
    return tecla;
}

bool loopOrgano()
{
    static byte estado = 255;
    static byte notaActual = 0;
    static byte reIntentos=0;

    static unsigned long tick = millis();
    byte n;

    switch (estado)
    {

    case 255:
        for (byte k = 0; k < PixelCount; k++)
            strip.SetPixelColor(k, black);
        strip.Show();
        estado = 0;
        break;
    case 0: // eNCIENDE LED
        strip.SetPixelColor(notaActual, notasColores[partituraTeclas[notaActual]]);
        strip.Show();
        estado = 1;
        tick = millis();
        break;
    case 1: // ESPERA QUE SE PULSE TECLA
        n = leeTeclas();
        if (n != 8)
        {
            // tone(PIN_ALTAVOZ, escala[n], 100);
            /*tone(PIN_ALTAVOZ, partitura1[notaActual].nota / 2, partitura1[notaActual].tempo);
            delay(partitura1[notaActual].tempo);*/

            if (leeTeclas() == partituraTeclas[notaActual])
            {
                tone(PIN_ALTAVOZ, escala[n]);
                delay(50);
                while (leeTeclas() != 8)
                    ;
                noTone(PIN_ALTAVOZ);
                estado = 0;
                tick = millis();
                notaActual++;
            }
            else
            {
                estado = 255;
                notaActual = 0;
                tick = millis();
                tone(PIN_ALTAVOZ, 500, 1000);
                delay(1000);
            }
            if (notaActual == 18)
            {
                tocaMelodiaEntera();
                for (byte k = 0; k < PixelCount; k++)
                    strip.SetPixelColor(k, black);
                strip.Show();
                noTone(PIN_ALTAVOZ);
                estado = 2;
                notaActual = 0;
                return true;
            }
            break;
        }
        if (millis() - tick > DELAY_PULSAR_NOTAS)
        {
            estado = 255;
            notaActual = 0;
            tick = millis();
            tone(PIN_ALTAVOZ, 500, 1000);
            delay(1000);
        }
        break;
    case 2:
        n = leeTeclas();
        if (n != 8)
        {

            if (leeTeclas() == partituraTeclas[notaActual])
            {
                tone(PIN_ALTAVOZ, escala[n]);
                delay(50);
                while (leeTeclas() != 8)
                    ;
                noTone(PIN_ALTAVOZ);
                estado = 2;
                tick = millis();
                notaActual++;
            }
            else
            {
                estado = 2;
                notaActual = 0;
                tick = millis();
                tone(PIN_ALTAVOZ, 500, 1000);
                delay(1000);
            }
            if (notaActual == 18)
            {
                tocaMelodiaEntera();
                for (byte k = 0; k < PixelCount; k++)
                    strip.SetPixelColor(k, black);
                strip.Show();
                noTone(PIN_ALTAVOZ);
                estado = 255;
                notaActual = 0;
                return true;
            }
            break;
        }
        if (millis() - tick > DELAY_PULSAR_NOTAS)
        {
            if(reIntentos++>REINTENTOS_ORGANO_SOLO){
                estado = 255;
                reIntentos=0;
            }else estado = 2;
            notaActual = 0;           
            tone(PIN_ALTAVOZ, 500, 1000);
            delay(1000);
            tick = millis();
        }

        break;
    }

    /*for (byte n = 0; n < 7; n++)
    {
        if (!digitalRead(pinesOrgano[n]))
        {
            tone(PIN_ALTAVOZ, escala[n], 100);
            break;
        }
    }
    digitalWrite(PIN_ORGANO_COMUN, HIGH);*/
    return false;
}
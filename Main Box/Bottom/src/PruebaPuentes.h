#include <Arduino.h>
#include <Pines.h>
#define NO_CONECTADO 8
const byte solucion[5] = {NO_CONECTADO, 2, 0, 1, NO_CONECTADO};
void iniPruebaPuente()
{
    for (byte n = 0; n < 5; n++)
    {
        pinMode(pinesCablesFilaSup[n], OUTPUT);
        pinMode(pinesCablesFilaInf[n], INPUT_PULLUP);
    }
}

boolean PruebaPuentes()
{
    byte solucionLeida[5];
    for (byte sup = 0; sup < 5; sup++)
    {
        digitalWrite(pinesCablesFilaSup[sup], LOW);
        solucionLeida[sup] = NO_CONECTADO;
        for (byte inf = 0; inf < 5; inf++)
        {
            if (!digitalRead(pinesCablesFilaInf[inf]))
            {
                solucionLeida[sup] = inf;
                //tone(PIN_ALTAVOZ, escala[inf], 100);
                break;
            }
        }
        // Serial.print(solucionLeida[sup]);
        // Serial.print(",");
        digitalWrite(pinesCablesFilaSup[sup], HIGH);
    }
    // Serial.println();
    if (!memcmp(solucion, solucionLeida, 5))
    {
        for (byte n = 0; n < 5; n++)
        {
            pinMode(pinesCablesFilaSup[n], INPUT_PULLUP);
            pinMode(pinesCablesFilaInf[n], INPUT_PULLUP);
        }
        return true;
    }
    // delay(100);
    return false;
}
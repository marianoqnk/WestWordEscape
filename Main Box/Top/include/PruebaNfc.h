// #include "IniHard.h"
#include "Pines.h"
#include <Adafruit_PN532.h>
#include <Servo.h>
const int posTapaOpen = 30;
const int posTapaClose = 170;
#define ULTRALIGHT_PAGE_SIZE 4
#define ULTRALIGHT_READ_SIZE 4 // we should be able to read 16 bytes at a time

#define ULTRALIGHT_DATA_START_PAGE 4
#define ULTRALIGHT_MESSAGE_LENGTH_INDEX 1
#define ULTRALIGHT_DATA_START_INDEX 2
#define ULTRALIGHT_MAX_PAGE 63

Servo myservo; // create servo object to control a servo
Adafruit_PN532 nfc(PIN_PN532_IRQ, PIN_PN532_RESET);

uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};
uint8_t uidLength;
byte SecuenciaNfc[][7] = {
    {0x04, 0xEA, 0x81, 0x92, 0x6D, 0x40, 0x80},
    {0x04, 0x42, 0x74, 0x52, 0x78, 0x3F, 0x80},
    {0x14, 0xBC, 0x61, 0x8B, 0x00, 0x00, 0x00}};
char Personajes[][5] = {
    {"en01"}, {"en02"}, {"en03"}, {"en04"}};
char datoActual = '1';
char ultimoDato;
boolean hayDatosNfc = false;
// Funcion auxiliar para mostrar el buffer
void printArray(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
void abrirTapa()
{
    myservo.write(posTapaOpen);
    delay(1000);
}
void cerrarTapa()
{
    myservo.write(posTapaClose);
    delay(1000);
}

void irsNfc()
{
    hayDatosNfc = true;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void iniPruebaNfc()
{
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
        Serial.print(F("PN53x no encontrado"));
        while (1)
            ; // halt
    }
    // Mostrar datos del sensor
    /*Serial.print("Found chip PN5");
    Serial.println((versiondata >> 24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata >> 16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata >> 8) & 0xFF, DEC);*/
    Serial.println("Ini NFC");
    // Configurar para leer etiquetas RFID
    // nfc.setPassiveActivationRetries(0xFF);
    nfc.SAMConfig();
    Serial.println(F("Esperando tarjeta ISO14443A"));
    attachInterrupt(digitalPinToInterrupt(PIN_PN532_IRQ), irsNfc, FALLING);
    nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A);
    //myservo.attach(PIN_SERVO_PUERTA);
    //myservo.write(posTapaClose);
}
boolean PruebaNfc()
{
    static unsigned long tick = millis();
    static bool esperaOtraTarjeta;
    if (esperaOtraTarjeta == true)
    {
        if (millis() - tick > TIEMPO_ENTRE_TARJETAS)
            if (!nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A))
            {
                Serial.println(F("ERROR2"));
            };
        esperaOtraTarjeta=false;
        hayDatosNfc = false;
        return false;
    }

    if (hayDatosNfc)
    {
        dfmp3.playAdvertisement(2);
        if (!nfc.readDetectedPassiveTargetID(&uid[0], &uidLength))
        {
            Serial.println(F("ERROR1"));
            hayDatosNfc = false;
            return false;
        };

        byte datos[5];
        nfc.mifareultralight_ReadPage(7, datos);
        delay(500);
        //Adafruit_PN532::PrintHexChar(datos, 4);
        if (datos[3] == datoActual)
        {
            ultimoDato = datoActual;

            Serial.print("NFC Fase:");
            Serial.println(datoActual);
            //delay(100);
            if (datoActual++ == '4')
            {
                //abrirTapa();
                Serial.println("Pasada prueba NFC");
                // desactivar lectura NFC
                return true;
            }
        }
        else if (datos[3] != ultimoDato)
        {
            Serial.println("TARJETA ERROR");
            datoActual = '1';
        }
        esperaOtraTarjeta=true;
    }
    return false;
}

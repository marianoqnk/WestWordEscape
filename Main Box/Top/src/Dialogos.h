byte cadenaActual = 0;
void martir() { return; }
void (*funcionToMensajeActual)() = martir;
void dialogoPuentes()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("ALGO FALLO HAY"));
        lcd.locate(0, 1);
        lcd.print(F("QUE RECOSNTRUIR"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {
        lcd.cls();
        lcd.print(F("EL ADN ROTO"));
        lcd.locate(0, 1);
        lcd.print(F(""));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("UNE CADA ORGANO"));
        lcd.locate(0, 1);
        lcd.print(F("CON SU PROTEINA"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 3)
    {

        lcd.cls();
        lcd.print(F("APOE TNF TP5"));
        lcd.locate(0, 1);
        lcd.print(F("ESR1 IL6"));
        cadenaActual = 0;
        return;
    }
}

void dialogoOrgano()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("FENOMENAL YA"));
        lcd.locate(0, 1);
        lcd.print(F("TIENES EL ADN"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("QUE NECESITAS"));
        lcd.locate(0, 1);
        lcd.print(F("DEBERAS"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("APRENDER"));
        lcd.locate(0, 1);
        lcd.print(F("A SECUENCIAR"));

        cadenaActual = 0;
        return;
    }
}
void dialogoOrgano2()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("FENOMENAL YA"));
        lcd.locate(0, 1);
        lcd.print(F("HAS APRENDIDO"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("LA SECUENCIA "));
        lcd.locate(0, 1);
        lcd.print(F("INTRODUCELA "));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("TU SOLO"));
        lcd.locate(0, 1);
        lcd.print(F("SIN AYUDA"));
        cadenaActual = 0;
        return;
    }
}

void dialogoInterruptores()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("CORRECTO"));
        lcd.locate(0, 1);
        lcd.print(F("AHORA TIENES QUE"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("ENCENDER LA"));
        lcd.locate(0, 1);
        lcd.print(F("SALA DE CONTROL"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("LEE CUIDADOSAMENTE"));
        lcd.locate(0, 1);
        lcd.print(F("LAS INSTRUCCIONES"));
        cadenaActual = 0;
        return;
    }
}
void dialogoTeclado()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("BIEN"));
        lcd.locate(0, 1);
        lcd.print(F("INTRODUCE"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("EN EL TECLADO"));
        lcd.locate(0, 1);
        lcd.print(F("LA PASSWORD"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("Y PARA ESTA "));
        lcd.locate(0, 1);
        lcd.print(F("LOCURA"));
        cadenaActual++;
        return;
    }

    else if (cadenaActual == 3)
    {
        lcd.cls();
        lcd.print(F("LA PASSWORD ES"));
        lcd.locate(0, 1);
        lcd.print(F("HEXAGONO AZUL"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 4)
    {

        lcd.cls();
        lcd.print(F("CUADRADO VERDE"));
        lcd.locate(0, 1);
        lcd.print(F("TRIANGUL NARANJA"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 5)
    {

        lcd.cls();
        lcd.print(F("CIRCULO AZUL"));
        lcd.locate(0, 1);
        lcd.print(F("#"));
        cadenaActual = 0;
        return;
    }
}

void dialogoHasPerdido()
{
    if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("HAS TRABAJADO"));
        lcd.locate(0, 1);
        lcd.print(F("MUCHO Y BIEN"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("PERO EL TIEMPO"));
        lcd.locate(0, 1);
        lcd.print(F("CORRIA EN TU"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("CONTRA MAS"));
        lcd.locate(0, 1);
        lcd.print(F("SUERTE EN LA "));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 3)
    {
        lcd.cls();
        lcd.print(F("PROXIMA"));
        lcd.locate(0, 1);
        lcd.print(F("SAYONARA"));
        cadenaActual=0;
        return;
    }
    
}
void dialogoFinal()
{
     if (cadenaActual == 0)
    {
        lcd.cls();
        lcd.print(F("HAS CONSEGUIDO"));
        lcd.locate(0, 1);
        lcd.print(F("REPARAR A LOS"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 1)
    {

        lcd.cls();
        lcd.print(F("ANFITRIONES "));
        lcd.locate(0, 1);
        lcd.print(F("AHORA TODO"));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 2)
    {

        lcd.cls();
        lcd.print(F("VOLVERA A LA NORMALIDAD"));
        lcd.locate(0, 1);
        lcd.print(F("SUERTE EN LA "));
        cadenaActual++;
        return;
    }
    else if (cadenaActual == 3)
    {
        lcd.cls();
        lcd.print(F("PROXIMA"));
        lcd.locate(0, 1);
        lcd.print(F("SAYONARA"));
        cadenaActual=0;
        return;
    }
 

}
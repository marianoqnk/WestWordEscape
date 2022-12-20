 #include <Arduino.h>
 #include <pines.h>

  void iniPruebaFusibles()
  {
    pinMode(PIN_FUSIBLES,INPUT_PULLUP);

  }
  boolean PruebaFusibles(){
    if(!digitalRead(PIN_FUSIBLES))
    {
        //lcd.display(DISPLAY_ON);
        //Serial.println("Pasada prueba fusible");
        delay(100);
        return true;
        //Mensaje voz y display
    }else delay(100);
    return false;

}

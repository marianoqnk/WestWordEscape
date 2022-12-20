void setupInterruptores()
{
pinMode(PIN_INTERRUPTOR1,INPUT_PULLUP);
pinMode(PIN_INTERRUPTOR2,INPUT_PULLUP);

}

boolean loopInterruptores()
{
if(!digitalRead(PIN_INTERRUPTOR1) && !digitalRead(PIN_INTERRUPTOR2))
{
    //tone(PIN_ALTAVOZ,1000,400);
    return true;
}
//tone(PIN_ALTAVOZ,200,100);
return false;
}
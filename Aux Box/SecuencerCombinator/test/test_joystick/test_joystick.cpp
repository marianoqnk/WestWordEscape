#include <Snake.h>
#include <Simon.h>
#include <unity.h>
#include <Arduino.h>
void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void func2(void)
{
   TEST_ASSERT_TRUE(leePulsador(0));
}
void func3(void)
{
   TEST_ASSERT_EQUAL(true, leePulsador(1)); 
}

void RUN_UNITY_TESTS() {
        Serial.print("Hola");
    UNITY_BEGIN();

    RUN_TEST(func2);

    RUN_TEST(func3);

    /*RUN_TEST(test_calculator_subtraction);
    RUN_TEST(test_calculator_multiplication);
    RUN_TEST(test_calculator_division);
    RUN_TEST(test_expensive_operation);*/
    UNITY_END();
        Serial.print("ADIOS");
}
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    //delay(4000);
    //setupSimon();
    for(byte n=0;n<BOTONES;n++)
    {

    }
      
    //Serial.begin(115000);
    RUN_UNITY_TESTS();
}


void loop() {
    /*digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);*/
}
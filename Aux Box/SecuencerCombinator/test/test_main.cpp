#include <Snake.h>
#include <Simon.h>
#include <unity.h>
void check_botton(void)
{
    TEST_ASSERT_EQUAL(true, leePulsador(0));
}
void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(check_botton);
    /*RUN_TEST(test_calculator_subtraction);
    RUN_TEST(test_calculator_multiplication);
    RUN_TEST(test_calculator_division);
    RUN_TEST(test_expensive_operation);*/
    UNITY_END();
}
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    RUN_UNITY_TESTS();
}


void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
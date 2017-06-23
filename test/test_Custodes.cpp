#ifdef UNIT_TEST
#include <Arduino.h>
#include <unity.h>
#include "Custodes.h"


Custodes custodes;
// void setUp(void) {
//
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_check_sala_by_time(void){

  TEST_ASSERT_FALSE(custodes.salaCheck(44, 0, 8, 49));
  TEST_ASSERT_FALSE(custodes.salaCheck(56, 2, 8, 100));
  TEST_ASSERT_TRUE(custodes.salaCheck(109, 18, 9, 50));
  TEST_ASSERT_FALSE(custodes.salaCheck(36, 21, 16, 100));
  TEST_ASSERT_FALSE(custodes.salaCheck(113, 6, 2, 49));
  TEST_ASSERT_TRUE(custodes.salaCheck(133, 18, 1, 100));
  TEST_ASSERT_TRUE(custodes.salaCheck(12, 23, 5, 50));
  TEST_ASSERT_FALSE(custodes.salaCheck(57, 19, 19, 100));
  TEST_ASSERT_TRUE(custodes.salaCheck(126, 20, 5, 49));
  TEST_ASSERT_FALSE(custodes.salaCheck(93, 12, 13, 100));
  TEST_ASSERT_FALSE(custodes.salaCheck(143, 22, 18, 50));
}

void test_check_garagem_by_time(void){

  TEST_ASSERT_FALSE(custodes.garagemCheck(44, 0, 8, 49));
  TEST_ASSERT_FALSE(custodes.garagemCheck(56, 2, 8, 100));
  TEST_ASSERT_FALSE(custodes.garagemCheck(109, 18, 9, 50));
  TEST_ASSERT_TRUE(custodes.garagemCheck(36, 21, 16, 100));
  TEST_ASSERT_FALSE(custodes.garagemCheck(113, 6, 2, 49));
  TEST_ASSERT_FALSE(custodes.garagemCheck(133, 18, 1, 100));
  TEST_ASSERT_FALSE(custodes.garagemCheck(12, 23, 5, 50));
  TEST_ASSERT_TRUE(custodes.garagemCheck(57, 19, 19, 100));
  TEST_ASSERT_FALSE(custodes.garagemCheck(126, 20, 5, 49));
  TEST_ASSERT_FALSE(custodes.garagemCheck(93, 12, 13, 100));
  TEST_ASSERT_TRUE(custodes.garagemCheck(143, 22, 18, 50));
}


void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  UNITY_BEGIN();    // IMPORTANT LINE!
}

uint8_t i = 0;
uint8_t max_blinks = 3;

void loop() {
  if (i < max_blinks)
  {
    RUN_TEST(test_check_sala_by_time);
    delay(500);
    RUN_TEST(test_check_garagem_by_time);
    delay(500);
    i++;
  }
  else if (i == max_blinks) {
    UNITY_END(); // stop unit testing
  }
}

#endif

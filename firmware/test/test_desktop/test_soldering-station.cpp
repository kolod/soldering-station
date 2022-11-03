#include <ArduinoFake.h>
#include <unity.h>

using namespace fakeit;
volatile unsigned char PORTD;
volatile unsigned char DDRD;

#include "config.h"
#include "buzzer.h"


void setUp(void) {
    ArduinoFakeReset();
}

void tearDown(void) {
    // clean stuff up here
}

void test_buzzer_setup() {
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    buzzer.setup();

    Verify(Method(ArduinoFake(), pinMode).Using(BUZZER, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(BUZZER, LOW)).Once();
}

void test_buzzer(void) {
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();

    buzzer.setup();
    //buzzer.play(BuzzerPattern::Single, 2, 2);

    Verify(Method(ArduinoFake(), digitalWrite).Using(BUZZER, HIGH)).Once();
    Verify(Method(ArduinoFake(), digitalWrite).Using(BUZZER, LOW)).Once();
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_buzzer_setup);
    return UNITY_END();
}
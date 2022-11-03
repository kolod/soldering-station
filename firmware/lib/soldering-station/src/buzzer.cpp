#include "config.h"
#include "buzzer.h"

void Buzzer::setup() {
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    mPattern = BuzzerPattern::None;
    mLength = 10;
    mPause = 20;
    mTime = millis();    
    mIsBuzzing = false;
}

void Buzzer::loop() {
    if (mPattern == BuzzerPattern::None) {
        mTime = millis();
        return;
    }

    unsigned long time = millis();
    unsigned long delta = time - mTime;

    if (mIsBuzzing) {
        digitalWrite(BUZZER, time & 1);
        if (delta > mLength) {
            digitalWrite(BUZZER, LOW);
            mIsBuzzing = false;
            if (mPattern == BuzzerPattern::Single) mPattern = BuzzerPattern::None;
            else if (mPattern == BuzzerPattern::Double) mPattern = BuzzerPattern::Single;
        }
    } else {
        if (delta > mPause) {
            digitalWrite(BUZZER, HIGH);
            mIsBuzzing = true;
        }
    }

    mTime = time;
}

void Buzzer::play(BuzzerPattern pattern) {
    mPattern = pattern;
}

void Buzzer::play(BuzzerPattern pattern, unsigned char lenght) {
    mPattern = pattern;
    mLength = lenght;
}

void Buzzer::play(BuzzerPattern pattern, unsigned char lenght, unsigned char pause) {
    mPattern = pattern;
    mLength = lenght;
    mPause = pause;
}

void Buzzer::stop() {
    mPattern = BuzzerPattern::None;
}

Buzzer buzzer;

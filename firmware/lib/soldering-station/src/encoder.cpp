#include "encoder.h"

void Encoder::setup() {
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);
    pinMode(ENCODER_KEY, INPUT_PULLUP);

    mButtonFilter = 0;
    mMax = __LONG_MAX__;
    mMin = - __LONG_MAX__;
    mLastState = digitalRead(ENCODER_A);
}

void Encoder::setRange(long min, long max) {
    mMax = max;
    mMin = min;
}

void Encoder::setCallback(EncoderCallback callback) {
    mCallback = callback;
}

void Encoder::loop() {

    if (digitalRead(ENCODER_KEY) == 0) {
        if (mButtonFilter < 10) {
            mButtonFilter++;
        } else {
            mCallback();
        }
    } else if (mButtonFilter) {
        mButtonFilter--;
    }


    auto state = digitalRead(ENCODER_A);
    if (state != mLastState) {
        if (digitalRead(ENCODER_B) != state) {
            if (mCounter < mMax) mCounter++;
        } else {
            if (mCounter > mMin) mCounter--;
        }
   } 
   mLastState = state;
}

long Encoder::value() {
    return mCounter;
}

Encoder encoder;

#pragma once

#include "config.h"

typedef void (*EncoderCallback)();

class Encoder {
private:
    bool mLastState;
    long mCounter;
    long mMin;
    long mMax;

    unsigned char mButtonFilter;
    EncoderCallback mCallback;

public:
    void setup();
    void loop();
    long value();
    void setRange(long min, long max);
    void setCallback(EncoderCallback callback);
};

extern Encoder encoder;
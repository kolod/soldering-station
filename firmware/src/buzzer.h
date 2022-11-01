#pragma once

enum class BuzzerPattern {
    None,
    Single,
    Double,
};

class Buzzer {
private:
    BuzzerPattern mPattern;
    unsigned char mLength;
    unsigned char mPause;
    unsigned long mTime;
    bool mIsBuzzing;

public:
    void setup();
    void loop();
    void play(BuzzerPattern pattern);
    void play(BuzzerPattern pattern, unsigned char lenght);
    void play(BuzzerPattern pattern, unsigned char lenght, unsigned char pause);
    void stop();
};

extern Buzzer buzzer;

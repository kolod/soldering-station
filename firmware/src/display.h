
#pragma once

class Display
{
private:
    unsigned char pos;
	unsigned char buffer[3];
	unsigned long last;

    unsigned char gliph(char ch);

public:
    void setup();
    void loop();
    void clear();
    void print(int value);
};

extern Display display;

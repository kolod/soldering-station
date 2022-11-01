#include "display.h"
#include "buzzer.h"
#include "encoder.h"

extern "C" void setup() {
	display.setup();
	buzzer.setup();
	display.print(0);
	encoder.setup();
	encoder.setRange(0, 999);

	encoder.setCallback([]{
		display.clear();
	});
}

extern "C" void loop() {
	if (!digitalRead(ENCODER_KEY)) {
		buzzer.play(BuzzerPattern::Double);
		//digitalWrite(BUZZER, millis() & 1);
	}

	encoder.loop();
	display.print(encoder.value());
	display.loop();
	buzzer.loop();
}

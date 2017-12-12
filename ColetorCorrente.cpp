#include <Arduino.h>

byte led = 13;
boolean estado = false;

void setup() {
	Serial.begin(9600);
	pinMode(led,OUTPUT);
}

void loop() {
	estado = !estado;
	digitalWrite(led,estado);
	delay(1000);
}

#include <Arduino.h>
#include "libs/Sensor.h"
#include "libs/Leituras.h"
#include "libs/DFT.h"

uint8_t frequenciaRede = 60;
uint8_t numeroAmostras = 64;
uint8_t nHarmonicas = 13;
uint16_t *valoresLidos;
float *harmonicas;

Sensor sensor1(
		"5.36,5.33,5.35,5.35,5.35,5.36,5.37,5.37,5.38,5.38,5.38,5.39,5.39",
		nHarmonicas, A0);
Leituras leitura(frequenciaRede, numeroAmostras);
DFT dft(numeroAmostras);

void setup() {
	Serial.begin(9600);
	valoresLidos = new uint16_t[numeroAmostras];
	harmonicas = new float[nHarmonicas];
}

void loop() {
	leitura.executaLeitura(&sensor1, valoresLidos);

	dft.getHarmonicas(valoresLidos, harmonicas);

	for (int i = 0; i < numeroAmostras; i++) {
		Serial.print(valoresLidos[i]);
		Serial.print(";");
	}

	for (int i = 0; i < nHarmonicas; i++) {
		Serial.print(harmonicas[i]);
		Serial.print(";");
	}
	delay(5000);
}

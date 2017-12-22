#include <Arduino.h>
#include "libs/Sensor.h"
#include "libs/Leituras.h"
#include "libs/DFT.h"

#define DEBUG true

const uint8_t ps64 = (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
const uint8_t ps128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

uint8_t frequenciaRede = 60;
uint8_t numeroAmostras = 32;
uint8_t nHarmonicas = 13;
float *valoresLidos;
float *harmonicas;

extern int __bss_end;
extern void *__brkval;

int memoriaLivre() {
	int memLivre;
	if ((int) __brkval == 0)
		memLivre = ((int) &memLivre) - ((int) &__bss_end);
	else
		memLivre = ((int) &memLivre) - ((int) &__brkval);
	return memLivre;
}

Sensor sensor1(
		"5.36,5.33,5.35,5.35,5.35,5.36,5.37,5.37,5.38,5.38,5.38,5.39,5.39",
		nHarmonicas, A1);
Leituras leitura(frequenciaRede, numeroAmostras);
DFT dft(numeroAmostras);

void setup() {
	//alteração do prescaler do conversor AD
	//ativa prescaler 64
	//ADCSRA &= ~ps128;
	//ADCSRA |= ps64;

	Serial.begin(9600);
	valoresLidos = new float[numeroAmostras];
	harmonicas = new float[nHarmonicas];

	leitura.estimaTempoConversao(&sensor1);

}

void loop() {
	leitura.executaLeitura(&sensor1, valoresLidos);
	dft.calcHarmonicas(valoresLidos, harmonicas);
	dft.calMagX();

	Serial.println("Valores lidos:");
	for (int i = 0; i < numeroAmostras; i++) {
		Serial.print(" ");
		Serial.print(valoresLidos[i]);
	}
	Serial.println("");

	Serial.println("realX: ");
	for (int i = 0; i < numeroAmostras / 2; i++) {
		Serial.print(" ");
		Serial.print(dft.getRealX(i));
	}
	Serial.println("");

	Serial.println("imagX: ");
	for (int i = 0; i < numeroAmostras / 2; i++) {
		Serial.print(" ");
		Serial.print(dft.getImagX(i));

	}
	Serial.println("");

	Serial.println("magnitude:");
	for (int i = 0; i < nHarmonicas; i++) {
		Serial.print(" ");
		Serial.print(dft.getMagX(i), 3);
	}
	Serial.println("");

	Serial.println("magnitude convertida para corrente");
	for (int i = 0; i < nHarmonicas; i++) {
		Serial.print(" ");
		Serial.print(dft.getMagX(i) / sensor1.getGanhoPorHarmonica(i));
	}
	Serial.println("");

	Serial.print("Free memory: ");
	Serial.println(memoriaLivre(), DEC);
	Serial.println("");
	delay(1000);
}


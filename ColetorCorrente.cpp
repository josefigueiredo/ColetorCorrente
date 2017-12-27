#include <Arduino.h>
#include "libs/Sensor.h"
#include "libs/Leituras.h"
#include "libs/DFT.h"

#define DEBUG true

const uint8_t ps64 = (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
const uint8_t ps128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

uint8_t frequenciaRede = 60;
uint8_t numeroAmostras = 64;
uint8_t nHarmonicas = 13;
float *valoresLidos;

extern int __bss_end;
extern void *__brkval;

char cmd;
uint8_t porTempo = 0;



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


void rotina(){
	leitura.executaLeitura(&sensor1, valoresLidos);
	//valoresLidos = {2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50, 2.49, 2.50, 2.50, 2.50, 2.50, 2.50, 2.50};
	//valoresLidos = {2.47, 2.48, 2.49, 2.50, 2.52, 2.53, 2.54, 2.55, 2.55, 2.55, 2.54, 2.54, 2.53, 2.52, 2.51, 2.50, 2.48, 2.47, 2.46, 2.45, 2.45, 2.44, 2.45, 2.45, 2.45, 2.46, 2.47, 2.48, 2.50, 2.51, 2.52, 2.53};
	dft.calcHarmonicas(valoresLidos);
	dft.calcMagnitude();

	Serial.println("Valores lidos:");
	for (int i = 0; i < numeroAmostras; i++) {
		Serial.print(" ");
		Serial.print(valoresLidos[i]);
	}
	Serial.println("");

	Serial.println("realX: ");
	for (int i = 0; i < numeroAmostras / 2; i++) {
		Serial.print(" ");
		Serial.print(dft.getRealX(i),4);
	}
	Serial.println("");

	Serial.println("imagX: ");
	for (int i = 0; i < numeroAmostras / 2; i++) {
		Serial.print(" ");
		Serial.print(dft.getImagX(i),4);

	}
	Serial.println("");

	Serial.println("magnitude em volts:");
	for (int i = 0; i < nHarmonicas; i++) {
		Serial.print(" ");
		Serial.print(dft.getMagX(i), 4);
	}
	Serial.println("");

	Serial.println("magnitude convertida para corrente");
	for (int i = 0; i < nHarmonicas; i++) {
		Serial.print("valorMag: ");Serial.print(dft.getMagX(i+1));Serial.print(" e valorGanho: ");Serial.print(sensor1.getGanhoPorHarmonica(i));

		float tmp = dft.getMagX(i+1) * sensor1.getGanhoPorHarmonica(i);
		Serial.print("/ convertido: ");
		Serial.println(tmp,4);
	}
	Serial.println("");

	Serial.print("Free memory: ");
	Serial.println(memoriaLivre(), DEC);
	Serial.println("");
}

void setup() {
	//alteração do prescaler do conversor AD
	//ativa prescaler 64
	//ADCSRA &= ~ps128;
	//ADCSRA |= ps64;

	Serial.begin(9600);
	valoresLidos = new float[numeroAmostras];
	leitura.estimaTempoConversao(&sensor1);

	rotina();
}

void loop() {

	if(Serial.available()){
		cmd = Serial.read();
		if(cmd == 'l'){
			rotina();
		}
	}else if(porTempo > 59 ){
		rotina();
		porTempo = 0;
	}

	delay(1000);
	porTempo += 1;
}




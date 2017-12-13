#include <Arduino.h>
#include "libs/Sensor.h"
#include "libs/Leituras.h"
#include "libs/DFT.h"

uint8_t frequenciaRede = 60;
uint8_t numeroAmostras = 64;
uint8_t nHarmoncias = 13;

uint16_t valoresLidos[(int)numeroAmostras];
float harmonicas[(int)nHarmoncias];


Sensor sensor1("5.36,5.33,5.35,5.35,5.35,5.36,5.37,5.37,5.38,5.38,5.38,5.39,5.39",nHarmoncias,A0);
Leituras leitura(sensor1,frequenciaRede,numeroAmostras);
DFT dft(numeroAmostras);


void setup() {
	Serial.begin(9600);
}

void loop() {
	leitura.executaLeitura(valoresLidos);



	delay(1000);
}

/*
 * Leituras.cpp
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */

#include "Leituras.h"

Leituras::Leituras(uint8_t f,uint8_t a) {
	// TODO Auto-generated constructor stub
	_freq = f;
	_amostras = a;
}

Leituras::~Leituras() {
	// TODO Auto-generated destructor stub
}

void Leituras::executaLeitura(Sensor *s, uint16_t *valores){
	//uma leitura para inicializar o conversor AD e descartar o tempo.
	uint16_t valor = s->getValor();
	//intervalo entre uma amostra e outra.
	uint16_t intervalo = (1/_freq/_amostras * 1000000) - 18;

	for(uint8_t i=0;i<_amostras;i++){
		valores[i] = s->getValor();
		delayMicroseconds(intervalo);
	}

}

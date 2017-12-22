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
	//intervalo entre uma amostra e outra conforme a frequencia
	uint16_t periodo = (_freq == 60)?16666:20000;
	uint16_t intervalo = (periodo/_amostras) - _tEstimadoConversao;
	Serial.println(_tEstimadoConversao);
	for(uint8_t i=0;i<_amostras;i++){
		valores[i] = s->getValor();
		delayMicroseconds(intervalo);
	}
}


/**
 * Método para calcular o tempo médio cada leitura do conversor AD
 * o valor é importante para descontar da medida de intervalo entre uma amostra e outra
 * não conseguimos ter um valor exato.
 * 24 us é o tempo medio sem alteração do prescaler do conversor.
 */
uint8_t Leituras::estimaTempoConversao(Sensor *s){
	//uma leitura para inicializar o conversor AD e descartar o tempo.
	uint16_t valor = s->getValor();

	unsigned long ini=0,fim=0;
	//laço para fazer calcular otempo médio
	for(uint8_t i=0;i<_amostras;i++){
		valor = s->getValor();
		fim += micros();
	}
	_tEstimadoConversao = (fim - ini)/_amostras;
}

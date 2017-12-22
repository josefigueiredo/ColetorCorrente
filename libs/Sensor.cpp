/*
 * Sensor.cpp
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */

#include "Sensor.h"

/**
 * Construtor de Sensor
 * @params String com valores dos ganhos, numero de harmonicas, porta do sensor
 *
 */
Sensor::Sensor(String s,uint8_t nHarmonicas,uint8_t p) {
	// TODO Auto-generated constructor stub
	setPino(p);
	_nHarmonicas = nHarmonicas;
	_ganhos = new float[_nHarmonicas];
	setGanhoPorHarmonica(s);
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

/**
 * Método privado setPino - configura o pino do sensor
 * @params: pino em que o sensor será instalado
 */
void Sensor::setPino(uint8_t p) {
	// TODO Auto-generated constructor stub
	_pino = p;
	pinMode(_pino, INPUT);
}

/**
 * Metodo setGanhoPorHarmonica
 * carrega os valores dos ganhos de cada harmonica em um vetor de tamanho variável
 * @params: string com os ganhos separados por vírgula.
 */
void Sensor::setGanhoPorHarmonica(String s){
	uint8_t iniSub = 0;
	uint8_t fimSub = s.indexOf(",");
	String partial;

	for(uint8_t i=0;i<_nHarmonicas;i++){
		partial = s.substring(iniSub,fimSub);
		_ganhos[i] = partial.toFloat();
		iniSub = fimSub+1;
		fimSub = s.indexOf(",",iniSub);
	}
}
/**
 * Método getGanhoPorHarmonica
 * retorna o ganho da harmonica especificada
 * @return valor do ganho da harmonica
 */
float Sensor::getGanhoPorHarmonica(uint8_t harmonica){
	return _ganhos[harmonica];
}

/**
 * Método getValor
 * faz uma leitura de valor do sensor.
 */
uint16_t Sensor::getValor(){
	return analogRead(_pino);

}

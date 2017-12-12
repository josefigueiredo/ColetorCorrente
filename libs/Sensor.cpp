/*
 * Sensor.cpp
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */

#include "Sensor.h"


Sensor::Sensor(String s,uint8_t p,uint8_t nHarmonicas,) {
	// TODO Auto-generated constructor stub
	_nHarmonicas = nHarmonicas;
	setPino(p);
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::setPino(uint8_t p) {
	// TODO Auto-generated constructor stub
	_pino = p;
	pinMode(_pino, INPUT);
}


void Sensor::setGanhoPorHarmonica(String s){
	for(uint8_t i=0;i<_nHarmonicas,i++){

	}

}

float Sensor::getGanhoPorHarmonica(uint8_t harmonica){

}

uint16_t Sensor::getValor(){
	return analogRead(_pino);

}

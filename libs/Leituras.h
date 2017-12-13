/*
 * Leituras.h
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */
#include <Arduino.h>
#include "Sensor.h"


#ifndef LIBS_LEITURAS_H_
#define LIBS_LEITURAS_H_

class Leituras {
private:
	uint8_t _freq;
	uint8_t _amostras;
	//uint16_t _leituras[_amostras];

public:
	Leituras(uint8_t,uint8_t);
	virtual ~Leituras();
	void executaLeitura(Sensor *, uint16_t *);
};

#endif /* LIBS_LEITURAS_H_ */

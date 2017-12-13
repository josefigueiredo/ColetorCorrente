/*
 * DFT.h
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */
#include <Arduino.h>


#ifndef LIBS_DFT_H_
#define LIBS_DFT_H_

class DFT {
private:
	uint8_t _amostras;
public:
	DFT(uint8_t);
	virtual ~DFT();
	void getHarmonicas(uint16_t *,float *);
};

#endif /* LIBS_DFT_H_ */

/*
 * DFT.cpp
 *
 *  Created on: 12 de dez de 2017
 *      Author: jose
 */

#include "DFT.h"

DFT::DFT(uint8_t n) {
	// TODO Auto-generated constructor stub
	_amostras = n;
}

DFT::~DFT() {
	// TODO Auto-generated destructor stub
}

void DFT::getHarmonicas(uint16_t *origem, float *harmonicas) {
	float R[_amostras], I[_amostras];
	float accReal = 0.0, accImag = 0.0;

	//aplica a dft gerando dois vetores: Real e Imaginario
	for (int k = 0; k < _amostras; k++) {
		for (int j = 0; j < _amostras; j++) {
			accReal += origem[j] * cos((2 * M_PI * j * k) / _amostras);
			accImag += -origem[j] * sin((2 * M_PI * j * k) / _amostras);
		}
		R[k] = accReal;
		I[k] = accImag;
		accReal = 0;
		accImag = 0;
	}

	//vetor de harmonicas
	for (int i = 0; i < _amostras; i++) {
		if (i == 0) {
			harmonicas[i] = R[i];
		} else {
			harmonicas[i] = sqrt((pow(R[i], 2) + pow(I[i], 2)));
		}
	}

}


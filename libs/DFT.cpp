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
	_realX = new float[(_amostras / 2)+1];
	_imagX = new float[(_amostras / 2)+1];
	_magX = new float[(_amostras / 2)+1];
	_phaseX = new float[(_amostras / 2)+1];
}

DFT::~DFT() {
	// TODO Auto-generated destructor stub
}

void DFT::calcHarmonicas(float *origem) {
	float accReal = 0.0, accImag = 0.0;

	//aplica a dft gerando dois vetores: Real e Imaginario
	for (int k = 0; k < _amostras / 2; k++) {
		for (int i = 0; i < _amostras; i++) {
			accReal += origem[i] * cos(_piVezes2 * k * i / _amostras);
			accImag += origem[i] * sin(_piVezes2 * k * i / _amostras);
		}
		if(k == 0){
			_realX[k] = accReal/_amostras;
			_imagX[k] = accImag/_amostras;
		}else{
			_realX[k] = 2*accReal/_amostras;
			_imagX[k] = 2*accImag/_amostras;
		}
		accReal = 0;
		accImag = 0;
	}
}


void DFT::calcMagnitude() {
	_magX[0] = sqrt(_realX[0]*_realX[0]);
	for (int i = 1; i < (_amostras / 2)+1; i++) {
		_magX[i] = sqrt(_realX[i] *_realX[i] + _imagX[i] *_imagX[i]);
	}
}

float DFT::getImagX(uint8_t i) {
	return _imagX[i];
}

float DFT::getRealX(uint8_t i) {
	return _realX[i];
}

float DFT::getMagX(uint8_t i) {
	return _magX[i];
}

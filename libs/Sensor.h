/*
 * Sensor.h
 *
 *  Created on: 12 de dez de 2017
 *  Author: jose
 */
#include <Arduino.h>

#ifndef LIBS_SENSOR_H_
#define LIBS_SENSOR_H_

class Sensor {
private:
	uint8_t _pino;
	uint8_t _nHarmonicas;

	float[14]__ganhos;

	void setPino(uint8_t);

public:
	Sensor(String,uint8_t,uint8_t);
	virtual ~Sensor();

	void setGanhoPorHarmonica(String);
	float getGanhoPorHarmonica(uint8_t);
	uint16_t getValor();
	void setPino(uint16_t);

};

#endif /* LIBS_SENSOR_H_ */

/*
 * Aereo.h
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#ifndef AEREO_H_
#define AEREO_H_

typedef struct{
		float constVolumetrica;
		float valorPorKg;
	}Aereo;


	Aereo* aer_new();
	Aereo* aer_newParam(float constVolum, float precio);
	Aereo* aer_newParamTxt(char* constVolum, char* precio);
	int aer_delete(Aereo* this);

	int aer_setConstVolum(Aereo* this, float constVolum);
	float aer_getConstVolum(Aereo* this,int* flagError);
	int aer_setPrecio(Aereo* this, float precio);
	float aer_getPrecio(Aereo* this,int* flagError);
#endif /* AEREO_H_ */

/*
 * Maritimo.h
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#ifndef MARITIMO_H_
#define MARITIMO_H_

typedef struct{
		float metrosCubicos;
		float valorContenedor;
	}Maritimo;

	Maritimo* mar_new(void);
	Maritimo* mar_newParam(float mtsCubicos, float precio);
	Maritimo* mar_newParamTxt(char* mtsCubicos, char* precio);
	int mar_delete(Maritimo* this);


	int mar_setMtsCubicos(Maritimo* this, float mtsCubicos);
	float mar_getMtsCubicos(Maritimo* this,int* flagError);
	int mar_setPrecio(Maritimo* this, float precio);
	float mar_getPrecio(Maritimo* this,int* flagError);
//	int mar_setIdMaritimo(Maritimo* this, int idMaritimo);
//	int mar_getIdMaritimo(Maritimo* this,int* flagError);

#endif /* MARITIMO_H_ */

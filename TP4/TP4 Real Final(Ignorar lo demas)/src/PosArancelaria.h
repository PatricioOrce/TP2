/*
 * PosArancelaria.h
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#ifndef POSARANCELARIA_H_
#define POSARANCELARIA_H_
#include "Dictionary.h"

typedef struct{
		char nomenclador[64];
		float seguro;
		float porcentajeDeInportacion;
		float tasaEstadistica;
		char tipoDeLicencia[64];
	}PosArancelaria;

PosArancelaria* posAr_new(void);
PosArancelaria* posAr_newParam(char* nomenclatura,float porcentajeSeguro,float porcentajeImportacion,
		float porcentajeTasaEst,char* tipoLicencia);
PosArancelaria* posAr_newParamTxt(char* nomenclatura,char* porcentajeSeguro,char* porcentajeImportacion,
		char* porcentajeTasaEst,char* tipoLicencia);
int posAr_delete(PosArancelaria* this);
PosArancelaria* posAr_buscarPorId(LinkedList* pListaPosArancelarias,int idABuscar);

int posAr_setSeguro(PosArancelaria* this, int seguro);
float posAr_getSeguro(PosArancelaria* this,int* flagError);
int posAr_setPorcDeImportacion(PosArancelaria* this, int porcentajeDeInportacion);
float posAr_getPorcDeImportacion(PosArancelaria* this,int* flagError);
int posAr_setTasaEstadistica(PosArancelaria* this, float tasaEstadistica);
float posAr_getTasaEstadistica(PosArancelaria* this,int* flagError);
int posAr_setNomenclador(PosArancelaria* this, char* nomenclador);
char* posAr_getNomenclador(PosArancelaria* this,int* flagError);
int posAr_setTipoDeLicencia(PosArancelaria* this, char* tipoDeLicencia);
char* posAr_getTipoDeLicencia(PosArancelaria* this,int* flagError);


void posAr_setearValorInicialDeId(Dictionary* pDictionaryPosArancelaria);
int posAr_generarId(void);

#endif /* POSARANCELARIA_H_ */

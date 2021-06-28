/*
 * PosArancelaria.c
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn2.h"
#include "PosArancelaria.h"


PosArancelaria* posAr_new(void)
{
	return (PosArancelaria*) malloc(sizeof(PosArancelaria));
}

PosArancelaria* posAr_newParam(char* nomenclatura,float porcentajeSeguro,float porcentajeImportacion,float porcentajeTasaEst,char* tipoLicencia)
{
	PosArancelaria* auxPosAr = posAr_new();
	if(auxPosAr != NULL)
	{
		if  ( 	posAr_setNomenclador(auxPosAr,nomenclatura) < 0 ||
				posAr_setSeguro(auxPosAr, porcentajeSeguro) < 0 ||
				posAr_setPorcDeImportacion(auxPosAr, porcentajeImportacion) < 0 ||
				posAr_setTasaEstadistica(auxPosAr,porcentajeTasaEst) < 0 ||
				posAr_setTipoDeLicencia(auxPosAr,tipoLicencia) < 0)
		{
			posAr_delete(auxPosAr);
			auxPosAr = NULL;
		}
	}
	return auxPosAr;;
}

PosArancelaria* posAr_newParamTxt(char* nomenclatura,char* porcentajeSeguro,char* porcentajeImportacion,char* porcentajeTasaEst,char* tipoLicencia)
{
	PosArancelaria* auxPosAr = posAr_new();
	if(auxPosAr != NULL)
	{
		if  ( 	posAr_setNomenclador(auxPosAr,nomenclatura) < 0 ||
				posAr_setSeguro(auxPosAr, atof(porcentajeSeguro)) < 0 ||
				posAr_setPorcDeImportacion(auxPosAr, atof(porcentajeImportacion)) < 0 ||
				posAr_setTasaEstadistica(auxPosAr,atof(porcentajeTasaEst)) < 0 ||
				posAr_setTipoDeLicencia(auxPosAr,tipoLicencia) < 0)
		{
			posAr_delete(auxPosAr);
			auxPosAr = NULL;
		}
	}
	return auxPosAr;;
}

int posAr_delete(PosArancelaria* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		this=NULL;
		retorno = 0;
	}
	return retorno;
}

int posAr_setSeguro(PosArancelaria* this, int seguro)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(seguro)==0)
	{
		this->seguro = seguro;
		retorno = 0;
	}
	return retorno;
}

float posAr_getSeguro(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float seguro = -1;
	if(this != NULL && flagError != NULL )
	{
		seguro=this->seguro;
		*flagError = 0;
	}
	return seguro;
}

int posAr_setPorcDeImportacion(PosArancelaria* this, int porcentajeDeInportacion)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(porcentajeDeInportacion)==0)
	{
		this->porcentajeDeInportacion = porcentajeDeInportacion;
		retorno = 0;
	}
	return retorno;
}

float posAr_getPorcDeImportacion(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float porcentajeDeInportacion;
	if(this != NULL && flagError != NULL )
	{
		porcentajeDeInportacion = this->porcentajeDeInportacion;
		*flagError = 0;
	}
	return porcentajeDeInportacion;
}


int posAr_setTasaEstadistica(PosArancelaria* this, float tasaEstadistica)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(tasaEstadistica)==0)
	{
		this->tasaEstadistica = tasaEstadistica;
		retorno = 0;
	}
	return retorno;
}

float posAr_getTasaEstadistica(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	float tasaEstadistica;
	if(this != NULL && flagError != NULL )
	{
		tasaEstadistica = this->tasaEstadistica;
		*flagError = 0;
	}
	return tasaEstadistica;
}

int posAr_setNomenclador(PosArancelaria* this, char* nomenclador)
{
	int retorno = -1;
	if(this != NULL)
	{
		strcpy(this->nomenclador, nomenclador);
		retorno = 0;
	}
	return retorno;
}

char* posAr_getNomenclador(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	char* nomenclador = NULL;
	if(this != NULL && flagError != NULL )
	{
		nomenclador = this->nomenclador;
		*flagError = 0;
	}
	return nomenclador;
}

int posAr_setTipoDeLicencia(PosArancelaria* this, char* tipoDeLicencia)
{
	int retorno = -1;
	if(this != NULL && isTipo(tipoDeLicencia)==0)
	{
		strcpy(this->tipoDeLicencia,tipoDeLicencia);
		retorno = 0;
	}
	return retorno;
}

char* posAr_getTipoDeLicencia(PosArancelaria* this,int* flagError)
{
	*flagError = -1;
	char* auxTipoDeLicencia = NULL;
	if(this != NULL && flagError != NULL )
	{
		auxTipoDeLicencia =this->tipoDeLicencia;
		*flagError = 0;
	}
	return auxTipoDeLicencia;
}


/*
 * Aereo.c
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Aereo.c
 *
 *  Created on: Jun 16, 2021
 *      Author: facu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn2.h"
#include "Aereo.h"

Aereo* aer_new(void)
{
	return (Aereo*) malloc(sizeof(Aereo));
}

Aereo* aer_newParam(float constVolum, float precio)
{
	Aereo* auxAereo = aer_new();
	if(auxAereo != NULL)
	{
		if  ( 	aer_setConstVolum(auxAereo, constVolum) < 0 ||
				aer_setPrecio(auxAereo, precio) < 0)
		{
			aer_delete(auxAereo);
			auxAereo = NULL;
		}
	}
	return auxAereo;
}

Aereo* aer_newParamTxt(char* constVolum, char* precio)
{
	Aereo* auxAereo = aer_new();
	if(auxAereo != NULL)
	{
		if  ( 	aer_setConstVolum(auxAereo, atof(constVolum)) < 0 ||
				aer_setPrecio(auxAereo, atof(precio)) < 0)
		{
			aer_delete(auxAereo);
			auxAereo = NULL;
		}
	}
	return auxAereo;
}

int aer_delete(Aereo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int aer_setConstVolum(Aereo* this, float constVolum)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(constVolum)==0 )
	{
		this->constVolumetrica = constVolum;
		retorno = 0;
	}
	return retorno;
}

float aer_getConstVolum(Aereo* this,int* flagError)
{
	*flagError = -1;
	float auxConstVolum = -1;
	if(this != NULL && flagError != NULL )
	{
		auxConstVolum=this->constVolumetrica;
		*flagError = 0;
	}
	return auxConstVolum;
}

int aer_setPrecio(Aereo* this, float precio)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(precio)==0 )
	{
		this->valorPorKg = precio;
		retorno = 0;
	}
	return retorno;
}

float aer_getPrecio(Aereo* this,int* flagError)
{
	*flagError = -1;
	float auxPrecio = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPrecio=this->valorPorKg;
		*flagError = 0;
	}
	return auxPrecio;
}




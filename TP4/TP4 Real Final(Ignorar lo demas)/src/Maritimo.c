/*
 * Maritimo.c
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn2.h"
#include "Maritimo.h"

Maritimo* mar_new(void)
{
	return (Maritimo*) malloc(sizeof(Maritimo));
}

Maritimo* mar_newParam(float mtsCubicos, float precio)
{
	Maritimo* auxMaritimo = mar_new();
	if(auxMaritimo != NULL)
	{
		if  ( 	mar_setMtsCubicos(auxMaritimo, mtsCubicos) < 0 ||
				mar_setPrecio(auxMaritimo, precio) < 0)
		{
			mar_delete(auxMaritimo);
			auxMaritimo = NULL;
		}
	}
	return auxMaritimo;
}

Maritimo* mar_newParamTxt(char* mtsCubicos, char* precio)
{
	Maritimo* auxMaritimo = mar_new();
	if(auxMaritimo != NULL)
	{
		if  ( 	mar_setMtsCubicos(auxMaritimo, atof(mtsCubicos)) < 0 ||
				mar_setPrecio(auxMaritimo, atof(precio)) < 0)
		{
			mar_delete(auxMaritimo);
			auxMaritimo = NULL;
		}
	}
	return auxMaritimo;
}

int mar_delete(Maritimo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int mar_setMtsCubicos(Maritimo* this, float mtsCubicos)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(mtsCubicos)==0 )
	{
		this->metrosCubicos = mtsCubicos;
		retorno = 0;
	}
	return retorno;
}

float mar_getMtsCubicos(Maritimo* this,int* flagError)
{
	*flagError = -1;
	float auxMtsCubicos = -1;
	if(this != NULL && flagError != NULL )
	{
		auxMtsCubicos=this->metrosCubicos;
		*flagError = 0;
	}
	return auxMtsCubicos;
}

int mar_setPrecio(Maritimo* this, float precio)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(precio)==0 )
	{
		this->valorContenedor = precio;
		retorno = 0;
	}
	return retorno;
}

float mar_getPrecio(Maritimo* this,int* flagError)
{
	*flagError = -1;
	float auxPrecio = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPrecio=this->valorContenedor;
		*flagError = 0;
	}
	return auxPrecio;
}
/*
int mar_setIdMaritimo(Maritimo* this, int idMaritimo)
{
	int retorno = -1;
	if(this != NULL && isIntegerValue(idMaritimo)==0 )
	{
		this->idMaritimo = idMaritimo;
		retorno = 0;
	}
	return retorno;
}

int mar_getIdMaritimo(Maritimo* this,int* flagError)
{
	*flagError = -1;
	float auxIdMaritimo = -1;
	if(this != NULL && flagError != NULL )
	{
		auxIdMaritimo=this->idMaritimo;
		*flagError = 0;
	}
	return auxIdMaritimo;
}
*/

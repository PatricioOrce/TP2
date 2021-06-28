/*
 * Articulo.c
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn2.h"
#include "Articulo.h"


Articulo* art_new(void)
{
	return (Articulo*) malloc(sizeof(Articulo));
}

Articulo* art_newParametros(char* nombre,char* codigo,char* paisDeFabricacion,float valorFob,
		float pesosEnKg, float ancho, float alto, float profundidad, char* idPosicionArancelaria)
{
	Articulo* auxArticulo = art_new();
	if(auxArticulo != NULL)
	{
		if  (	art_setNombre(auxArticulo, nombre) != 0 ||
				art_setCodigo(auxArticulo, codigo) != 0  ||
				art_setPaisDeFabricacion(auxArticulo, paisDeFabricacion) != 0 ||
				art_setValorFOB(auxArticulo, valorFob) != 0 ||
				art_setPesosEnKg(auxArticulo, pesosEnKg) != 0 ||
				art_setAncho(auxArticulo, ancho) != 0 ||
				art_setAlto(auxArticulo, alto) != 0 ||
				art_setProfundidad(auxArticulo, profundidad) != 0 ||
				art_setIdPosicionArancelaria(auxArticulo, idPosicionArancelaria) != 0)
		{
			art_delete(auxArticulo);
			auxArticulo = NULL;
		}
	}
	return auxArticulo;
}

Articulo* art_newParametrosTxt(char* nombre,char* codigo,char* paisDeFabricacion,char* valorFob,
		char* pesosEnKg, char* ancho, char* alto, char* profundidad, char* idPosicionArancelaria)
{
	Articulo* auxArticulo = art_new();
	if(auxArticulo != NULL)
	{
		if  (	art_setNombre(auxArticulo, nombre) != 0 ||
				art_setCodigo(auxArticulo, codigo) != 0 ||
				art_setPaisDeFabricacion(auxArticulo, paisDeFabricacion) != 0 ||
				art_setValorFOB(auxArticulo, atof(valorFob)) != 0 ||
				art_setPesosEnKg(auxArticulo, atof(pesosEnKg)) != 0 ||
				art_setAncho(auxArticulo, atof(ancho)) != 0 ||
				art_setAlto(auxArticulo, atof(alto)) != 0 ||
				art_setProfundidad(auxArticulo, atof(profundidad)) != 0 ||
				art_setIdPosicionArancelaria(auxArticulo, idPosicionArancelaria) != 0)
		{
			art_delete(auxArticulo);
			auxArticulo = NULL;
		}
	}
	return auxArticulo;
}

int art_delete(Articulo* this)
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

int art_setNombre(Articulo* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && isArticleName(nombre)==0)
	{
		strncpy(this->nombre, nombre,sizeof(this->nombre));
		retorno = 0;
	}
	return retorno;
}

char* art_getNombre(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* nombre = NULL;
	if(this != NULL && flagError != NULL )
	{
		nombre = this->nombre;
		*flagError = 0;
	}
	return nombre;
}



int art_setCodigo(Articulo* this, char* codeArticulo)
{
	int retorno = -1;
	if(this != NULL && isAlphanumeric(codeArticulo)==0)
	{
		strncpy(this->codigo, codeArticulo,sizeof(this->codigo));
		retorno = 0;
	}
	return retorno;
}

char* art_getCodigo(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxCodeArticulo = NULL;
	if(this != NULL && flagError != NULL )
	{
		auxCodeArticulo = this->codigo;
		*flagError = 0;
	}
	return auxCodeArticulo;
}



int art_setDescripcion(Articulo* this, char* descripcion)
{
	int retorno = -1;
	if(this != NULL && utn_isDNI(descripcion)==0)
	{
		strncpy(this->descripcion, descripcion,sizeof(this->descripcion));
		retorno = 0;
	}
	return retorno;
}

char* art_getDescripcion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* descripcion = NULL;
	if(this != NULL && flagError != NULL )
	{
		descripcion=this->descripcion;
		*flagError = 0;
	}
	return descripcion;
}



int art_setPaisDeFabricacion(Articulo* this, char* paisDeFabricacion)
{
	int retorno = -1;
	if(this != NULL && isName(paisDeFabricacion)==0)
	{
		strcpy(this->paisDeFabricacion, paisDeFabricacion);
		retorno = 0;

	}
	return retorno;
}

char* art_getPaisDeFabricacion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* paisDeFabricacion = NULL;
	if(this != NULL && flagError != NULL )
	{
		paisDeFabricacion = this->paisDeFabricacion;
		*flagError = 0;
	}
	return paisDeFabricacion;
}


int art_setValorFOB(Articulo* this, float valorFob)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(valorFob)==0)
	{
		this->valorFob = valorFob;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFOB(Articulo* this,int* flagError)
{
	*flagError = -1;
	float valorFob = -1;
	if(this != NULL && flagError != NULL )
	{
		valorFob=this->valorFob;
		*flagError = 0;
	}
	return valorFob;
}

int art_setPesosEnKg(Articulo* this, float pesosEnKg)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(pesosEnKg)==0)
	{
		this->pesosEnKg = pesosEnKg;
		retorno = 0;
	}
	return retorno;
}

float art_getPesosEnKg(Articulo* this,int* flagError)
{
	*flagError = -1;
	float pesosEnKg = -1;
	if(this != NULL && flagError != NULL )
	{
		pesosEnKg=this->pesosEnKg;
		*flagError = 0;
	}
	return pesosEnKg;
}


int art_setAncho(Articulo* this, float ancho)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(ancho)==0)
	{
		this->ancho = ancho;
		retorno = 0;
	}
	return retorno;
}

float art_getAncho(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxAncho = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAncho=this->ancho;
		*flagError = 0;
	}
	return auxAncho;
}

int art_setAlto(Articulo* this, float alto)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(alto)==0)
	{
		this->alto = alto;
		retorno = 0;
	}
	return retorno;
}

float art_getAlto(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxAlto = -1;
	if(this != NULL && flagError != NULL )
	{
		auxAlto=this->alto;
		*flagError = 0;
	}
	return auxAlto;
}

int art_setProfundidad(Articulo* this, float profundidad)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(profundidad)==0)
	{
		this->profundidad = profundidad;
		retorno = 0;
	}
	return retorno;
}

float art_getProfundidad(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxProfundidad = -1;
	if(this != NULL && flagError != NULL )
	{
		auxProfundidad=this->profundidad;
		*flagError = 0;
	}
	return auxProfundidad;
}

int art_setIdPosicionArancelaria(Articulo* this, char* idPosicionArancelaria)
{
	int retorno = -1;
	if(this != NULL && isAlphanumeric(idPosicionArancelaria)==0)
	{
		strcpy(this->posArancel, idPosicionArancelaria);
		retorno = 0;
	}
	return retorno;
}

char* art_getIdPosicionArancelaria(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxIdPosicionArancelaria = NULL;
	if(this != NULL && flagError != NULL )
	{
		auxIdPosicionArancelaria=this->posArancel;
		*flagError = 0;
	}
	return auxIdPosicionArancelaria;
}



int art_setValorFinalAereo(Articulo* this, float comodin)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(comodin)==0)
	{
		this->valorFinalAereo = comodin;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFinalAereo(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxProfundidad = -1;
	if(this != NULL && flagError != NULL )
	{
		auxProfundidad=this->valorFinalAereo;
		*flagError = 0;
	}
	return auxProfundidad;
}

int art_setValorFinalMaritimo(Articulo* this, float comodin)
{
	int retorno = -1;
	if(this != NULL && isFloatValue(comodin)==0)
	{
		this->valorFinalMaritimo = comodin;
		retorno = 0;
	}
	return retorno;
}

float art_getValorFinalMaritimo(Articulo* this,int* flagError)
{
	*flagError = -1;
	float auxProfundidad = -1;
	if(this != NULL && flagError != NULL )
	{
		auxProfundidad=this->valorFinalMaritimo;
		*flagError = 0;
	}
	return auxProfundidad;
}


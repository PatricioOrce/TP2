/*
 * Informes.c
 *
 *  Created on: 19 jun. 2021
 *      Author: Pato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn2.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "Parser.h"
#include "Articulo.h"
#include "PosArancelaria.h"
#include "Controller.h"
#include "Maritimo.h"
#include "Aereo.h"
#include "Informes.h"

float info_getBaseImponibleAereo(Articulo* pArticulo,Aereo* pAereo, PosArancelaria* pPosArancelaria)
{
	int flagError;
	float valorFob;
	float costoEnvioAereo;
	float seguro;
	float porcentajeSeguro;
	float baseImponible = -1;

	if(pArticulo != NULL && pAereo != NULL && pPosArancelaria != NULL)
	{
		porcentajeSeguro = posAr_getSeguro(pPosArancelaria, &flagError);
		valorFob = art_getValorFOB(pArticulo, &flagError);
		costoEnvioAereo = info_getCostoAvion(pArticulo, pAereo);
		seguro = (valorFob * porcentajeSeguro) / 100;
		baseImponible = valorFob + seguro + costoEnvioAereo;
	}
	return baseImponible;
}
float info_getBaseImponibleMaritimo(Articulo* pArticulo,Maritimo* pMaritimo, PosArancelaria* pPosArancelaria)
{
	int flagError;
	float valorFob;
	float costoEnvioMaritimo;
	float seguro;
	float porcentajeSeguro;
	float baseImponible = -1;

	if(pArticulo != NULL && pMaritimo != NULL && pPosArancelaria != NULL)
	{
		porcentajeSeguro = posAr_getSeguro(pPosArancelaria, &flagError);
		valorFob = art_getValorFOB(pArticulo, &flagError);
		costoEnvioMaritimo = info_getCostoBarco(pArticulo, pMaritimo);
		seguro = (valorFob * porcentajeSeguro) / 100;
		baseImponible = valorFob + seguro + costoEnvioMaritimo;
	}
	return baseImponible;
}

float info_getCostoAvion(Articulo* pArticulo,Aereo* pAereo)
{
	float retorno;
	int flagError;
	float volumen;
	float pesoDelProductoEnKg;
	float constanteVolumetrico;
	float resultadoVolumEnKG;
	float pesoVolumetrico;
	float alto;
	float ancho;
	float profundidad;
	float valorPorKg;
	float pesoReal;

	if(pArticulo != NULL && pAereo != NULL)
	{
		pesoDelProductoEnKg = art_getPesosEnKg(pArticulo, &flagError);
		valorPorKg = aer_getPrecio(pAereo, &flagError);
		alto = art_getAlto(pArticulo, &flagError);
		ancho = art_getAncho(pArticulo, &flagError);
		profundidad = art_getProfundidad(pArticulo, &flagError);
		constanteVolumetrico = aer_getConstVolum(pAereo, &flagError);

		pesoReal = pesoDelProductoEnKg * valorPorKg;
		volumen = (alto * ancho * profundidad);
		resultadoVolumEnKG = volumen / constanteVolumetrico;
		pesoVolumetrico = resultadoVolumEnKG * valorPorKg;

		if(pesoReal > pesoVolumetrico)
		{
			retorno = pesoReal;
		}
		else
		{
			retorno = pesoVolumetrico;
		}
	}
	return retorno;
}

float info_getCostoBarco(Articulo* pArticulo,Maritimo* pMaritimo)
{
	float retorno;
	int flagError;
	float alto = art_getAlto(pArticulo, &flagError);
	float ancho = art_getAncho(pArticulo, &flagError);
	float profundidad = art_getProfundidad(pArticulo, &flagError);
	float metrosCubicos = mar_getMtsCubicos(pMaritimo, &flagError);
	float valorContenedor = mar_getPrecio(pMaritimo, &flagError);
	float totalMtsCubicos;
	float valorPorKg;
	float costoFinal;

	if(pArticulo != NULL && pMaritimo != NULL)
	{
		totalMtsCubicos=(alto*ancho*profundidad)/(float)(100*100*100);
		valorPorKg = valorContenedor/metrosCubicos;
		costoFinal=totalMtsCubicos*valorPorKg;
		retorno = costoFinal;
	}
	return retorno;
}

float info_getCostoNacionalAvion(Articulo* pArticulo,PosArancelaria* pPosArancelaria,Aereo* pAereo)
{
	int flagError;
	float baseImponible;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	float importacion;
	float tasaEst;
	float precioFinal = -1;

	if(pArticulo != NULL && pPosArancelaria != NULL && pAereo != NULL)
	{
		porcentajeImportacion = posAr_getPorcDeImportacion(pPosArancelaria, &flagError);
		porcentajeTasaEst = posAr_getTasaEstadistica(pPosArancelaria, &flagError);
		baseImponible = info_getBaseImponibleAereo(pArticulo, pAereo, pPosArancelaria);

		if(baseImponible > -1)
		{
			importacion = (baseImponible * porcentajeImportacion) / 100;
			tasaEst = (baseImponible * porcentajeTasaEst) / 100;
			precioFinal = baseImponible + importacion + tasaEst;
		}
	}
	return precioFinal;
}

float info_getCostoNacionalBarco(Articulo* pArticulo,PosArancelaria* pPosArancelaria,Maritimo* pMaritimo)
{
	int flagError;
	float baseImponible;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	float importacion;
	float tasaEst;
	float precioFinal = -1;


	if(pArticulo != NULL && pPosArancelaria != NULL && pMaritimo != NULL)
	{
		porcentajeImportacion = posAr_getPorcDeImportacion(pPosArancelaria, &flagError);
		porcentajeTasaEst = posAr_getTasaEstadistica(pPosArancelaria, &flagError);
		baseImponible = info_getBaseImponibleMaritimo(pArticulo, pMaritimo, pPosArancelaria);
		if(baseImponible > -1)
		{
			importacion = (baseImponible * porcentajeImportacion) / 100;
			tasaEst = (baseImponible * porcentajeTasaEst) / 100;
			precioFinal = baseImponible + importacion + tasaEst;
		}
	}
	return precioFinal;
}

float info_listarArticulosConCostosFinales(Dictionary* pDiccionarioArticulo,Dictionary* pDiccionarioPosArancelaria,LinkedList* listaMaritima, LinkedList* listaAerea)
{
	float retorno = -1;
	float valorFinalAereo;
	float valorFinalMaritimo;
	int flagError;
	int size;
	char* idPosArancelariaStr;
	LinkedList* listaAux;
	Articulo* articuloAux;
	PosArancelaria* posArancelariaAux;
	Maritimo* pMaritimo;
	Aereo* pAereo;

	if(pDiccionarioArticulo!=NULL &&  listaMaritima!=NULL && listaAerea !=NULL)
	{

		pMaritimo = ll_get(listaMaritima, 0);
		pAereo = ll_get(listaAerea,0);
		listaAux = dict_getValues(pDiccionarioArticulo);
		size = ll_len(listaAux);
		for(int i=0;i<size;i++)
		{
			printf("-----------------------------------------------------------------------\n");
			articuloAux = ll_get(listaAux, i);
			if(articuloAux!=NULL)
			{
				idPosArancelariaStr = art_getIdPosicionArancelaria(articuloAux, &flagError);

				posArancelariaAux = dict_get(pDiccionarioPosArancelaria, idPosArancelariaStr);
				valorFinalMaritimo = info_getCostoNacionalBarco(articuloAux, posArancelariaAux, pMaritimo);
				valorFinalAereo = info_getCostoNacionalAvion(articuloAux, posArancelariaAux, pAereo);
				art_setValorFinalAereo(articuloAux, valorFinalAereo);
				art_setValorFinalMaritimo(articuloAux, valorFinalMaritimo);

				printf("Nombre: [%s]\tCodigo: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\nValor con aereo [U$D%.2f]\tValor con barco [U$D%.2f]\n",

						art_getNombre(articuloAux, &flagError),
						art_getCodigo(articuloAux, &flagError),
						art_getPaisDeFabricacion(articuloAux, &flagError),
						art_getValorFOB(articuloAux, &flagError),
						art_getPesosEnKg(articuloAux, &flagError),
						art_getAlto(articuloAux, &flagError),
						art_getAncho(articuloAux, &flagError),
						art_getProfundidad(articuloAux, &flagError),
						valorFinalAereo, valorFinalMaritimo);
			}

		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}


int funcionCriterio(void* pArticulo, char* arg)
{
	int retorno = -1;
	char posAr[64];
	int flagError = -1;
	Articulo* auxArticulo;
	if(pArticulo!=NULL)
	{
		auxArticulo = (Articulo*)pArticulo;
		strcpy(posAr, art_getIdPosicionArancelaria(auxArticulo, &flagError));
		if(strcmp(posAr,arg)!=0)
		{
			//art_setValorFOB(pArticulo, 0);
			retorno = 0;
		}
	}
	return retorno;
}

int funcionCriterioSort(void* pArticulo,void* pArticuloDos)
{
	int retorno = -1;
	float* auxPrecioUno;
	float* auxPrecioDos;
	if(pArticulo!=NULL && pArticuloDos!=NULL)
	{
		auxPrecioUno = (float*)pArticulo;
		auxPrecioDos = (float*)pArticuloDos;
		if(auxPrecioUno > auxPrecioDos)
		{
			retorno = 1;
		}
	}
	return retorno;
}


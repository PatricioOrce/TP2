/*
 * Parser.c
 *
 *  Created on: 16 jun. 2021
 *      Author: Pato
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Articulo.h"
#include "utn2.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "PosArancelaria.h"
#include "Maritimo.h"
#include "Aereo.h"

int parser_articleFromText(FILE* pFile , Dictionary* pDictionaryArticulo)
{
	int retorno = -1;
	char codigoAux[50];
	char nombreAux[50];
	char paisDeFabricacionAux[50];
	char valorFob[50];
	char pesosEnKg[50];
	char alto[50];
	char ancho[50];
	char profundidad[50];
	char nomenclatura[50];
	Articulo* auxArticulo;
	int flagFirst = 0;
	int conteo=0;

	if(pFile != NULL && pDictionaryArticulo != NULL)
	{
		do
		{
			{
				if(	fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",codigoAux,nombreAux,paisDeFabricacionAux,
					valorFob,pesosEnKg,alto,ancho,profundidad,nomenclatura)==9)
				{
					if(flagFirst == 1)
					{
						auxArticulo = art_newParametrosTxt(nombreAux, codigoAux, paisDeFabricacionAux,
								valorFob, pesosEnKg, ancho, alto, profundidad, nomenclatura);
						if(auxArticulo != NULL)
						{
							dict_insert(pDictionaryArticulo, codigoAux, auxArticulo);
							conteo++;
						}
					}
					flagFirst = 1;
				}
			}

		}while(!feof(pFile));
		printf("Se cargaron %d articulos.\n",conteo);
		retorno = 0;
	}
    return retorno;
}

int parser_posArancelariaFromText(FILE* pFile , Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	char nomenclatura[50];
	char porcentajeSeguro[50];
	char porcentajeImportacion[50];
	char porcentajeTasaEst[50];
	char tipoLicencia[50];
	PosArancelaria* auxPosAr;
	int flagFirst = 0;
	int conteo=0;
	if(pFile != NULL && pDictionaryPosArancelaria != NULL)
	{
		do
		{
			{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",nomenclatura,porcentajeSeguro,porcentajeImportacion,
						porcentajeTasaEst,tipoLicencia)==5)
				{

					if(flagFirst == 1)
					{
						auxPosAr = posAr_newParamTxt(nomenclatura,porcentajeSeguro, porcentajeImportacion, porcentajeTasaEst, tipoLicencia);
						if(auxPosAr != NULL)
						{
							dict_insert(pDictionaryPosArancelaria, nomenclatura, auxPosAr);
							conteo++;
						}
					}
					flagFirst = 1;
				}
			}

		}while(!feof(pFile));
		printf("Se cargaron %d articulos.\n",conteo);
		retorno = 0;
	}
    return retorno;
}

int parser_maritimoFromText(FILE* pFile , LinkedList* listaMaritimo)
{
	int retorno = -1;
	char metrosCubicos[50];
	char valorContenedor[50];
	Maritimo* auxMaritimo;
	int flagFirst = 0;
	int conteo=0;

	if(pFile != NULL && listaMaritimo != NULL)
	{
		do
		{
			if(	fscanf(pFile,"%[^,],%[^\n]\n",metrosCubicos,valorContenedor)==2)
			{
				if(flagFirst == 1)
				{
					auxMaritimo = mar_newParamTxt(metrosCubicos,valorContenedor);
					if(auxMaritimo != NULL)
					{
						ll_add(listaMaritimo, auxMaritimo);
						conteo++;
					}
				}
				flagFirst = 1;
			}
		}while(!feof(pFile));
		printf("Se cargaron %d maritimos.\n",conteo);
		retorno = 0;
	}
    return retorno;
}

int parser_aereoFromText(FILE* pFile , LinkedList* listaAereo)
{
	int retorno = -1;
	char constVolumetrica[50];
	char valorPorKg[50];
	Aereo* auxAereo;
	int flagFirst = 0;
	int conteo=0;

	if(pFile != NULL && listaAereo != NULL)
	{
		do
		{
			{
				if(	fscanf(pFile,"%[^,],%[^\n]\n",constVolumetrica,valorPorKg)==2)
				{
					if(flagFirst == 1)
					{
						auxAereo = aer_newParamTxt(constVolumetrica,valorPorKg);
						if(auxAereo != NULL)
						{
							ll_add(listaAereo, auxAereo);
							conteo++;
						}
					}
					flagFirst = 1;
				}
			}

		}while(!feof(pFile));
		printf("Se cargaron %d aereos.\n",conteo);
		retorno = 0;
	}
    return retorno;
}

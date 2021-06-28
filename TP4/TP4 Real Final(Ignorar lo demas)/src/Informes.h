/*
 * Informes.h
 *
 *  Created on: 19 jun. 2021
 *      Author: Pato
 */

#ifndef INFORMES_H_
#define INFORMES_H_
#include "Informes.h"
#include "Aereo.h"
#include "Maritimo.h"

float info_getBaseImponibleAereo(Articulo* pArticulo,Aereo* pAereo, PosArancelaria* pPosArancelaria);
float info_getBaseImponibleMaritimo(Articulo* pArticulo,Maritimo* pMaritimo, PosArancelaria* pPosArancelaria);

float info_getCostoAvion(Articulo* pArticulo,Aereo* pAereo);
float info_getCostoBarco(Articulo* pArticulo,Maritimo* pMaritimo);

float info_getCostoNacionalAvion(Articulo* pArticulo,PosArancelaria* pPosArancelaria,Aereo* pAereo);
float info_getCostoNacionalBarco(Articulo* pArticulo,PosArancelaria* pPosArancelaria,Maritimo* pMaritimo);

float info_listarArticulosConCostosFinales(Dictionary* pDiccionarioArticulo,Dictionary* pDiccionarioPosArancelaria,LinkedList* listaMaritima, LinkedList* listaAerea);
int funcionCriterio(void* pArticulo,char* arg);
int funcionCriterioSort(void* pArticulo,void* pArticuloDos);
#endif /* INFORMES_H_ */

/*
 ============================================================================
 Name        : Z.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//calcular el valor promedio de la nacionalizacion aerea y maritima. Hacer un informe, que informe todos los articulos que esten
//por debajo del valor maritimo maritimo
// y en otro informe aereo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Articulo.h"
#include "utn2.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "Controller.h"
#include "Informes.h"
#include "Maritimo.h"
#include "Aereo.h"
int main(void) {

	setbuf(stdout,NULL);
	int opcion;
	Dictionary* pDictionaryArticulo = dict_new(0);
	Dictionary* pDictionaryPosArancelaria = dict_new(0);
	LinkedList* listaMaritima = ll_newLinkedList();
	LinkedList* listaAerea = ll_newLinkedList();

	controller_loadArticuloFromText("articulo.csv", pDictionaryArticulo);
	controller_loadPosArancelariaFromText("posicion.csv", pDictionaryPosArancelaria);
	controller_loadMaritimoFromText("TransporteMaritimo.csv", listaMaritima);
	controller_loadAereoFromText("TransporteAereo.csv", listaAerea);

	do
		{
			utn_getNumero(&opcion, 	"1)Listar articulos con precios finales.\n"
									"2)Listar articulos sin precios finales.\n"
									"3)Modificar articulo de la lista.\n"
									"4)Agregar articulo a la lista.\n"
									"5)Eliminar articulo de la lista.\n"
									"6)Listar posiciones arancelarias.\n"
									"7)Modificar posicion arancelaria.\n"
									"8)Agregar posicion arancelaria.\n"
									"9)Eliminar posicion arancelaria.\n"
									"10)Modificar transporte por barco.\n"
									"11)Modificar transporte por avion.\n"
									"12)Mostrar Maritimo.\n"
									"13)Mostrar Aereo.\n"
									"14)Por Debajo del promedio aereo.\n"
									"15)Por debajo del promedio maritimo\n", "Opcion incorrecta.\n", 1, 16, 3);

			switch (opcion)
			{
				case 1:
					info_listarArticulosConCostosFinales(pDictionaryArticulo, pDictionaryPosArancelaria, listaMaritima, listaAerea);
					break;
				case 2:
					controller_ListarArticulo(pDictionaryArticulo);
					break;
				case 3:
					controller_ListarArticulo(pDictionaryArticulo);
					controller_editArticulo(pDictionaryArticulo);
					controller_saveArticleAsText("articulo.csv", pDictionaryArticulo);
					break;
				case 4:
					controller_addArticulo(pDictionaryArticulo,pDictionaryPosArancelaria);
					controller_saveArticleAsText("articulo.csv", pDictionaryArticulo);
					break;
				case 5:
					controller_ListarArticulo(pDictionaryArticulo);
					controller_removeArticulo(pDictionaryArticulo);
					controller_saveArticleAsText("articulo.csv", pDictionaryArticulo);
					break;
				case 6:
					controller_ListarPosArancelaria(pDictionaryPosArancelaria);
					break;
				case 7:
					controller_ListarPosArancelaria(pDictionaryPosArancelaria);
					controller_editPosArancelaria(pDictionaryPosArancelaria);
					controller_savePosArancelariaAsText("posicion.csv",pDictionaryPosArancelaria);
					break;
				case 8:
					controller_addPosArancelaria(pDictionaryPosArancelaria);
					break;
				case 9:
					controller_ListarPosArancelaria(pDictionaryPosArancelaria);
					controller_removePosArancelaria(pDictionaryPosArancelaria,pDictionaryArticulo);
					controller_savePosArancelariaAsText("posicion.csv",pDictionaryPosArancelaria);
					break;
				case 10:
					controller_loadMaritimoFromText("TransporteMaritimo.csv", listaMaritima);
					if(controller_editMaritimo(listaMaritima)==0)
					controller_saveMaritimoAsText("TransporteMaritimo.csv", listaMaritima);
					break;
				case 11:
					controller_loadAereoFromText("TransporteAereo.csv", listaAerea);
					if(controller_editAereo(listaAerea)==0)
					controller_saveAereoAsText("TransporteAereo.csv", listaAerea);
					break;
				case 12:
					controller_ListarMaritimo(listaMaritima);
					break;
				case 13:
					controller_ListarAereo(listaAerea);
					break;
				case 14:
					controller_loQuePidioMauricioAereo(pDictionaryArticulo);
					break;
				case 15:
					controller_loQuePidioMauricioMaritimo(pDictionaryArticulo);
					break;
				case 16:
					printf("Saliste del programa.\n");
					break;

			}
		}
		while(opcion!=16);

	/*
	 * do
	{
		utn_getNumero(&opcion, "Ingrese una opcion:\n1] Prueba load.\n2]Prueba add.\n3]Prueba Modificar.\n4]Prueba Eliminar.\n5]Prueba listar.\n"
				"6]Prueba load posArancelaria\n7]Prueba cargar posARancelaria\n8]Prueba modificar posArancelaria\n9]Prueba eliminar posARancelaria\n10]Prueba imprimir posARAncelaria\n11]Prueba Save posARancelaria\n", "Opcion Invalida.\n", 1, 11, 3);

		switch (opcion)
		{
			case 1:
				controller_loadArticuloFromText("ArchivoPrueba.csv", pDictionaryArticulo);
				art_setearValorInicialDeId(pDictionaryArticulo);
				break;
			case 2:
				controller_addArticulo(pDictionaryArticulo);
				break;
			case 3:
				controller_editArticulo(pDictionaryArticulo);
				break;
			case 4:
				controller_removeArticulo(pDictionaryArticulo);
				break;
			case 5:
				controller_ListarArticulo(pDictionaryArticulo);
				break;
			case 6:
				controller_loadPosArancelariaFromText("ArchivoPosArancelPrueba.csv",pDictionaryPosArancelaria);
				posAr_setearValorInicialDeId(pDictionaryPosArancelaria);
				break;
			case 7:
				controller_addPosArancelaria(pDictionaryPosArancelaria);
				break;
			case 8:
				controller_editPosArancelaria(pDictionaryPosArancelaria);
				break;
			case 9:
				controller_removePosArancelaria(pDictionaryPosArancelaria);
				break;
			case 10:
				controller_ListarPosArancelaria(pDictionaryPosArancelaria);
				break;
			case 11:
				controller_savePosArancelariaAsText("ArchivoPosArancelPrueba.csv",pDictionaryPosArancelaria);
				break;
		}

	}
	while(opcion!=12);*/

	return EXIT_SUCCESS;
}

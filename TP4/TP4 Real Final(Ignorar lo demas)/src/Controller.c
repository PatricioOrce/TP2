/*
 * Controller.c
 *
 *  Created on: 16 jun. 2021
 *      Author: Pato
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn2.h"
#include "LinkedList.h"
#include "Parser.h"
#include "Articulo.h"
#include "Controller.h"
#include "Dictionary.h"
#include "Aereo.h"
#include "Maritimo.h"
#include "Informes.h"

int controller_loadArticuloFromText(char* path , Dictionary* pDictionary)
{

	if(path!=NULL && pDictionary!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_articleFromText(pFile, pDictionary);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_loadPosArancelariaFromText(char* path , Dictionary* pDictionary)
{

	if(path!=NULL && pDictionary!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_posArancelariaFromText(pFile, pDictionary);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_loadMaritimoFromText(char* path , LinkedList* pListaMaritimo)
{
	if(path!=NULL && pListaMaritimo!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_maritimoFromText(pFile, pListaMaritimo);
			fclose(pFile);
		}
	}
	return 0;
}

int controller_loadAereoFromText(char* path , LinkedList* pListaAereo)
{

	if(path!=NULL && pListaAereo!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_aereoFromText(pFile, pListaAereo);
			fclose(pFile);
		}
	}
	return 0;
}
/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_addArticulo(Dictionary* pDictionaryArt,Dictionary* pDictionaryPosAr)
{
	int retorno = -1;
	char auxNombre[64];
	char codigo[64];
	char paisDeFabricacion[64];
	float valorFob;
	float pesosEnKg;
	float alto;
	float ancho;
	float profundidad;
	char posArancel[64];
	int reintentos = 3;
	Articulo* auxArticulo;
	if(pDictionaryArt!=NULL && pDictionaryPosAr)
	{

		if(utn_getString(codigo, sizeof(codigo), "Ingrese un codigo(Alfanumerico):\n", "Error Codigo incorrecto.\n", 3)==0)
		{
			if(canUseThisAlphCodeArt(pDictionaryArt, codigo)!=0)
			{
				if(	utn_getName(auxNombre, sizeof(auxNombre), "Ingrese nombre:\n", "Nombre Incorrecto.\n", 3)==0 &&
					utn_getString(paisDeFabricacion, sizeof(paisDeFabricacion), "Ingrese pais de fabricacion:\n", "Error pais incorrecto.\n", 3)==0 &&
					utn_getNumeroFloat(&valorFob, "Ingrese valor FOB.\n", "Valor FOB incorrecto.\n", 1, 999999, 3)==0 &&
					utn_getNumeroFloat(&pesosEnKg, "Ingrese peso del articulo(KG).\n", "Peso invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&alto, "Medidas(Al*An*Pr):\nIngrese alto del articulo(cm).\n", "Alto invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&ancho, "Ingrese ancho del articulo(cm).\n", "Ancho invalido.\n", 0.1, 999999, 3)==0 &&
					utn_getNumeroFloat(&profundidad, "Ingrese profundidad del articulo(cm).\n", "Profundidad invalida.\n", 0.1, 999999, 3)==0)
				{
					controller_ListarPosArancelaria(pDictionaryPosAr);
					do
					{
						if(utn_getString(posArancel, sizeof(posArancel), "Ingrese una posicion arancelaria por su nomenclatura.\n", "Error nomenclatura invalida.\n", 3)==0)
						{
							if(canUseThisAlphCodePosAr(pDictionaryPosAr, posArancel)==0)
							{
								auxArticulo = art_newParametros(auxNombre,codigo,paisDeFabricacion,valorFob,pesosEnKg,ancho,alto,profundidad,posArancel);
								if(auxArticulo!=NULL)
								{
									dict_insert(pDictionaryArt,codigo,auxArticulo);
									retorno=0;
								}
							}
							else
							{
								printf("Esa posicion arancelaria no existe.\n");
							}
						}
						reintentos--;
					}
					while(reintentos!=0);
				}
			}
			else
			{
				printf("Este codigo ya pertenece a un producto.\n");
			}
		}

	}
	return retorno;
}

/** \brief Modificar datos de un articulo
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editArticulo(Dictionary* pDictionaryArticulo)
{
	int retorno = 0;
	char auxNombre[64];
	char paisDeFabricacion[64];
	char cadenaAModificar[64];
	float valorFob;
	float peso;
	float alto;
	float ancho;
	float profundidad;
	char posArancel[64];
	int opcion;
	Articulo* auxArticulo;

	if(pDictionaryArticulo!=NULL)
	{
		if(utn_getString(cadenaAModificar, sizeof(cadenaAModificar), "Ingrese codigo del producto a modificar.\n", "Error Codigo invalido", 3)==0)
		{
			if(canUseThisAlphCodeArt(pDictionaryArticulo, cadenaAModificar)==0)
			{
				auxArticulo = dict_get(pDictionaryArticulo, cadenaAModificar);
				if(auxArticulo!=NULL)
				{
					if(utn_getNumero(&opcion, "Que desea modificar?\n1)Nombre.\n2)Pais de fabricacion.\n3)Valor FOB.\n"
							"4)Peso(KG).\n5)Alto.\n6)Ancho.\n7)Profundidad.\n8)PosArancelaria.\n", "[Error]Incorrecto.\n", 1, 8, 3)==0)
					{
						switch (opcion) {
							case 1:
								if(utn_getName(auxNombre, sizeof(auxNombre), "Ingrese nuevo nombre.\n", "[ERROR]Nombre Invalido.\n", 3)==0)
								{
									art_setNombre(auxArticulo, auxNombre);
								}
								break;
							case 2:
								if(utn_getString(paisDeFabricacion, sizeof(paisDeFabricacion), "Ingrese nuevo pais de fabricacion:\n", "Error pais incorrecto.\n", 3)==0)
								{
									art_setPaisDeFabricacion(auxArticulo, paisDeFabricacion);
								}
								break;
							case 3:
								if(utn_getNumeroFloat(&valorFob, "Ingrese nuevo valor FOB.\n", "Valor FOB incorrecto.\n", 1, 999999, 3)==0)
								{
									art_setValorFOB(auxArticulo, valorFob);
								}
								break;
							case 4:
								if(utn_getNumeroFloat(&peso, "Ingrese peso del articulo(KG).\n", "Peso invalido.\n", 0.1, 999999, 3)==0)
								{
									art_setPesosEnKg(auxArticulo, peso);
								}
								break;
							case 5:
								if(utn_getNumeroFloat(&alto, "Ingrese nuevo alto del articulo(cm).\n", "Alto invalido.\n", 0.1, 999999, 3)==0)
								{
									art_setAlto(auxArticulo, alto);
								}
								break;
							case 6:
								if(utn_getNumeroFloat(&ancho, "Ingrese nuevo ancho del articulo(cm).\n", "Ancho invalido.\n", 0.1, 999999, 3)==0)
								{
									art_setAncho(auxArticulo, ancho);
								}
								break;
							case 7:
								if(utn_getNumeroFloat(&profundidad, "Ingrese nueva profundiad del articulo(cm).\n", "Profunidad invalida.\n", 0.1, 999999, 3)==0)
								{
									art_setProfundidad(auxArticulo, profundidad);
								}
								break;
							case 8:
								if(utn_getString(posArancel, sizeof(posArancel), "Ingrese nueva posicion arancelaria.\n", "Error posicion arancelaria invalida.\n", 3)==0)
								{
									art_setIdPosicionArancelaria(auxArticulo, posArancel);
								}
								break;
						}
					}
				}
			}
			else
			{
				printf("El codigo ingresado no representa ningun articulo de la lista.\n");
			}
		}
	}

	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeArticulo(Dictionary* pDictionaryArticulo)
{
	int retorno=-1;
	char cadenaAEliminar[64];
	Articulo* auxArticulo;

	if(pDictionaryArticulo!=NULL)
	{
		controller_ListarArticulo(pDictionaryArticulo);
		if(utn_getString(cadenaAEliminar, sizeof(cadenaAEliminar), "Ingrese codigo del articulo a eliminar.\n", "Codigo invalido.\n", 3)==0)
			{
			if(canUseThisAlphCodeArt(pDictionaryArticulo, cadenaAEliminar)==0)
			{
				auxArticulo = (Articulo*) dict_get(pDictionaryArticulo, cadenaAEliminar);
				if(auxArticulo != NULL)
				{
					if(art_delete(auxArticulo)==0 && dict_remove(pDictionaryArticulo,cadenaAEliminar)==0)
					{
						printf("Articulo eliminado con exito.\n");
					}
				}
			}
			else
			{
				printf("El codigo no representa ningun articulo de la lista.\n");
			}
		}
	}
	return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListarArticulo(Dictionary* pDictionaryArticulo)
{
	int retorno = -1;
	int size;
	int flagError;
	char nombre[50];
	char pais[50];
	char codigo[50];
	float valorFob,alto,ancho,profundidad,pesosEnKg;

	Articulo* auxArticulo;
	LinkedList* listaAux;
	listaAux = dict_getValues(pDictionaryArticulo);
	size = ll_len(listaAux);
	if(pDictionaryArticulo != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxArticulo = (Articulo*)ll_get(listaAux, i);
			strncpy(nombre,art_getNombre(auxArticulo, &flagError),sizeof(nombre));
			strncpy(codigo,art_getCodigo(auxArticulo, &flagError),sizeof(nombre));
			strncpy(pais,art_getPaisDeFabricacion(auxArticulo, &flagError),sizeof(nombre));
			valorFob = art_getValorFOB(auxArticulo, &flagError);
			alto = art_getAlto(auxArticulo, &flagError);
			ancho = art_getAncho(auxArticulo, &flagError);
			profundidad = art_getProfundidad(auxArticulo, &flagError);
			pesosEnKg = art_getPesosEnKg(auxArticulo, &flagError);
			printf("Nombre: [%s]\tCodigo: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",nombre,codigo,
					pais,valorFob,pesosEnKg,alto,ancho,profundidad);
		}
		retorno = 0;
	}
	ll_deleteLinkedList(listaAux);
    return retorno;
}


int controller_saveArticleAsText(char* path , Dictionary* diccionarioArticulos)
{
   int retorno = -1;
   Articulo* auxArticulo;
   LinkedList* listaAux;
   FILE* pFile;
   int flagError;
   int longitud;

   if(path!=NULL && diccionarioArticulos!=NULL)
   {
	   listaAux = dict_getValues(diccionarioArticulos);
	   longitud = ll_len(listaAux);
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"CODIGO,ITEM,ORIGEN,FOB,KG,ALTO,ANCHO,PROFUNDO,NCM\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxArticulo = ll_get(listaAux, i);
			   if(auxArticulo!=NULL)
			   {
					fprintf(pFile,"%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n",
					art_getCodigo(auxArticulo, &flagError),art_getNombre(auxArticulo, &flagError),
					art_getPaisDeFabricacion(auxArticulo, &flagError),art_getValorFOB(auxArticulo, &flagError),
					art_getPesosEnKg(auxArticulo, &flagError),art_getAlto(auxArticulo, &flagError),
					art_getAncho(auxArticulo, &flagError),art_getProfundidad(auxArticulo, &flagError),
					art_getIdPosicionArancelaria(auxArticulo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }
	ll_deleteLinkedList(listaAux);
   return retorno;
}

int controller_savePosArancelariaAsText(char* path , Dictionary* diccionarioPosArancelaria)
{
   int retorno = -1;
   PosArancelaria* auxPosArancelaria;
   LinkedList* listaAux;
   FILE* pFile;
   int flagError;
   int longitud;

   listaAux = dict_getValues(diccionarioPosArancelaria);
   longitud = ll_len(listaAux);
   if(path!=NULL && diccionarioPosArancelaria!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"NCM,SEGURO,DERECHO,TASA,TIPO_LICENCIA\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxPosArancelaria = (PosArancelaria*)ll_get(listaAux, i);
			   if(auxPosArancelaria!=NULL)
			   {
					fprintf(pFile,"%s,%.2f,%.2f,%.2f,%s\n",	posAr_getNomenclador(auxPosArancelaria, &flagError),
																posAr_getSeguro(auxPosArancelaria, &flagError),
																posAr_getPorcDeImportacion(auxPosArancelaria, &flagError),
																posAr_getTasaEstadistica(auxPosArancelaria, &flagError),
																posAr_getTipoDeLicencia(auxPosArancelaria, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }
	ll_deleteLinkedList(listaAux);
   return retorno;
}

int controller_addPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	char auxNomenclatura[64];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	char tipoDeLicencia[64];
	PosArancelaria* auxPosArancelaria;

	if(pDictionaryPosArancelaria!=NULL)
	{
		if(utn_getString(auxNomenclatura, sizeof(auxNomenclatura), "Ingrese la nomenclatura:\n", "Error Nomenclatura invaluda.\n", 3)==0)
		{
			if(canUseThisAlphCodePosAr(pDictionaryPosArancelaria, auxNomenclatura)!=0)
			{

				if(	utn_getNumeroFloat(&porcentajeSeguro, "Ingrese el porcentaje del seguro:\n", "Porcentaje invalido.\n", 0,100, 3)==0 &&
					utn_getNumeroFloat(&porcentajeImportacion, "Ingrese el porcentaje de importacion:\n", "Porcentaje invalido.\n", 0,100, 3)==0 &&
					utn_getNumeroFloat(&porcentajeTasaEst, "Ingrese el porcentaje de la tasa de estadistica:\n", "Porcentaje invaludo.\n", 0,100, 3)==0 &&
					utn_getString(tipoDeLicencia, sizeof(tipoDeLicencia), "Ingrese el tipo de licencia (1)AUTOMATICO - (2)NO AUTOMATICO :\n","Error tipo de licencia incorrecta.\n", 3)==0)
				{
					auxPosArancelaria = posAr_newParam(auxNomenclatura, porcentajeSeguro, porcentajeImportacion, porcentajeTasaEst, tipoDeLicencia);
					if(auxPosArancelaria!=NULL)
					{
						dict_insert(pDictionaryPosArancelaria,auxNomenclatura,auxPosArancelaria);
						retorno=0;
					}
				}
			}
			else
			{
				printf("La nomenclatura ingresada ya existe.\n");
			}
		}

	}
	return retorno;
}

int controller_editPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	char auxNomenclatura[64];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEst;
	char tipoDeLicencia[64];
	char cadenaAModificar[64];
	int desicion;
	int opcion;
	PosArancelaria* auxPosArancelaria;

	if(pDictionaryPosArancelaria!=NULL)
	{
		if(utn_getNumero(&desicion, "Ingrese ID de posicion arancelaria a modificar.\n", "Error ID Incorrecto.\n", 0, 99999, 3)==0)
		{
			snprintf(cadenaAModificar,sizeof(cadenaAModificar),"%d",desicion);
			auxPosArancelaria = dict_get(pDictionaryPosArancelaria,cadenaAModificar);
			if(auxPosArancelaria!=NULL)
			{
				if(utn_getNumero(&opcion, "Que desea modificar?\n1)Nomenclatura.\n2)Porcentaje de seguro.\n3)Porcentaje de importacion.\n4)Porcentaje de tasa de estadistica.\n"
						"5)Tipo de licencia.\n","[Error]Incorrecto.\n", 1, 5, 3)==0)
				{
					switch (opcion) {
						case 1:
							if(utn_getString(auxNomenclatura, sizeof(auxNomenclatura), "Ingrese la nomenclatura:\n", "Error Nomenclatura invaluda.\n", 3)==0)
							{
								posAr_setNomenclador(auxPosArancelaria, auxNomenclatura);
							}
							break;
						case 2:
							if(utn_getNumeroFloat(&porcentajeSeguro, "Ingrese el porcentaje del seguro:\n", "Porcentaje invalido.\n", 0,100, 3)==0)
							{
								posAr_setSeguro(auxPosArancelaria, porcentajeSeguro);
							}
							break;
						case 3:
							if(utn_getNumeroFloat(&porcentajeImportacion, "Ingrese el porcentaje de importacion:\n", "Porcentaje invalido.\n", 0,100, 3)==0)
							{
								posAr_setPorcDeImportacion(auxPosArancelaria, porcentajeImportacion);
							}
							break;
						case 4:
							if(utn_getNumeroFloat(&porcentajeTasaEst, "Ingrese el porcentaje de la tasa de estadistica:\n", "Porcentaje invaludo.\n", 0,100, 3)==0)
							{
								posAr_setTasaEstadistica(auxPosArancelaria, porcentajeTasaEst);
							}
							break;
						case 5:
							if(utn_getString(tipoDeLicencia, sizeof(tipoDeLicencia), "Ingrese el tipo de licencia (1)AUTOMATICO - (2)NO AUTOMATICO :\n","Error tipo de licencia incorrecta.\n", 3)==0)
							{
								posAr_setTipoDeLicencia(auxPosArancelaria, tipoDeLicencia);
							}
							break;
					}
				}
			}
		}
	}

	return retorno;
}

int controller_removePosArancelaria(Dictionary* pDictionaryPosArancelaria,Dictionary* pDiccionaryArticulo)
{
	int retorno=-1;
	char deleteOption[64];
	int sizeArticulos;
	int cantidadDeArticulosConPosArancel = 0;
	int flagError = -1;
	int yesOrNo;
	PosArancelaria* auxPosArancelaria;
	LinkedList* listaAux;
	Articulo* articuloAux;

	if(pDictionaryPosArancelaria!=NULL)
	{
		listaAux = dict_getValues(pDiccionaryArticulo);
		sizeArticulos = ll_len(listaAux);
		if(utn_getString(deleteOption, sizeof(deleteOption), "Ingrese codigo de posicion arancelaria a eliminar.\n", "Codigo invalido.\n", 3)==0)
		{
			if(canUseThisAlphCodePosAr(pDictionaryPosArancelaria, deleteOption)==0)
			{
				auxPosArancelaria = (PosArancelaria*) dict_get(pDictionaryPosArancelaria, deleteOption);
				if(auxPosArancelaria != NULL)
				{
					for(int i=0;i<sizeArticulos;i++)
					{
						articuloAux = ll_get(listaAux, i);
						if(strcmp(art_getIdPosicionArancelaria(articuloAux, &flagError),deleteOption)==0)
						{
							cantidadDeArticulosConPosArancel++;
						}
					}
					if(cantidadDeArticulosConPosArancel>0)
					{
						printf("No es posible eliminar esta posicion arancelaria ya que hay (%d) articulos utilizandola.\n",cantidadDeArticulosConPosArancel);
						if(utn_getNumero(&yesOrNo, "Desea saber cuales?(1-Si/2-No)\n", "Opcion invalida.\n", 1, 2, 3)==0)
						{
							if(yesOrNo == 1)
							{
								ll_MyFilter(listaAux, funcionCriterio, deleteOption);
								controller_ListarArticulos(listaAux);
							}
						}
					}
					else
					{
						if(posAr_delete(auxPosArancelaria)==0 && dict_remove(pDictionaryPosArancelaria,deleteOption)==0)
						{
							printf("Posicion Arancelaria eliminada con exito.\n");
						}
					}

				}
			}
			else
			{
				printf("El codigo ingresado no representa ninguna posicion arancelaria de la lista.\n");
			}
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}


int controller_ListarPosArancelaria(Dictionary* pDictionaryPosArancelaria)
{
	int retorno = -1;
	int size;
	int flagError;
	PosArancelaria* auxPosArancelaria;
	LinkedList* listaAux;
	listaAux = dict_getValues(pDictionaryPosArancelaria);
	size = ll_len(listaAux);
	if(pDictionaryPosArancelaria != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxPosArancelaria = (PosArancelaria*)ll_get(listaAux, i);

			printf("Nomenclador:[%s]\tSeguro:[%.2f]\tPorcentajeDeImportacion:[%.2f]\tTasaEstadistica:[%.2f]\t,TipoDeLicencia[%s]\n",
					posAr_getNomenclador(auxPosArancelaria, &flagError),
					posAr_getSeguro(auxPosArancelaria, &flagError),posAr_getPorcDeImportacion(auxPosArancelaria, &flagError),
					posAr_getTasaEstadistica(auxPosArancelaria, &flagError), posAr_getTipoDeLicencia(auxPosArancelaria, &flagError));
		}
		retorno = 0;
	}
	ll_deleteLinkedList(listaAux);
    return retorno;
}

int controller_editMaritimo(LinkedList* pListaMaritimo)
{
	int retorno = -1;
	float metrosCubicos;
	float valorContenedor;
	int posicion = 0;
	int opcion;
	Maritimo* auxMaritimo;

	if(pListaMaritimo!=NULL)
	{
		auxMaritimo = (Maritimo*)ll_get(pListaMaritimo,posicion);
		if(auxMaritimo!=NULL)
		{
			if(utn_getNumero(&opcion, "Que desea modificar?\n1)Metros cubicos.\n2)Valor del contenedor.\n","[Error]Incorrecto.\n", 1, 2, 3)==0)
			{
				switch (opcion) {
					case 1:
						if(utn_getNumeroFloat(&metrosCubicos, "Ingrese nuevos metros cubicos.\n", "Error longitud invalida.\n", 0, 99999, 3)==0)
						{
							mar_setMtsCubicos(auxMaritimo, metrosCubicos);
							retorno = 0;;
						}
						break;
					case 2:
						if(utn_getNumeroFloat(&valorContenedor, "Ingrese el nuevo valor del contenedor:\n", "Valor invalido.\n", 1,99999, 3)==0)
						{
							mar_setPrecio(auxMaritimo, valorContenedor);
							retorno = 0;
						}
						break;
					default:
						break;
				}
			}
		}
	}

	return retorno;
}

int controller_saveMaritimoAsText(char* path , LinkedList* listaMaritimo)
{
   int retorno = -1;
   Maritimo* auxMaritimo;
   FILE* pFile;
   int flagError;
   int longitud;

   longitud = ll_len(listaMaritimo);
   if(path!=NULL && listaMaritimo!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"MetrosCubicos,PrecioContenedor\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxMaritimo = (Maritimo*)ll_get(listaMaritimo, i);
			   if(auxMaritimo!=NULL)
			   {
					fprintf(pFile,"%.2f,%.2f\n",mar_getMtsCubicos(auxMaritimo, &flagError),mar_getPrecio(auxMaritimo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
}

int controller_editAereo(LinkedList* pListaAereo)
{
	int retorno = -1;
	float constVolumetrica;
	float valorPorKg;
	int posicion = 0;
	int opcion;
	Aereo* auxAereo;

	if(pListaAereo!=NULL)
	{
		auxAereo = (Aereo*)ll_get(pListaAereo,posicion);
		if(auxAereo!=NULL)
		{
			if(utn_getNumero(&opcion, "Que desea modificar?\n1)Constante volumetrica.\n2)Valor por KG.\n","[Error]Incorrecto.\n", 1, 2, 3)==0)
			{
				switch (opcion) {
					case 1:
						if(utn_getNumeroFloat(&constVolumetrica, "Ingrese nueva constante volumetrica.\n", "Error constante volumetrica invalida.\n", 1, 99999, 3)==0)
						{
							aer_setConstVolum(auxAereo, constVolumetrica);
							retorno = 0;
						}
						break;
					case 2:
						if(utn_getNumeroFloat(&valorPorKg, "Ingrese el nuevo valor por KG:\n", "Valor invalido.\n", 1,99999, 3)==0)
						{
							aer_setPrecio(auxAereo, valorPorKg);
							retorno = 0;
						}
						break;
					default:
						break;

				}
			}
		}
	}
	return retorno;
}

int controller_saveAereoAsText(char* path , LinkedList* listaAereo)
{
   int retorno = -1;
   Aereo* auxAereo;
   FILE* pFile;
   int flagError;
   int longitud;

   longitud = ll_len(listaAereo);
   if(path!=NULL && listaAereo!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"ConstanteVolumetrica,ValorPorKG\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxAereo = (Aereo*)ll_get(listaAereo, i);
			   if(auxAereo!=NULL)
			   {
					fprintf(pFile,"%.2f,%.2f\n",aer_getConstVolum(auxAereo, &flagError),aer_getPrecio(auxAereo, &flagError));
					retorno = 0;
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
}

int controller_ListarMaritimo(LinkedList* pListaMaritimo)
{
	int retorno = -1;
	int size;
	int flagError;
	Maritimo* auxMaritimo;
	size = ll_len(pListaMaritimo);
	if(pListaMaritimo != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxMaritimo = (Maritimo*)ll_get(pListaMaritimo, i);

			printf("Metros Cubicos: [%.2f]\t Valor del contenedor: [%.2f]\n",
			mar_getMtsCubicos(auxMaritimo, &flagError),mar_getPrecio(auxMaritimo, &flagError));
		}
		retorno = 0;
	}
    return retorno;
}

int controller_ListarAereo(LinkedList* listaAereo)
{
	int retorno = -1;
	int size;
	int flagError;
	Aereo* auxAereo;

	size = ll_len(listaAereo);
	if(listaAereo != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxAereo = (Aereo*)ll_get(listaAereo, i);

			printf("Constante Volumetrica:[%.2f]\tPrecio:[%.2f]\n",
					aer_getConstVolum(auxAereo, &flagError),aer_getPrecio(auxAereo, &flagError));
		}
		retorno = 0;
	}
    return retorno;
}

int controller_ListarArticulos(LinkedList* pLista)
{
	int retorno = -1;
	int size;
	int flagError;
	char nombre[50];
	char pais[50];
	char codigo[50];
	float valorFob,alto,ancho,profundidad,pesosEnKg;
	Articulo* auxArticulo;
	size = ll_len(pLista);
	if(pLista != NULL)
	{
		for(int i=0;i<size;i++)
		{
			auxArticulo = (Articulo*)ll_get(pLista, i);
			strncpy(nombre,art_getNombre(auxArticulo, &flagError),sizeof(nombre));
			strncpy(codigo,art_getCodigo(auxArticulo, &flagError),sizeof(nombre));
			strncpy(pais,art_getNombre(auxArticulo, &flagError),sizeof(nombre));
			valorFob = art_getValorFOB(auxArticulo, &flagError);
			alto = art_getAlto(auxArticulo, &flagError);
			ancho = art_getAncho(auxArticulo, &flagError);
			profundidad = art_getProfundidad(auxArticulo, &flagError);
			pesosEnKg = art_getPesosEnKg(auxArticulo, &flagError);
			printf("Nombre: [%s]\tCodigo: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",nombre,codigo
					,pais,valorFob,pesosEnKg,alto,ancho,profundidad);
		}
		retorno = 0;
	}
    return retorno;
}

int controller_loQuePidioMauricioMaritimo(Dictionary* pDictionary)
{
	int retorno = -1;
	LinkedList* listaAux;
	int size;
	Articulo* auxArt;
	int flagError = -1;
	float acumMaritimo = 0;
	int cantidadMarit=0;
	float promediomaritimo;
	if(pDictionary!=NULL)
	{
		listaAux = dict_getValues(pDictionary);
		size= ll_len(listaAux);
		for(int i = 0; i<size;i++)
		{
			cantidadMarit++;
			auxArt = ll_get(listaAux, i);
			acumMaritimo = acumMaritimo+art_getValorFinalMaritimo(auxArt, &flagError);
		}
		promediomaritimo=acumMaritimo/cantidadMarit;
		retorno = 0;


		for(int i=0;i<size;i++)
		{
			auxArt = ll_get(listaAux, i);
			if(art_getValorFinalMaritimo(auxArt, &flagError)<promediomaritimo)
			{
				printf("Nombre: [%s]\tCodigo: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",
				art_getNombre(auxArt, &flagError),art_getCodigo(auxArt, &flagError),art_getPaisDeFabricacion(auxArt, &flagError),
				art_getValorFOB(auxArt, &flagError),art_getPesosEnKg(auxArt, &flagError),art_getAlto(auxArt, &flagError),
				art_getAncho(auxArt, &flagError),art_getProfundidad(auxArt, &flagError));
			}
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}

int controller_loQuePidioMauricioAereo(Dictionary* pDictionary)
{
	int retorno = -1;
	LinkedList* listaAux;
	int size;
	Articulo* auxArt;
	int flagError = -1;
	float acumAereo =0;
	int cantidadAer=0;
	float promedioaereo;
	if(pDictionary!=NULL)
	{
		listaAux = dict_getValues(pDictionary);
		size= ll_len(listaAux);
		for(int i = 0; i<size;i++)
		{

			cantidadAer++;
			auxArt = ll_get(listaAux, i);
			acumAereo = acumAereo+art_getValorFinalAereo(auxArt, &flagError);

		}
		promedioaereo = acumAereo/cantidadAer;
		retorno = 0;

		for(int i=0;i<size;i++)
		{
			auxArt = ll_get(listaAux, i);
			if(art_getValorFinalAereo(auxArt, &flagError)<promedioaereo)
			{
				printf("Nombre: [%s]\tCodigo: [%s]\tHecho en: [%s]\tFOB: [%.2f]\tPeso(KG): [%.2f]\tDimensiones(Al*An*Pr): [%.2f*%.2f*%.2f]\n",
				art_getNombre(auxArt, &flagError),art_getCodigo(auxArt, &flagError),art_getPaisDeFabricacion(auxArt, &flagError),
				art_getValorFOB(auxArt, &flagError),art_getPesosEnKg(auxArt, &flagError),art_getAlto(auxArt, &flagError),
				art_getAncho(auxArt, &flagError),art_getProfundidad(auxArt, &flagError));
			}
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}
//calcular el valor promedio de la nacionalizacion aerea y maritima. Hacer un informe, que informe todos los articulos que esten
//por debajo del valor maritimo maritimo
// y en otro informe aereo.




//Complicaciones para usar map: La funcion criterio no puede recibir el valor promedio como para mapear
int calcularPromedioMaritimo(Dictionary* pDictionary)
{
	LinkedList* listaAux;
	int size;
	int cantidadAer = 0;
	int acumAereo = 0;
	Articulo* auxArt;
	int flagError=-1;
	float promedioaereo;
	if(pDictionary!=NULL)
	{
		listaAux = dict_getValues(pDictionary);
		size = ll_len(listaAux);
		for(int i = 0; i<size;i++)
		{

			cantidadAer++;
			auxArt = ll_get(listaAux, i);
			acumAereo = acumAereo+art_getValorFinalAereo(auxArt, &flagError);

		}
		promedioaereo = acumAereo/cantidadAer;
	}

	return promedioaereo;
}






int canUseThisAlphCodeArt(Dictionary* pDictionaryArt, char* arg)
{
	int retorno = -1;
	int flagError=-1;
	LinkedList* listaAux;
	int size;
	char* codigoAux;
	Articulo* artAux;
	listaAux = dict_getValues(pDictionaryArt);
	size = ll_len(listaAux);
	for(int i=0;i<size;i++)
	{
		artAux = ll_get(listaAux, i);
		codigoAux = art_getCodigo(artAux, &flagError);
		if(strcmp(codigoAux,arg)==0)
		{
			retorno = 0;
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}

int canUseThisAlphCodePosAr(Dictionary* pDictionaryArt, char* arg)
{
	int retorno = -1;
	int flagError=-1;
	LinkedList* listaAux;
	int size;
	char* codigoAux;
	PosArancelaria* posArAux;
	listaAux = dict_getValues(pDictionaryArt);
	size = ll_len(listaAux);
	for(int i=0;i<size;i++)
	{
		posArAux = ll_get(listaAux, i);
		codigoAux = posAr_getNomenclador(posArAux, &flagError);
		if(strcmp(codigoAux,arg)==0)
		{
			retorno = 0;
		}
	}
	ll_deleteLinkedList(listaAux);
	return retorno;
}

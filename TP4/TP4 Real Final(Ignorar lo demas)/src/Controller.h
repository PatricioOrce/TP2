/*
 * Controller.h
 *
 *  Created on: 16 jun. 2021
 *      Author: Pato
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Dictionary.h"


int controller_loadArticuloFromText(char* path , Dictionary* pDictionaryArticulo);
int controller_loadPosArancelariaFromText(char* path , Dictionary* pDictionary);
int controller_loadMaritimoFromText(char* path , LinkedList* pDictionary);
int controller_addArticulo(Dictionary* pDictionary,Dictionary* pDictionaryPosAr);
int controller_editArticulo(Dictionary* pDictionaryArticulo);
int controller_removeArticulo(Dictionary* pDictionaryArticulo);
int controller_ListarArticulo(Dictionary* pDictionaryArticulo);
int controller_saveArticleAsText(char* path , Dictionary* diccionarioArticulos);
int controller_savePosArancelariaAsText(char* path , Dictionary* diccionarioPosArancelaria);
int controller_addPosArancelaria(Dictionary* pDictionaryPosArancelaria);
int controller_editPosArancelaria(Dictionary* pDictionaryPosArancelaria);
int controller_removePosArancelaria(Dictionary* pDictionaryPosArancelaria, Dictionary* pDictionaryArticulo);
int controller_ListarPosArancelaria(Dictionary* pDictionaryPosArancelaria);
int controller_saveAereoAsText(char* path , LinkedList* listaAereo);
int controller_loadAereoFromText(char* path , LinkedList* pListaAereo);
int controller_saveMaritimoAsText(char* path , LinkedList* listaMaritimo);
int controller_ListarMaritimo(LinkedList* pListaMaritimo);
int controller_ListarAereo(LinkedList* listaAereo);
int controller_editMaritimo(LinkedList* pListaMaritimo);
int controller_editAereo(LinkedList* pListaAereo);
int controller_getMaxId(LinkedList*);
int controller_ListarArticulos(LinkedList* pLista);
int canUseThisAlphCodeArt(Dictionary* pDictionaryArt, char* arg);
int canUseThisAlphCodePosAr(Dictionary* pDictionaryArt, char* arg);
int controller_loQuePidioMauricioMaritimo(Dictionary* pDictionary);
int controller_loQuePidioMauricioAereo(Dictionary* pDictionary);
#endif /* CONTROLLER_H_ */

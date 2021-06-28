/*
 * Parser.h
 *
 *  Created on: 16 jun. 2021
 *      Author: Pato
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "Dictionary.h"
#include "LinkedList.h"

int parser_articleFromText(FILE* pFile , Dictionary* pArrayListArticle);
int parser_posArancelariaFromText(FILE* pFile , Dictionary* pDictionaryPosArancelaria);
int parser_maritimoFromText(FILE* pFile , LinkedList* pDictionaryMaritimo);
int parser_aereoFromText(FILE* pFile , LinkedList* listaAereo);

#endif /* PARSER_H_ */

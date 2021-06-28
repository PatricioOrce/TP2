/*
 * Articulo.h
 *
 *  Created on: 15 jun. 2021
 *      Author: Pato
 */

#ifndef ARTICULO_H_
#define ARTICULO_H_
#include "PosArancelaria.h"
#include "LinkedList.h"
#include "Dictionary.h"

typedef struct{
	char nombre[64];
	char codigo[64];
	char descripcion[64];
	char paisDeFabricacion[64];
	float valorFob;
	float pesosEnKg;
	float alto;
	float ancho;
	float profundidad;
	char posArancel[64];
	float valorFinalAereo;
	float valorFinalMaritimo;
}Articulo;


Articulo* art_new(void);
Articulo* art_newParametros(char* nombre,char* codigo,char* paisDeFabricacion,float valorFob,
		float pesosEnKg, float ancho, float alto, float profundidad, char* idPosicionArancelaria);
int art_delete(Articulo* this);
Articulo* art_newParametrosTxt(char* nombre,char* codigo,char* paisDeFabricacion,char* valorFob,
		char* pesosEnKg, char* ancho, char* alto, char* profundidad, char* idPosicionArancelaria);

int art_setNombre(Articulo* this, char* nombre);
char* art_getNombre(Articulo* this,int* flagError);
int art_setCodigo(Articulo* this, char* codeArticulo);
char* art_getCodigo(Articulo* this,int* flagError);
int art_setDescripcion(Articulo* this, char* descripcion);
char* art_getDescripcion(Articulo* this,int* flagError);
int art_setPaisDeFabricacion(Articulo* this, char* paisDeFabricacion);
char* art_getPaisDeFabricacion(Articulo* this,int* flagError);
int art_setAncho(Articulo* this, float ancho);
float art_getAncho(Articulo* this,int* flagError);
int art_setAlto(Articulo* this, float alto);
float art_getAlto(Articulo* this,int* flagError);
int art_setProfundidad(Articulo* this, float profundidad);
float art_getProfundidad(Articulo* this,int* flagError);
int art_setIdPosicionArancelaria(Articulo* this, char* idPosicionArancelaria);
char* art_getIdPosicionArancelaria(Articulo* this,int* flagError);
int art_setValorFOB(Articulo* this, float valorFob);
float art_getValorFOB(Articulo* this,int* flagError);
int art_setPesosEnKg(Articulo* this, float pesosEnKg);
float art_getPesosEnKg(Articulo* this,int* flagError);
int art_setIdArticulo(Articulo* this, int id);
int art_getIdArticulo(Articulo* this,int* flagError);
int art_setComodin(Articulo* this, float comodin);
float art_getComodin(Articulo* this,int* flagError);
void art_setearValorInicialDeId(Dictionary* pDictionaryArticulo);
int art_generarId(void);

int art_setValorFinalAereo(Articulo* this, float comodin);
float art_getValorFinalAereo(Articulo* this,int* flagError);
int art_setValorFinalMaritimo(Articulo* this, float comodin);
float art_getValorFinalMaritimo(Articulo* this,int* flagError);

int isFloatValue(float value);
int isIntegerValue(int value);

Articulo* buscarArticuloPorId(LinkedList* pArrayListArticle,int idABuscar);
#endif /* ARTICULO_H_ */

/*
 ============================================================================
 Name        : TrabajoPracticoN2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "utn2.h"
#include "Empleado.h"
#define QTY_EMPLOYEES 1000

int main(void) {

	setbuf(stdout,NULL);
	Employee arrayEmployee[QTY_EMPLOYEES];
	int idEmployee = -1;
	int choice;
	int secondChoice;
	int flagPrimerAlta=0;
	initEmployees(arrayEmployee, QTY_EMPLOYEES);
	do
	{

		tp_menuTpDos();
		utn_getNumero(&choice, "Ingrese una opcion\n", "Opcion invalida\n", 1, 5, 2);
		switch(choice)
		{
		case 1:
			if(newEmployee(arrayEmployee, &idEmployee)==0)
			{
				flagPrimerAlta++;
				printf("Alta exitosa!\n");
			}
			break;
		case 2:
			if(flagPrimerAlta>0)
			{
				modifyEmployee(arrayEmployee, QTY_EMPLOYEES,&idEmployee);
				printf("Modificacion exitosa!\n");
			}
			else
			{
				printf("Carga al menos un empleado para realizar una modificacion.\n");
			}
			break;
		case 3:
			if(flagPrimerAlta!=0)
			{
				deleteEmployee(arrayEmployee, QTY_EMPLOYEES);
				flagPrimerAlta--;
				printf("Baja exitosa!\n");
			}
			else
			{
				printf("Carga al menos un empleado para realizar una eliminacion.\n");
			}
			break;
		case 4:
			if(flagPrimerAlta>0)
			{
				if(utn_getNumero(&secondChoice, " 1). Listado de los empleados ordenados alfabéticamente por Apellido y Sector.\n"
						" 2). Total y promedio de los salarios, y cuántos empleados superan el salario promedio.", "[ERROR]Opcion Invalida.\n", 1, 2, 3)==0)
				{
					switch (secondChoice) {
						case 1:
							reportOne(arrayEmployee, QTY_EMPLOYEES);
							break;
						case 2:
							reporTwo(arrayEmployee, QTY_EMPLOYEES);
							break;
						default:
							break;
					}
				}
			}
			else
			{
				printf("Carga al menos un empleado para ingresar a los informes.\n");
			}

			break;
		case 5:
			system("cls");
			break;
			}
	}
	while(choice!=5);
	return EXIT_SUCCESS;
}

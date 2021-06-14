#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn2.h"
#include "LinkedList.h"


int main()
{
	setbuf(stdout,NULL);

	LinkedList* listaEmpleados = ll_newLinkedList();
	int opcion;
	int flagPrimeroTxt = 0;
	int flagPrimeroBin = 0;

	do{
		utn_getNumero(&opcion, "Ingrese una opcion:\n1] Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
				"2] Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n3] Alta de empleado.\n4] Modificar datos de empleado\n"
				"5] Baja de empleado.\n6] Listar empleados.\n7] Ordenar empleados.\n8] Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
				"9] Guardar los datos de los empleados en el archivo data.csv (modo binario).\n10] Salir\n", "Opcion Invalida.\n", 1, 10, 3);

		switch (opcion) {
			case 1:
				flagPrimeroTxt = 1;
				controller_loadFromText("data.csv", listaEmpleados);
				break;
			case 2:
				flagPrimeroBin = 1;
				controller_loadFromBinary("data.bin", listaEmpleados);
				break;
			case 3:
				controller_addEmployee(listaEmpleados);
				break;
			case 4:
				controller_editEmployee(listaEmpleados);
				break;
			case 5:
				controller_removeEmployee(listaEmpleados);
				break;
			case 6:
				controller_ListEmployee(listaEmpleados);
				break;
			case 7:
				controller_sortEmployee(listaEmpleados);
				break;
			case 8:
				if(flagPrimeroTxt==1)
				{
					controller_saveAsText("data.csv", listaEmpleados);
				}
				else
				{
					printf("No es posible guardar datos en un archivo sin previamente haberlos cargado.(Modo Texto)\n");
				}
				break;
			case 9:
				if(flagPrimeroBin==1)
				{
					controller_saveAsBinary("data.bin", listaEmpleados);
				}
				else
				{
					printf("No es posible guardar datos en un archivo sin previamente haberlos cargado.(Modo Binario)\n");
				}
				break;
			case 10:
				printf("Saliste Excitosamente!.\n");
				break;
			default:
				break;
		}

	}
	while(opcion!=10);




    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char idAux[50];
	char nombreAux[50];
	char horasAux[50];
	char sueldoAux[50];
	Employee* auxEmpleado;
	int flagFirst = 0;
	int conteo=0;


	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",idAux,nombreAux,horasAux,sueldoAux)==4)
				{
					if(flagFirst == 1)
					{
						auxEmpleado = employee_newParametrosTxt(idAux, nombreAux, horasAux, sueldoAux);
						if(auxEmpleado != NULL)
						{
							ll_add(pArrayListEmployee, auxEmpleado);
							conteo++;
						}
					}
					flagFirst = 1;
				}
			}

		}while(!feof(pFile));
		printf("Se cargaron %d empleados.",conteo);
		retorno = 0;
	}
    return retorno;
}



/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int fin;
	int retorno = -1;
	Employee auxEmployee;
	Employee* pEmployee;
	int conteo=0;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{
			fin = fread(&auxEmployee,sizeof(Employee),1,pFile);
			if(fin==1)
			{
				pEmployee = employee_newParametros(auxEmployee.id, auxEmployee.nombre, auxEmployee.horasTrabajadas, auxEmployee.sueldo);
				if(pEmployee!=NULL)
				{
					ll_add(pArrayListEmployee, pEmployee);
					conteo++;
				}
				retorno=0;
			}

		}while(feof(pFile)==0);
		printf("Se cargaron %d empleados",conteo);
	}
	return retorno;
}

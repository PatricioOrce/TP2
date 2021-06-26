/*
 * Empleado.c
 *
 *  Created on: 11 may. 2021
 *      Author: Pato
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Empleado.h"
#include "utn2.h"
#define QTY_EMPLOYEES 1000


/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int initEmployees(Employee* list, int len)
{
	int retorno = -1;

	if(list!=NULL && len >= 0)
	{
		for(int i=0;i<len;i++)
		{
			list[i].isEmpty=0;
		}
	}

 return retorno;
}

/** \brief Looks for a empty position in the array.
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int findEmptyPlace(Employee* list, int len)
{
	int retorno = -1;

	if(list!=NULL && len>=0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty==0)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 *
*/
int addEmployee(Employee* list, int len, int id, char* name,char* lastName,float salary,int sector)
{
	int retorno = -1;
	int indice;

	if(list!=NULL && len>0 && id>=0 && name!=NULL && lastName!=NULL && salary>0 && sector>0)
	{
		indice=findEmptyPlace(list, len);
		if(indice>=0)
		{
			retorno = 0;
			list[indice].id=id;
			strcpy(list[indice].name,name);
			strcpy(list[indice].lastName,lastName);
			list[indice].salary=salary;
			list[indice].sector=sector;
			list[indice].isEmpty=1;
			printf("El ID del empleado es (%d)\n",list[indice].id);
		}
	}

 return retorno;;
}

/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */
int findEmployeeById(Employee* list, int len,int id)
{
	int retorno = -1;

	if(list!=NULL && len>0 && id>=0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].id==id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int removeEmployee(Employee* list, int len, int id)
{
	int retorno = -1;
	if(list!=NULL && len>0 && id>=0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].id==id)
			{
				retorno = 0;
				list[i].isEmpty=0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Request the id and then proceed to remove the employee
 *
 * \param arrayEmployee Employee*
 * \param lenght int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int deleteEmployee(Employee* arrayEmployee, int lenght)
{
	int retorno=-1;
	int auxId;
	if(arrayEmployee!=NULL)
	{
		if(utn_getNumero(&auxId, "Ingrese el ID del empleado a despedir.\n", "[ERROR]ID Invalido.\n", 0, QTY_EMPLOYEES, 3)==0)
		{
			if(arrayEmployee->isEmpty==1)
			{
				retorno=0;
				removeEmployee(arrayEmployee, lenght, auxId);
			}
		}
	}

	return retorno;
}
/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployees(Employee* list, int len, int order)
{
	int retorno = -1;
	int flagSwap;
	int i;
	Employee bufferEmployee;
	int auxiliarCmp;

	if(list != NULL && len >0 && (order == 1 || order == 0))
	{
		retorno=0;
		switch (order) {
			case 1:
				do
				{
					flagSwap = 0;
					for(i=0;i<len;i++)
					{
						auxiliarCmp = strncmp(list[i].lastName,list[i+1].lastName,sizeof(list[i].lastName));
						if(auxiliarCmp > 0 ||
							(auxiliarCmp == 0 && list[i].sector > list[i+1].sector))
						{
							flagSwap = 1;
							bufferEmployee = list[i];
							list[i] = list[i+1];
							list[i+1] = bufferEmployee;
						}
					}
					len--;
				}while(flagSwap);
				break;
			case 0:
				do
				{
					flagSwap = 0;
					for(i=0;i<len;i++)
					{
						auxiliarCmp = strncmp(list[i].lastName,list[i+1].lastName,sizeof(list[i].lastName));
						if(auxiliarCmp < 0 ||
							(auxiliarCmp == 0 && list[i].sector < list[i+1].sector))
						{
							flagSwap = 1;
							bufferEmployee = list[i];
							list[i] = list[i+1];
							list[i+1] = bufferEmployee;
						}
					}
					len--;
				}while(flagSwap);
				break;
		}
	}
	return retorno;
}

/** \brief Print the content of employees array
 * \param list Pointer to employee큦 array
 * \param length int
 * \return int
 *
 */
int printEmployeesArray(Employee* list, int length)
{
	int retorno = -1;

	if(list!=NULL && length>=0)
	{
		retorno=0;
		for(int i=0;i<length;i++)
		{
			printEmployee(&list[i]);
		}
	}

	return retorno;
}

/** \brief Print an employee
 *
 * \param employee Employee*
 * \return int Return (-1) if Error [NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int printEmployee(Employee* employee)
{
	int retorno = -1;

	if(employee!=NULL)
	{
		retorno=0;
		if(employee->isEmpty==1)
		printf("ID: [%d]\tName : [%s]\tLast Name : [%s]\tSalary : [%.2f]\tSector : [%d]\n",employee->id,employee->name,employee->lastName,employee->salary,employee->sector);
	}

	return retorno;
}

/** \brief Requests the employee data and saves it in an auxiliary variable
 * \param employee pointer to array of employees.
 * \param idEmployee Employee큦 ID
 * \return int Return (-1) if Error and (0) if Ok
 */
int newEmployee(Employee* newEmployee,int *idEmployee)
{
	int retorno = -1;
	Employee buffer_employee;

	if(newEmployee!=NULL && idEmployee!=NULL)
	{
		if(	utn_getName(buffer_employee.name, sizeof(buffer_employee.name), "Ingrese nombre: \n", "[Error]Nombre Invalido.\n", 3)==0 &&
			utn_getName(buffer_employee.lastName, sizeof(buffer_employee.lastName), "Ingrese apellido: \n", "[Error]Apellido Invalido.\n", 3)==0 &&
			utn_getNumeroFloat(&buffer_employee.salary, "Ingrese salario: \n", "[Error]Salario Invalido.\n", 1, 5000, 3)==0 &&
			utn_getNumero(&buffer_employee.sector, "Ingrese sector.\n", "[Error]Sector Invalido.\n", 1, 100, 3)==0)
		{
			retorno=0;
			*idEmployee=*idEmployee+1;
			addEmployee(newEmployee, QTY_EMPLOYEES, *idEmployee, buffer_employee.name, buffer_employee.lastName, buffer_employee.salary, buffer_employee.sector);
		}
	}

	return retorno;
}

/** \brief Modifies a specific data of an employee selected by id.
 * \param employee pointer to array of employees.
 * \param longitud lenght of employee큦 array
 * \param idEmployee Employee큦 ID
 * \return int Return (-1) if Error and (0) if Ok
 */
int modifyEmployee(Employee* arrayEmployees,int longitud, int* idEmployee)
{
	int retorno=-1;
	int desicion;
	int indice;
	int auxId;
		printEmployeesArray(arrayEmployees, longitud);
		if(arrayEmployees!=NULL && longitud > 0)
		{
			utn_getNumero(&auxId, "Ingrese ID del empleado a modificar.\n", "[ERROR]ID Invalido.\n", 0, *idEmployee, 3);
			indice=findEmployeeById(arrayEmployees, longitud, auxId);
			if(arrayEmployees[indice].isEmpty==1)
			{
				printf("Que desea modificar?\n");
				printf("1)Nombre\n2)Apellido\n3)Salario\n4)Sector\n");
				utn_getNumero(&desicion, "---->:\n", "[ERROR]Opcion Invalida.\n", 1, 4, 3);

					switch (desicion) {
						case 1:
							if(utn_getName(arrayEmployees[indice].name, sizeof(arrayEmployees[indice].name), "Ingrese Nombre:\n", "[ERROR]Nombre Invalido.\n", 3)==0)
							{
								printf("Nombre modificado con exito!\n");
								retorno = 0;
							}
							break;
						case 2:
							if(utn_getName(arrayEmployees[indice].lastName, sizeof(arrayEmployees[indice].lastName), "Ingrese Apellido:\n", "[ERROR]Apellido Invalido.\n", 3)==0)
							{
								printf("Apellido modificado con exito!\n");
								retorno = 0;
							}
							break;
						case 3:
							if(utn_getNumeroFloat(&arrayEmployees[indice].salary, "Ingrese nuevo salario: \n", "[ERROR]Salario Invalido.\n", 1, 5000, 3)==0)
							{
								printf("Salario modificado con exito!\n");
								retorno = 0;
							}
							break;
						case 4:
							if(utn_getNumero(&arrayEmployees[indice].sector, "Ingrese nuevo sector:\n", "[ERROR]Sector Invalido.\n", 1, 133, 3)==0)
							{
								printf("Sector modificada con exito!\n");
								retorno = 0;
							}
							break;
						default:
							printf("Opcion Incorrecta.\n");
							break;
					}
				}
			}
	return retorno;
}

/** \brief Find the average salary,
 * \param employee Pointer to array of employees.
 * \param longitud Lenght of employee큦 array
 * \param averageSalary Returns the average salary found
 * \return int Return (-1) if Error and (0) if Ok
 */
int findTheAverageSalary(Employee* arrayEmployee, int lenght, float* averageSalary)
{
	int retorno = -1;
	int qtyEmployees=0;
	float acumSueldo=0;

	if(arrayEmployee!=NULL && lenght>=0)
	{
		for(int i=0;i<lenght;i++)
		{
			if(arrayEmployee[i].isEmpty==1)
			{
				qtyEmployees++;
				acumSueldo=acumSueldo+arrayEmployee[i].salary;
			}
		}
		*averageSalary=acumSueldo/qtyEmployees;
	}

	return retorno;
}

/** \brief look for employees with over average salaries
 * \param employee Pointer to array of employees.
 * \param longitud Lenght of employee큦 array
 * \param averageSalary Recives an average salary
 * \return int Return (-1) if Error and (0) if Ok
 */
int employeesAboveAverageSalary(Employee* arrayEmployee, int lenght, float averageSalary)
{
	int retorno = -1;

	if(arrayEmployee!=NULL && lenght>=0)
	{
		for (int i=0;i<lenght;i++)
		{
			if(arrayEmployee[i].isEmpty==1)
			{
				retorno = 0;
				if(arrayEmployee[i].salary>averageSalary)
				printEmployee(&arrayEmployee[i]);
			}
		}
	}

	return retorno;


}

/** \brief List of employees sorted alphabetically by Surname and Sector
 * \param employee Pointer to array of employees.
 * \param lenght Lenght of employee큦 array
 * \return int Return (-1) if Error and (0) if Ok
 */
int reportOne(Employee* arrayEmployees, int lenght)
{
	int retorno = -1;
	if(arrayEmployees!=NULL && lenght>=0)
	{
		retorno = 0;
		sortEmployees(arrayEmployees, lenght, 1);
		printEmployeesArray(arrayEmployees, lenght);
	}

	return retorno;
}

/** \brief Total and average salaries, and how many employees exceed the average salary.
 * \param employee Pointer to array of employees.
 * \param lenght Lenght of employee큦 array
 * \return int Return (-1) if Error and (0) if Ok
 */

int reporTwo(Employee* arrayEmployee, int lenght)
{
	int retorno = -1;
	float salarioPromedio;

	if(arrayEmployee!=NULL && lenght>=0)
	{
		retorno=0;
		findTheAverageSalary(arrayEmployee, lenght, &salarioPromedio);
		printf("El sueldo promedio es %.2f superado por estos empleados: \n",salarioPromedio);
		employeesAboveAverageSalary(arrayEmployee, lenght, salarioPromedio);
	}

	return retorno;
}


void tp_menuTpDos()
{
	printf("[1]Nuevo empleado.\n[2]Modificar datos del empleado.\n[3]Eliminar empleado.\n[4]Informar: \n[5]Salir!\n");
}

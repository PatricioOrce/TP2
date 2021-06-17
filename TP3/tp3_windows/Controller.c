#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		FILE* pFile = fopen(path,"r");
		if(pFile!=NULL)
		{
			parser_EmployeeFromText(pFile, pArrayListEmployee);
			fclose(pFile);
		}
	}
	return 0;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		printf("Entre Load 1\n");
		FILE* pFile = fopen(path,"rb");
		if(pFile!=NULL)
		{
			printf("Entre Load 2\n");
			retorno=0;
			parser_EmployeeFromBinary(pFile, pArrayListEmployee);
			fclose(pFile);
		}
	}
	return retorno;
}
/** \brief Genera un nuevo id a partir del id maximo.
 * \return int
 */
int emp_generarId(LinkedList* lista)
{
	int contador = controller_getMaxId(lista);
	contador++;
	return contador;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char auxNombre[50];
	int auxHorasTrabajadas;
	int auxSalario;
	Employee* auxEmployee;
	int id=10;
	if(pArrayListEmployee!=NULL)
	{
		if(	utn_getName(auxNombre, sizeof(auxNombre), "Ingrese nombre:\n", "Nombre Incorrecto.\n", 3)==0 &&
			utn_getNumero(&auxHorasTrabajadas, "Ingrese Horas trabajadas.\n", "Horas Incorrectas.\n", 35, 730, 3)==0 &&
			utn_getNumero(&auxSalario, "Ingrese Salario.\n", "Salario Incorrecto.\n", 1000, 99999, 3)==0)
		{
			id = emp_generarId(pArrayListEmployee);
			auxEmployee = employee_newParametros(id, auxNombre, auxHorasTrabajadas, auxSalario);
			if(auxEmployee!=NULL)
			{
				ll_add(pArrayListEmployee, auxEmployee);
				retorno=0;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	char auxNombre[50];
	int auxHorasTrabajadas;
	int auxSalario;
	int opcion;
	int index;
	Employee* auxEmployee;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumero(&index, "Ingrese ID de empleado a modificar.\n", "[ERROR]ID Invalido.\n", 0, 999999, 3)==0)
		{
			auxEmployee = buscarPorId(pArrayListEmployee, index);
			if(auxEmployee!=NULL)
			{
				if(utn_getNumero(&opcion, "Que desea modificar?\n1)Nombre.\n2)Horas trabajadas.\n3)Salario.\n", "[Error]Incorrecto.\n", 1, 3, 3)==0)
				{
					switch (opcion) {
						case 1:
							if(utn_getName(auxNombre, sizeof(auxNombre), "Ingrese nuevo nombre.\n", "[ERROR]Nombre Invalido.\n", 3)==0)
							{
								employee_setNombre(auxEmployee, auxNombre);
							}
							break;
						case 2:
							if(utn_getNumero(&auxHorasTrabajadas, "Ingrese nuevas horas trabajadas.\n", "[ERROR]Horas Invalidas.\n", 8, 730, 3)==0)
							{
								employee_setHorasTrabajadas(auxEmployee, auxHorasTrabajadas);
							}
							break;
						case 3:
							if(utn_getNumero(&auxSalario, "Ingrese nuevo salario.\n", "[ERROR]Salario Invalido.\n", 3000, 50000, 3)==0)
							{
								employee_setSueldo(auxEmployee, auxSalario);
							}
							break;
						default:
							break;
					}
				}
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
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int index;
	Employee* auxEmployee;

	if(pArrayListEmployee!=NULL)
	{
		if(utn_getNumero(&index, "Ingrese ID de empleado a eliminar.\n", "[ERROR]ID Invalido.\n", 0, 999999, 3)==0)
		{
			auxEmployee = buscarPorId(pArrayListEmployee, index);
			if(auxEmployee!=NULL)
			{
				retorno = 0;
				index = ll_indexOf(pArrayListEmployee, auxEmployee);
				employee_delete(auxEmployee);
				ll_remove(pArrayListEmployee, index);
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
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	Employee* auxEmpleado;
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		for(int i=0;i<ll_len(pArrayListEmployee);i++)
		{
			auxEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			printf("ID:[%d]\tNombre:[%s]\tHoras trabajadas:[%d]\tSueldo:[%d]\n",auxEmpleado->id,auxEmpleado->nombre,auxEmpleado->horasTrabajadas,auxEmpleado->sueldo);
		}
		retorno = 0;
	}
    return retorno;
}


/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if (pArrayListEmployee!=NULL)
	{
		ll_sort(pArrayListEmployee, funcionCriterio, 1);
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
   int retorno = -1;
   Employee* auxEmployee;
   FILE* pFile;
   int auxId;
   char* auxNombre;
   int auxHoras;
   int auxSalario;
   int flagError;
   int longitud;

   longitud = ll_len(pArrayListEmployee);
   if(path!=NULL && pArrayListEmployee!=NULL)
   {
	   pFile = fopen(path,"w");
	   if(pFile!=NULL)
	   {
		   fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");
		   for(int i=0;i<longitud;i++)
		   {
			   auxEmployee = ll_get(pArrayListEmployee, i);
			   if(auxEmployee!=NULL)
			   {
				   auxId = employee_getId(auxEmployee, &flagError);
				   if(!flagError)
				   {
					  auxNombre = employee_getNombre(auxEmployee, &flagError);
					  if(!flagError)
					  {
						 auxHoras = employee_getHorasTrabajadas(auxEmployee, &flagError);
						 if(!flagError)
						 {
							auxSalario = employee_getSueldo(auxEmployee, &flagError);
							if(!flagError)
							{
							 fprintf(pFile,"%d,%s,%d,%d\n",auxId,auxNombre,auxHoras,auxSalario);
							 retorno = 0;
							}
						 }
					 }
				  }
			   }
			}
		   fclose(pFile);
	   }
   }

   return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* auxEmployee;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path,"wb");
		if(pFile!=NULL)
		{
			for(int i=0;i<ll_len(pArrayListEmployee);i++)
			{
				auxEmployee = ll_get(pArrayListEmployee, i);
				if(auxEmployee!=NULL)
				{
					fwrite(auxEmployee,sizeof(Employee),1,pFile);
				}
			}
			fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Funcion que busca el id maximo.
 *	\param LinkedList* recibe una lista dinamica con los empleados a utilizar.
 *	\return int
 */
int controller_getMaxId(LinkedList* lista)
{
	int retorno = -1;
	Employee* auxEmployee;
	int maximo;
	int size;
	if(lista!=NULL)
	{
		size = ll_len(lista);
		for(int i=0;i<size;i++)
		{
			auxEmployee = ll_get(lista, i);
			if(i==0)
			{
				maximo = auxEmployee->id;
			}
			if(auxEmployee->id > maximo)
			{
				maximo = auxEmployee->id;
			}
		}
		retorno = maximo;
	}
	return retorno;
}



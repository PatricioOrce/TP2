#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn2.h"


/** \brief Reserva espacio de memoria para la estructura Empleado.
 * \return Employee* retorna la direccion de memoria reservada.
 */
Employee* empleado_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}
/** \brief Reserva espacio de memoria para la estructura Empleado y setea sus valores recibidos como texto por parametro .
 * \param char* recibe el id como string
 * \param char*	recibe el nombre como string
 * \param char*	recibe las horas trabajadas como string
 * \param char*	recibe el salario como string
 * \return Employee* retorna un puntero a empleado con los valores seteados.
 */
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadas,char* salario)
{
	Employee* auxEmpleado = empleado_new();
	if(auxEmpleado != NULL)
	{
		if  ( 	employee_setNombre(auxEmpleado,nombreStr) != 0 ||
				employee_setHorasTrabajadas(auxEmpleado,atoi(horasTrabajadas)) != 0 ||
				employee_setSueldo(auxEmpleado,atoi(salario)) != 0 ||
				employee_setId(auxEmpleado,atoi(idStr)) != 0 )
		{
			employee_delete(auxEmpleado);
			auxEmpleado = NULL;
		}
	}
	return auxEmpleado;
}
/** \brief Reserva espacio de memoria para la estructura Empleado y setea sus valores recibidos por parametro.
 * \param int recibe el id como entero
 * \param char* recibe el nombre como string
 * \param int recibe las horas trabajadas como entero
 * \param int recibe el salario como entero
 * \return Employee* retorna un puntero a empleado con los valores seteados.
 */
Employee* employee_newParametros(int idStr,char* nombreStr,int horasTrabajadas,int salario)
{
	Employee* auxEmpleado = empleado_new();
	if(auxEmpleado != NULL)
	{
		if  ( 	employee_setNombre(auxEmpleado,nombreStr) != 0 ||
				employee_setHorasTrabajadas(auxEmpleado,horasTrabajadas) != 0 ||
				employee_setSueldo(auxEmpleado,salario) != 0 ||
				employee_setId(auxEmpleado,idStr) != 0 )
		{
			employee_delete(auxEmpleado);
			auxEmpleado = NULL;
		}
	}
	return auxEmpleado;
}
/** \brief Baja de empleados.
 * \param Employee* Puntero de empleado a eliminar.
 * \return int 0 si salio bien y -1 si salio mal.
 */
int employee_delete(Employee* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		this=NULL;
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el valor del id en la estructura empleado.
 * \param Employee* empleado al cual se le seteara el id.
 * \param Int  id a setear.
 * \return int devuelve 0 si salio todo bien y -1 si salio algo mal.
 */
int employee_setId(Employee* this, int idEmpleado)
{
	int retorno = -1;
	if(this != NULL && isValidId(idEmpleado)==0)
	{
		this->id = idEmpleado;
		retorno = 0;
	}
	return retorno;
}
/** \brief Pide y retorna el valor del Id de un empleado.
 * \param Employee* puntero a empleado a utilizar.
 * \param int* puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta el ID.
 */
int employee_getId(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->id;
		*flagError = 0;
	}
	return auxId;
}
/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

Employee* buscarPorId(LinkedList* pArrayListEmployee,int idABuscar)
{
	int i;
	int lenLista ;
	Employee* pEmpEdit;
	Employee* pRet=NULL;
	int idEncontrado;
	int flag;

	if(pArrayListEmployee!=NULL)
	{
		lenLista = ll_len(pArrayListEmployee);

		for(i=0; i<lenLista; i++)
		{
			pEmpEdit = (Employee*)ll_get(pArrayListEmployee, i);

			idEncontrado = employee_getId(pEmpEdit, &flag);

			if(idABuscar == idEncontrado)
			{
				pRet = pEmpEdit;
				break;
			}
		}
	}
	return pRet;
}
/** \brief Funcion que valida el id
 * \param int Valor del id a validar
 * \return 0 si salio todo bien y -1 si algo salio mal
 */
int isValidId(int idEmpleado)
{
	int retorno = -1;

	if(idEmpleado>=0)
	{
		retorno = 0;
	}

	return retorno;
}
/** \brief Setea el valor del nombre en la estructura empleado.
 * \param Employee* empleado al cual se le seteara el nombre
 * \param char* nombre a setear.
 * \return int devuelve 0 si salio todo bien y -1 si salio algo mal.
 */
int employee_setNombre(Employee* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isValidNombre(nombre)==0)
	{
		strcpy(this->nombre,nombre);
		retorno = 0;
	}
	return retorno;
}
/** \brief Pide y retorna como puntero a char el nombre de un empleado.
 * \param Employee* puntero a empleado a utilizar.
 * \param int* puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta el nombre como char*.
 */
char* employee_getNombre(Employee* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre=NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}
/** \brief Funcion que valida el nombre
 * \param char* puntero a char que representa el nombre a validar.
 * \return 0 si salio todo bien y -1 si algo salio mal
 */

int isValidNombre(char* nombre)
{
	int retorno=-1;

	if(isName(nombre)==0)
	{
		retorno=0;
	}
	return retorno;
}
/** \brief Setea el valor del Horas Trabajadas en la estructura empleado.
 * \param Employee* empleado al cual se le setearan las horas trabajadas.
 * \param Int Horas trabajadas a setear.
 * \return int devuelve 0 si salio todo bien y -1 si salio algo mal.
 */
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && isValidHorasTrabajadas(horasTrabajadas)==0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}
/** \brief Pide y retorna la cantidad de horas trabajadas de un empleado.
 * \param Employee* puntero a empleado a utilizar.
 * \param int* puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta las horas trabajadas del empleado.
 */
int employee_getHorasTrabajadas(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->horasTrabajadas;
		*flagError = 0;
	}
	return auxId;
}
/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int isValidHorasTrabajadas(int horasTrabajadas)
{
	int retorno = -1;

	if(horasTrabajadas>=35 && horasTrabajadas<=730)
	{
		retorno=0;
	}
	return retorno;
}
/** \brief Setea el valor del sueldo en la estructura empleado.
 * \param Employee* empleado al cual se le seteara el sueldo.
 * \param Int sueldo a setear.
 * \return int devuelve 0 si salio todo bien y -1 si salio algo mal.
 */
int employee_setSueldo(Employee* this, int sueldo)
{
	int retorno = -1;
	if(this != NULL && isValidSueldo(sueldo)==0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}
/** \brief Pide y retorna el valor del salario de un empleado.
 * \param Employee* puntero a empleado a utilizar.
 * \param int* puntero a int que almacena -1 si algo salio mal y 0 si salio bien.
 * \return int retorta el salario.
 */
int employee_getSueldo(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->sueldo;
		*flagError = 0;
	}
	return auxId;
}
/** \brief Funcion que valida el sueldo
 * \param sueldo Valor del sueldo a validar
 * \return 0 si salio todo bien y -1 si algo salio mal
 */
int isValidSueldo(int sueldo)
{
	int retorno = -1;

	if(sueldo>=1000 && sueldo<=99999)
	{
		retorno=0;
	}
	return retorno;
}

/** \brief Funcion que dice el criterio del ordenamiento
 * \param void* empleadoUno recive el primer puntero a void para hacer la comparacion.
 * \param void* empleadoDos recive el segundo puntero a void para hacer la comparacion.
 * \return int
 */
int funcionCriterio(void* empleadoUno, void* empleadoDos)
{
	int retorno = 0;
	Employee* empUno;
	Employee* empDos;
	int flagError;
	char* nombre;
	char* nombreDos;

	empUno = (Employee*)empleadoUno;
	empDos = (Employee*)empleadoDos;

	nombre = employee_getNombre(empUno, &flagError);
	nombreDos = employee_getNombre(empDos, &flagError);

	if(strcmp(nombre,nombreDos)>0)
	{
		retorno = 1;
	}
	else
	{
		retorno = -1;
	}
	return retorno;
}


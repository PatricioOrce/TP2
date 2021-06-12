#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn2.h"
#include "LinkedList.h"
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* salario);
Employee* employee_newParametros(int idStr,char* nombreStr,int horasTrabajadasStr,int salario);
int employee_delete(Employee* this);

int employee_setId(Employee* this, int idEmpleado);
int employee_getId(Employee* this,int* id);
Employee* buscarPorId(LinkedList* pArrayListEmployee,int idABuscar);
int funcionCriterio(void* empleadoUno, void* empleadoDos);

int employee_setNombre(Employee* this,char* nombre);
char* employee_getNombre(Employee* this,int* flagError);

int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this, int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int isValidHorasTrabajadas(int horasTrabajadas);
int isValidSueldo(int sueldo);
int isValidNombre(char* nombre);
int isValidId(int idEmpleado);
#endif // employee_H_INCLUDED

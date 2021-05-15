/*
 * Empleado.h
 *
 *  Created on: 11 may. 2021
 *      Author: Pato
 */

#ifndef EMPLEADO_H_
#define EMPLEADO_H_

typedef struct
{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;
}Employee;
int initEmployees(Employee* list, int len);
int modifyEmployee(Employee* arrayEmployees,int longitud, int* idEmployee);
int removeEmployee(Employee* list, int len, int id);
int deleteEmployee(Employee* arrayEmployee, int lenght);
int printEmployee(Employee* employee);
int newEmployee(Employee* newEmployee,int *idEmployee);
int reportOne(Employee* arrayEmployees, int lenght);
int reporTwo(Employee* arrayEmployee, int lenght);
void tp_menuTpDos();

#endif /* EMPLEADO_H_ */

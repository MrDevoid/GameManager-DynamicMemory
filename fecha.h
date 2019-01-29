//Alejandro Hern�ndez Cerezo y Jose Manuel Pinto Lozano
#ifndef FECHA_H
#define FECHA_H
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

const time_t MAX_DIAS = 2592000;

typedef time_t tFecha;
tFecha fechaActual();  //Devuelve la fecha actual
string stringFecha(tFecha fecha, bool hora);  //Funci�n que muestra la fecha en el formato A�o/Mes/Dia (HH:MM:SS)
bool inactivo(tFecha actual, tFecha ult_conex);
#endif
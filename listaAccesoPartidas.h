//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef LISTA_ACCESO_PARTIDAS_H
#define LISTA_ACCESO_PARTIDAS_H

#include <string>
#include "listaPartidas.h"
const int MAX_PAR_US = 10;
using namespace std;

struct tListaAccesoPartidas {
	tPartida* lista [MAX_PAR_US];
	int cont;
};


void iniciar(tListaAccesoPartidas & lista); //Inicia el vector de partidas en curso
bool llena(tListaAccesoPartidas const & lista); //Comprueba que el tamaño de tListaAccesoPartidas no supera MAX_PAR_US
bool insertar(tListaAccesoPartidas & lista, tPartida* partida); //Inserta un nuevo elemento tParIdEn en la lista
bool eliminar(tListaAccesoPartidas & lista, tPartida* id); //Elimina un elemento tParIdEn de la lista
void ordenar_Fecha(tListaAccesoPartidas & lista);
void ordenar_Turno(tListaAccesoPartidas & lista, string & nombre);
bool vacio(tListaAccesoPartidas & lista);

#endif
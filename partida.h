//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef PARTIDA_H
#define PARTIDA_H

#include "fecha.h"
#include "Conecta4.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
enum tEstadoPartida {EnCurso, Terminada};

struct tPartida{
	string identificador;
	string adv1;
	string adv2;
	tFecha inicio;
	tFecha fin;
	tEstadoPartida estado;
	tConecta4 juego;
};


void nueva(tPartida & partida, string const& adv1, string const& adv2);		//Crea una nueva partida iniciando todos sus campos
void guardar(const tPartida & partida, ofstream & archivo);		//Guarda los datos de tPartida en el archivo
bool cargar(tPartida & partida, ifstream & archivo);		//Carga los datos de tPartida del archivo
bool turno(tPartida const& partida, string const& usuario);		//Dada una partida y un usuario, devuelve true si es su turno
void abandonar(tPartida & partida);		//Actualiza los campos de una partida que se abandona
bool aplicarJugada(tPartida & partida, int col); //Aplica la jugada indicada si es posible y actualiza los campos de la partida
bool enCurso(tPartida & partida);		//Comprueba si una partida sigue en curso
string cabecera(tPartida const& partida, string const& usuario);	//Devuelve toda la informacion de la cabecera de una partida
bool buscarPartidas(tPartida const& partida, string const& user); //Dado un usuario concreto, comprueba que es uno de los jugadores de esa partida
bool inactivo(tPartida & partida);				//Funcion que dada una partida, comprueba si esta inactiva o no
bool evaluarcond(tPartida const&partida, string const& user);	//Funcion que dada una partida y un user, comprueba que uno de los contrincantes
																//es el user, que la partida ha terminado y que no ha sido ni por abandono ni inactividad
string adversario(tPartida const&partida, string const& user);	//Funcion que dada una partida y uno de los contendientes, devuelve el nombre del otro
#endif
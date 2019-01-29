#ifndef HISTORICO_H
#define HISTORICO_H

#include "listaPartidas.h"
#include "listaUsuarios.h"
#include <string>

struct tAdversarios{
	string nombre;
	int ganadas;
	int empatadas;
	int perdidas;
};

struct tAcabadas{
	tAdversarios* lista;
	int cont;
	int capacidad;
};

//Funcion que muestra por pantalla los distintos campos del adversario
void verestadisticas(tAdversarios const& adversario);	

//Funcion que recorre la lista de partidas;
//comprobando si hay alguna terminada (por victoria o empate) y que aun no este en el historico
void comprobarListaPartidas(tListaPartidas const& partidas, tAcabadas & lista, string const& user);

//Funcion que dado un usuario, carga todas las estadisticas de sus partidas
bool cargarhistorico(tAcabadas & partidas, string const& user); 

//Funcion que dado una lista de usuarios, genera la lista de adversarios del user actual (se mantiene el orden alfabetico)
void generarUsers(tAcabadas & partidas, tListaUsuarios & usuarios, string const& usuario); 

//Funcion que dada la lista de adversarios, una partida y el jugador actual; actualiza los campos del rival
//de esa partida en la lista de acabadas
void actualizar(tAcabadas & lista, tPartida & partida, string const& user);

//Funcion que borra el array dinamico utilizado
void destruir(tAcabadas & lista);
#endif
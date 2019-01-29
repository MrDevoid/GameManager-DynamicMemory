//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#ifndef GESTOR_H
#define GESTOR_H
#include "ListaAccesoPartidas.h"
#include "Historico.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


struct tGestor{
	tListaPartidas partidas;
	tListaUsuarios usuarios;
	int indiceusuario;
	tPartida * indicepartida;
	tListaAccesoPartidas listapartidas;
	tAcabadas acabadas;
};

/*Inicializa la lista de partidas y usuarios, devolviendo false si no se ha podido realizar correctamente*/
bool arrancar(tGestor & gestor);	

//Recorre las partidas y rellena las partidas actuales de cada uno de los jugadores
void generarAccesos(tGestor & gestor);

//Guarda los datos modificados de la sesion y apaga el gestor
void apagar(tGestor & gestor);

//Funcion que recibe el usuario y la clave, y devuelve true si se ha iniciado sesion correctamente
bool iniciarSesion(tGestor & gestor, string const& idUsu, string const& clave);

//Añade un nuevo elemento a la lista de usuarios
bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave);

//Comprueba si tiene avisos
bool tieneAvisos(tGestor const& gestor, string & aviso);

//Elimina todos los avisos de un jugador
void limpiarAvisos(tGestor & gestor);

//String que recoge todos los datos del usuario
string resumenActividad(tGestor const& gestor);

//Funcion que ordena la lista de partidas de un usuario por fecha
void ordenar_Fecha(tGestor & gestor);

//Funcion que ordena la lista de partidas de un usuario por turno y fecha
void ordenar_Turno(tGestor & gestor);

//Devuelve el numero de partidas del usuario en curso
int partidasUsuario(tGestor const& gestor);

//Muestra por pantalla las datos de las partidas de un usuario y si tiene o no el turno
string cabecera(tGestor const& gestor, int posEnCurso);

//Crea una nueva partida
bool nuevaPartida(tGestor & gestor);

//Selecciona la partida indicada por el usuario
void apuntaPartida(tGestor & gestor, int posParEnCurso);

//Muestra el juego por pantalla
void mostrarPartida(tGestor const& gestor);

//Devuelve true si es el turno del usuario
bool esSuTurno(tGestor const& gestor);

//Funcion que controla el funcionamiento de la partida
void jugarPartida(tGestor & gestor, int col);

//Funcion que gestiona el abandono voluntario de la partida
void abandonarPartida(tGestor & gestor);

//Comprueba si la partida actual sigue en curso
bool sigue(tGestor & gestor);

//Función que comprueba si el usuario seleccionado por el gestor tiene todas sus partidas ocupadas 
bool llena(tGestor & gestor);

//Devuelve true si el usuario no tiene ninguna partida en curso
bool vacia(tGestor & gestor);

//Funcion que reinicia el array dinamico de datos dinamicos de la lista de partidas
void reiniciar(tGestor & gestor);

//Funcion que muestra todos los users de la lista de adversarios
void mostrarAcabadas(tGestor & gestor);

//Funcion que devuelve el numero de adversarios en la lista de acabadas
int partidasAcabadas(tGestor & gestor);

//Funcion que muestra por pantalla las estadisticas contra otro usuario concreto
void mostrarStats(tGestor & gestor, int opcion);

//Funcion que crea y actualiza toda la lista de estadisticas contra otros usuarios
bool generarAcabadas(tGestor & gestor);

//Funcion que reinicia todas las acabadas
void terminarAcabadas(tGestor & gestor);
#endif
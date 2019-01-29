#include "Historico.h"
#include "checkML.h"

//Funcion que inicializa el array dinamico
void iniciar(tAcabadas & lista, int tam){
	lista.lista = new tAdversarios[tam];
	lista.cont = 0;
	lista.capacidad = tam;
}

void destruir(tAcabadas & lista){
	lista.cont = 0;
	delete[] lista.lista;
	lista.capacidad = 0;
}

//Funcion que inicializa los campos de un tAdversario
void rellenar(tAdversarios & user, string & nombre){
	user.ganadas = 0;
	user.empatadas = 0;
	user.perdidas = 0;
	user.nombre = nombre;
}

//Funcion que dada una partida y un adversario, actualiza el campo correspondiente al estado de la partida
void modificar(tAdversarios & user,tPartida & partida){
	if (partida.juego.estado == Bloqueo) ++user.empatadas;
	else if (turno(partida, user.nombre)) ++user.perdidas;
	else ++user.ganadas;
}

void verestadisticas(tAdversarios const& adversario){
	cout << "Usuario: " << adversario.nombre << '\n';
	cout << "Partidas ganadas: " << adversario.ganadas << '\n';
	cout << "Partidas empatadas: " << adversario.empatadas << '\n';
	cout << "Partidas perdidas: " << adversario.perdidas << '\n';
}

void generarUsers(tAcabadas & partidas, tListaUsuarios & usuarios, string const& usuario){
	iniciar(partidas, usuarios.cont-1);
	for (int i = 0; i < usuarios.cont; ++i){
		cout << usuarios.usuarios[i]->identificador;
		if (usuarios.usuarios[i]->identificador != usuario) rellenar(partidas.lista[partidas.cont], usuarios.usuarios[i]->identificador),
			++partidas.cont;
	}
}


//Busqueda binaria de un id en la lista de acabadas (true si la encuentra y false en caso contrario)
bool buscar(tAcabadas const& lista, string const& idUser, int & pos){
	int inicio = 0, fin = lista.cont, mitad;
	bool encontrado = false;
	while (inicio < fin && !encontrado){			//Se realiza busqueda binaria
		mitad = (inicio + fin - 1) / 2;		//Se actualiza la posicon mitad en funcion de su relacion de orden con el elemento buscado
		if ((lista.lista[mitad]).nombre > idUser) fin = mitad;
		else if ((lista.lista[mitad]).nombre < idUser) inicio = mitad + 1;
		else encontrado = true, pos = mitad;
	}
	if (!encontrado){
		pos = inicio;
		return false;
	}
	else return true;
}


void actualizar(tAcabadas & lista, tPartida & partida, string const& user){
	int pos;
	if (buscar(lista, adversario(partida, user), pos)){
		modificar(lista.lista[pos], partida);
	}
}

bool cargarhistorico(tAcabadas & partidas, string const& user){
	ifstream archivo;
	tPartida partida;
	int pos;
	archivo.open("historico.txt");
	if (archivo.is_open()){
		int tam;
		archivo >> tam;
		for (int i = 0; i < tam; ++i){
			cargar(partida, archivo);
			if (evaluarcond(partida, user)) actualizar(partidas, partida, user);
		}
	}
	archivo.close();
	return !archivo.fail();
}

void comprobarListaPartidas(tListaPartidas const& partidas, tAcabadas & lista, string const& user){
	int pos;
	for (int i = 0; i < partidas.cont; ++i){
		if (partidas.partidas[i]->estado == Terminada && evaluarcond(*partidas.partidas[i], user)){
			actualizar(lista, *partidas.partidas[i], user);
		}
	}
}

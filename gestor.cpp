//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "gestor.h"


bool arrancar(tGestor & gestor){
	bool cond = false;
	ifstream archivopartidas, archivousuarios;
	archivopartidas.open("partidas.txt");
	archivousuarios.open("usuarios.txt");
	if (archivopartidas.is_open() && archivousuarios.is_open() &&
		cargar(gestor.partidas, archivopartidas) && cargar(gestor.usuarios, archivousuarios)){
		cond = true;
	}
	archivopartidas.close();
	archivousuarios.close();
	return cond;
}

void generarAccesos(tGestor & gestor){
	int posicion;
	for (int i = 0; i < gestor.partidas.cont; ++i){
		if ((gestor.partidas.partidas[i])->estado == EnCurso){
			tPartida * puntero = gestor.partidas.partidas[i];
			if (buscarPartidas(*puntero, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador))
				insertar(gestor.listapartidas, puntero);
		}		
	}
}

int generarAvisos(tGestor & gestor){
	int cont = 0, pos1, pos2;
	stringstream avisouser, avisorival;
	for (int i = 0; i < gestor.partidas.cont; ++i){
		if (inactivo(*gestor.partidas.partidas[i])){
			++cont;
			buscar(gestor.usuarios, gestor.partidas.partidas[i]->adv1, pos1);
			buscar(gestor.usuarios, gestor.partidas.partidas[i]->adv2, pos2);
			if (turno(*gestor.partidas.partidas[i], gestor.partidas.partidas[i]->adv1)){
				avisouser << "Has perdido por inactividad contra " << gestor.usuarios.usuarios[pos2]->identificador << " el " << stringFecha(gestor.partidas.partidas[i]->fin, false);
				avisorival << "Has ganado por inactividad contra " << gestor.usuarios.usuarios[pos1]->identificador << " el " << stringFecha(gestor.partidas.partidas[i]->fin, false);
			}
			else{
				avisouser << "Has ganado por inactividad contra " << gestor.usuarios.usuarios[pos2]->identificador << " el " << stringFecha(gestor.partidas.partidas[i]->fin, false);
				avisorival << "Has perdido por inactividad contra " << gestor.usuarios.usuarios[pos1]->identificador << " el " << stringFecha(gestor.partidas.partidas[i]->fin, false);
			}
			actualizarAvisos(*gestor.usuarios.usuarios[pos1], avisouser.str());
			actualizarAvisos(*gestor.usuarios.usuarios[pos2], avisorival.str());
		}
		else if (gestor.partidas.partidas[i]->estado == Terminada) ++cont;
	}
	return cont;
}

void apagar(tGestor & gestor){
	ofstream archivopartidas, archivousuarios;
	archivopartidas.open("partidas.txt");
	archivousuarios.open("usuarios.txt");
	int cont = generarAvisos(gestor);
	apagar(gestor.partidas, archivopartidas,cont);
	apagar(gestor.usuarios, archivousuarios);
	archivopartidas.close();
	archivousuarios.close();
}

//Menu Registro:

bool iniciarSesion(tGestor & gestor, string const& idUsu, string const& clave){
	int posicion;
	if (buscar(gestor.usuarios, idUsu, posicion)){
		if (iniciarSesion(*(gestor.usuarios.usuarios[posicion]), clave)){
			gestor.indiceusuario = posicion;
			return true;
		}
	}
	return false;
}

bool crearCuenta(tGestor & gestor, string const& idUsu, string const& clave){
	tUsuario usuario; int posicion;
	iniciar(usuario, idUsu, clave);	
	if (insertar(gestor.usuarios, usuario, posicion)){
		gestor.indiceusuario = posicion;
		return true;
	}
	return false;
}

bool tieneAvisos(tGestor const& gestor, string & aviso){
	if (!gestor.usuarios.usuarios[gestor.indiceusuario]->avisos.empty()){
		aviso = gestor.usuarios.usuarios[gestor.indiceusuario]->avisos;
		return true;
	}
	return false;
}

void limpiarAvisos(tGestor & gestor){
	limpiarAvisos(*(gestor.usuarios.usuarios[gestor.indiceusuario]));
}

string resumenActividad(tGestor const& gestor){
	return resumenActividad(*(gestor.usuarios.usuarios[gestor.indiceusuario]));
}


// Menú Usuario:

//Funcion que devuelve true si es el turno del usuario por el que se pregunta



void ordenar_Fecha(tGestor & gestor){
	ordenar_Fecha(gestor.listapartidas);
}

void ordenar_Turno(tGestor & gestor){
	ordenar_Turno(gestor.listapartidas, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
}

int partidasUsuario(tGestor const& gestor){
	return gestor.listapartidas.cont;
}

string cabecera(tGestor const& gestor, int posEnCurso){
	return cabecera(*(gestor.listapartidas.lista[posEnCurso]), gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
}

bool llena(tGestor & gestor){
	return llena(gestor.listapartidas);
}

bool nuevaPartida(tGestor & gestor){
	int posicion;
	tPartida partida;
	//Comprueba que no ha completado el maximo de partidas y que aun no ha solicitado otra partida
	if (!llena(gestor) && !gestor.usuarios.usuarios[gestor.indiceusuario]->espera){
		//Busca un usuario de su mismo nivel en espera
		if (buscarUsuarioEsperando(gestor.usuarios, gestor.usuarios.usuarios[gestor.indiceusuario]->dificultad, posicion)){
			//En caso de encontrarlo, crea una nueva partida y la añade a la lista de partidas de cada usuario
			nueva(partida, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador, gestor.usuarios.usuarios[posicion]->identificador);
			insertar(gestor.partidas, partida);
			gestor.indicepartida = gestor.partidas.partidas[gestor.partidas.cont-1];
			nuevaPartida(*(gestor.usuarios.usuarios[gestor.indiceusuario]));
			nuevaPartida(*(gestor.usuarios.usuarios[posicion]));
			return true;
		}
		//En caso de no encontrar usuarios en espera, se pone el jugador en espera
		else gestor.usuarios.usuarios[gestor.indiceusuario]->espera = true;
	}
	return false;
}


//Menu Partida:

void apuntaPartida(tGestor & gestor, int posParEnCurso){
	gestor.indicepartida=gestor.listapartidas.lista[posParEnCurso];
}

void mostrarPartida(tGestor const& gestor){
	mostrar(gestor.indicepartida->juego, gestor.indicepartida->adv1, gestor.indicepartida->adv2);
}

bool esSuTurno(tGestor const& gestor){
	return turno(*(gestor.indicepartida), gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
}

//Funcion que busca el adversario del jugador actual en la partida seleccionada y devuelve su posicion
void encuentrarival(tGestor & gestor, int & pos){
	string rival;
	if (gestor.usuarios.usuarios[gestor.indiceusuario]->identificador==gestor.indicepartida->adv1){
		rival = gestor.indicepartida->adv2;
	}
	else rival = gestor.indicepartida->adv1;
	buscar(gestor.usuarios, rival, pos);
}

//Funcion que actualiza los datos del usuario y actualiza los avisos
void actualizarinfo(tGestor & gestor, int pos, tResultado act, tResultado otro, string const& aviso){
	aplicarFinPartida(*(gestor.usuarios.usuarios[gestor.indiceusuario]), act);
	aplicarFinPartida(*(gestor.usuarios.usuarios[pos]), otro);
	actualizarAvisos(*(gestor.usuarios.usuarios[pos]), aviso);
	eliminar(gestor.listapartidas, gestor.indicepartida);
}


void jugarPartida(tGestor & gestor, int col){
	if (aplicarJugada(*(gestor.indicepartida), col) && gestor.indicepartida->juego.estado != Jugando){
		int pos;
		encuentrarival(gestor, pos);
		tResultado act, otro;
		stringstream aviso;
		if (gestor.indicepartida->juego.estado == Ganador){
			act = Gana;
			otro = Pierde;
			aviso << "Has perdido la partida contra " << gestor.usuarios.usuarios[gestor.indiceusuario]->identificador << " el " << stringFecha(gestor.indicepartida->fin,false);
		}
		else{
			act = Empata, otro = Empata;
			aviso << "Has empatado la partida contra " << gestor.usuarios.usuarios[gestor.indiceusuario]->identificador << " el " << stringFecha(gestor.indicepartida->fin, false);
		}
		actualizarinfo(gestor, pos, act, otro, aviso.str());
		actualizar(gestor.acabadas, *gestor.indicepartida, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
	}
}

bool generarAcabadas(tGestor & gestor){
	generarUsers(gestor.acabadas, gestor.usuarios, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
	if (cargarhistorico(gestor.acabadas, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador)){
		comprobarListaPartidas(gestor.partidas, gestor.acabadas, gestor.usuarios.usuarios[gestor.indiceusuario]->identificador);
		return true;
	}
	return false;
}

void mostrarAcabadas(tGestor & gestor){
	int cont = gestor.acabadas.cont;
	for (int i = 0; i < cont; ++i){
		cout << i + 1 << ".- " << gestor.acabadas.lista[i].nombre << '\n';
	}
}

void mostrarStats(tGestor & gestor, int opcion){
	verestadisticas(gestor.acabadas.lista[opcion]);
}

int partidasAcabadas(tGestor & gestor){
	return gestor.acabadas.cont;
}

void terminarAcabadas(tGestor & gestor){
	destruir(gestor.acabadas);
}


bool sigue(tGestor & gestor){
	return enCurso(*(gestor.indicepartida));
}

void abandonarPartida(tGestor & gestor){
	string rival;
	stringstream aviso;
	int pos;
	encuentrarival(gestor, pos);
	abandonar(*(gestor.indicepartida));
	aviso << "Has ganado por abandono contra " << gestor.usuarios.usuarios[gestor.indiceusuario]->identificador << " el " << stringFecha(gestor.indicepartida->fin, false);
	actualizarinfo(gestor, pos, Pierde, Gana, aviso.str());

}

bool vacia(tGestor & gestor){
	return vacio(gestor.listapartidas);
}

void reiniciar(tGestor & gestor){
	iniciar(gestor.listapartidas);
}
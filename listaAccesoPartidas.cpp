//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaAccesoPartidas.h"

//Devuelve la posicion en la ListaAccesoPartidas a partir del indentificador de la partida
bool buscaridentificador(tListaAccesoPartidas & lista, tPartida* id,int & posicion){
	for (int i = 0; i < lista.cont; ++i){
		if (lista.lista[i] == id){
			posicion = i;
			return true;
		}
	}
	return false;
}

void iniciar(tListaAccesoPartidas & lista){
	lista.cont = 0;
}

bool llena(tListaAccesoPartidas const& lista){
	return lista.cont >= MAX_PAR_US;
}

bool insertar(tListaAccesoPartidas & lista, tPartida* partida){
	if (!llena(lista)){				
		lista.lista[lista.cont] = partida;		//En caso de quedar espacio añade el nuevo elemento tParIdEn
		++lista.cont;
		return true;
	}
	return false;
}

bool eliminar(tListaAccesoPartidas & lista, tPartida* id){
	int posicion;
	if (buscaridentificador(lista, id, posicion)){
		lista.lista[posicion] = lista.lista[lista.cont - 1];  //Dada la posicion de la partida con el identificador id, la busca y la borra
		--lista.cont;							//Para borrar intercambia con el último y este se elimina
		return true;
	}
	return false;
}

struct ordFecha{
	bool operator()(tPartida * elemento, tPartida * elementoarray){
		return elemento->fin > elementoarray->fin;
	}
};

struct ordTurno{
	string nombre;
	ordTurno(string N) : nombre(N){}
	bool operator()(tPartida * elemento, tPartida * elementoarray){
		bool cond = turno(*elemento, nombre);
		if (cond == turno(*elementoarray, nombre)){			//Llama a turno con ambas partidas, 									
			return ordFecha()(elemento, elementoarray);		//y en caso de coincidir en el turno, ordena por fecha
		}
		return cond;
	}
};


//Busqueda por insercion, que se emplea tanto para ordenar por turno como por fecha
template <typename Comp = less<T>>
void ordenarInsercion(tListaAccesoPartidas & lista, Comp ord = Comp()) {
	size_t N = lista.cont;
	for (size_t i = 1; i < N; ++i) {
		tPartida * elemento = lista.lista[i];
		size_t j = i;
		while (j > 0 && ord(elemento, lista.lista[j - 1])) {
			lista.lista[j] = lista.lista[j - 1];
			--j;
		}
		lista.lista[j] = elemento;
	}
}


void ordenar_Fecha(tListaAccesoPartidas & lista){
	ordenarInsercion(lista, ordFecha());
}

void ordenar_Turno(tListaAccesoPartidas & lista, string & nombre){
	ordenarInsercion(lista, ordTurno (nombre));
}

bool vacio(tListaAccesoPartidas & lista){
	return lista.cont == 0;
}
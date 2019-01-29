//Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaPartidas.h"
#include "checkML.h"

void iniciar(tListaPartidas & listapartidas, int tam){
	listapartidas.partidas = new tPartida*[tam*2];
	listapartidas.cont = 0;
	listapartidas.capacidad = tam*2;
}

void eliminar(tListaPartidas & listapartidas){
	for (int i = 0; i < listapartidas.cont; ++i){
		delete listapartidas.partidas[i];
	}
	delete[]listapartidas.partidas;
}


void cambiarcontador(fstream & archivo, int cont){
	int num;
	archivo.seekg(0, ios::beg); // movemos el cursor al inicio
	archivo >> num; // leemos el entero
	archivo.seekp(0, ios::beg); // movemos el cursor al inicio
	archivo << setw(11) << num + cont; // escribimos ocupando 11 caracteres
}

void guardar(tListaPartidas  & partidas, ofstream & archivo, int cont){
	ofstream archivohistorico;
	archivohistorico.open("historico.txt", ios::app);
	archivo << partidas.cont-cont <<'\n';		//Se escribe el tamaño del vector para despues conocer el numero de partidas
	for (int i = 0; i < partidas.cont; ++i){
		if (partidas.partidas[i]->estado == Terminada) guardar(*(partidas.partidas[i]), archivohistorico);
		else guardar(*(partidas.partidas[i]), archivo);
	}
	archivohistorico.close();
	fstream modificarcont("historico.txt", ios::in | ios::out);
	cambiarcontador(modificarcont, cont);
	modificarcont.close();
}

void apagar(tListaPartidas & lista, ofstream & archivo, int cont){
	guardar(lista, archivo, cont);
	eliminar(lista);
}


void redimensionar(tListaPartidas & listapartidas){
	int nuevacap;
	nuevacap = (listapartidas.capacidad * 3) / 2 + 1;
	tPartida ** aux = new tPartida*[nuevacap];
	for (int i = 0; i < listapartidas.cont; ++i){
		aux[i] = listapartidas.partidas[i];
	}
	delete[] listapartidas.partidas;
	listapartidas.partidas = aux;
	listapartidas.capacidad = nuevacap;
}

bool cargar(tListaPartidas & partidas, ifstream & archivo){
	int tam;
	bool cond = true;
	archivo >> tam;
	iniciar(partidas, tam);   //Se modifica el tamaño del vector al que indica el archivo (nº de partidas)
	for (int i = 0; i < tam && cond; ++i){
		partidas.partidas[i] = new tPartida;
		cond = cargar(*(partidas.partidas[i]), archivo);
	}
	partidas.cont = tam;
	return !archivo.fail()&&cond;
}

void insertar(tListaPartidas & listapartidas, tPartida const& partida){
	if (listapartidas.cont == listapartidas.capacidad){
		redimensionar(listapartidas);
	}
	listapartidas.partidas[listapartidas.cont] = new tPartida;
	*(listapartidas.partidas[listapartidas.cont]) = partida;
	++listapartidas.cont;
}


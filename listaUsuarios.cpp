 //Alejandro Hernández Cerezo y Jose Manuel Pinto Lozano
#include "listaUsuarios.h"
#include "checkML.h"

void iniciar(tListaUsuarios & listausuarios, int tam){
	listausuarios.usuarios = new tUsuario*[2*tam];
	listausuarios.cont = 0;
	listausuarios.capacidad = tam*2;
}

void eliminar(tListaUsuarios & listausuarios){
	for (int i = 0; i < listausuarios.cont; ++i){
		delete listausuarios.usuarios[i];
	}
	delete[]listausuarios.usuarios;
}

void redimensionar(tListaUsuarios & listausuarios){
	int nuevacap;
	nuevacap = (listausuarios.capacidad * 3) / 2 + 1;
	tUsuario ** aux = new tUsuario*[nuevacap];
	for (int i = 0; i < listausuarios.cont; ++i){
		aux[i] = listausuarios.usuarios[i];
	}
	delete[] listausuarios.usuarios;
	listausuarios.usuarios = aux;
	listausuarios.capacidad = nuevacap;
}

void insertarnew(tListaUsuarios & listausuarios, tUsuario const& usuario){
	if (listausuarios.cont == listausuarios.capacidad){
		redimensionar(listausuarios);
	}
	listausuarios.usuarios[listausuarios.cont] = new tUsuario;
	*(listausuarios.usuarios[listausuarios.cont]) = usuario;
	++listausuarios.cont;
}

//Funcion auxiliar que desplaza a los usuarios del vector cuando se añade un nuevo usuario
void desplazar(tListaUsuarios & usuarios, int & pos){
	insertarnew(usuarios, tUsuario());					/*Se añade variable vacia y despues se desplaza a la posicion
														en la que se debe encontrar el usuario*/
	tUsuario * puntero = usuarios.usuarios[usuarios.cont-1];
	int i = usuarios.cont - 1;
	for (; i > pos; --i){
		usuarios.usuarios[i] = usuarios.usuarios[i - 1];
	}
	usuarios.usuarios[i] = puntero;
}

void guardar(tListaUsuarios & usuarios, ofstream & archivo){
	int tam = usuarios.cont;
	archivo << tam << '\n';
	for (int i = 0; i < usuarios.cont; ++i){
		guardar(*(usuarios.usuarios[i]), archivo);
	}
}

void apagar(tListaUsuarios & usuarios, ofstream & archivo){
	guardar(usuarios, archivo);
	eliminar(usuarios);
}


bool cargar(tListaUsuarios & usuarios, ifstream & archivo){
	tUsuario usuario;
	int tam;
	int i = 0;
	archivo >> tam;
	iniciar(usuarios, tam);
	while (i < tam && cargar(usuario, archivo)) insertarnew(usuarios, usuario), ++i;
	return !archivo.fail() && i == tam;
}

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int & pos){
	int inicio = 0, fin = usuarios.cont, mitad;
	bool encontrado = false;
	while (inicio < fin && !encontrado){			//Se realiza busqueda binaria
		mitad = (inicio + fin - 1) / 2;		//Se actualiza la posicon mitad en funcion de su relacion de orden con el elemento buscado
		if ((usuarios.usuarios[mitad])->identificador > idUser) fin = mitad;
		else if ((usuarios.usuarios[mitad])->identificador < idUser) inicio = mitad + 1;
		else encontrado = true, pos = mitad;
	}
	if (!encontrado){
		pos = inicio;
		return false;
	}
	else return true;
}

bool insertar(tListaUsuarios & usuarios, tUsuario & usuario, int & pos){
	if (!buscar(usuarios, usuario.identificador, pos)){			//En caso de no existir se inserta el nuevo usuario
		desplazar(usuarios, pos);
		*usuarios.usuarios[pos] = usuario;
		return true;
	}
	else return false;
}



bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){
	int i = 0; bool encontrado = false;
	while (i < usuarios.cont && !encontrado){
		if ((usuarios.usuarios[i])->espera && (usuarios.usuarios[i])->dificultad == nivel){
			pos = i;
			encontrado = true;
		}
		++i;
	}
	return encontrado;
}




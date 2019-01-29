//Alejandro Hern�ndez Cerezo y Jose Manuel Pinto Lozano
#include "gestor.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
#include <Windows.h>
using namespace std;

//Funcion que convierte un string a mayusculas
void convertirmayusculas(string & nombre){
	for (unsigned int i = 0; i < nombre.size(); ++i)
		nombre[i] = toupper(nombre[i]);
}

//Funcion que regula la respuesta del usuario, devolviendo true en caso de SI y false en caso contrario
bool seleccionareleccion(){
	bool cond = false;
	string eleccion;
	cin >> eleccion;
	convertirmayusculas(eleccion);
	while (eleccion != "SI" && eleccion != "NO"){
		cout << "Por favor introduzca \"SI\" o \"NO\":";
		cin >> eleccion;
		convertirmayusculas(eleccion);
	}
	if (eleccion == "SI") cond = true;
	return cond;
}

//Comprueba que la opcion seleccionada es valida
int introduciropcion(int limiteinferior, int limitesuperior){
	int opcion;
	cin >> opcion;
	while (cin.fail() || opcion<limiteinferior || opcion>limitesuperior){
		cin.clear(); cin.sync();
		cout << "Opci�n incorrecta, por favor introduzca una nueva:";
		cin >> opcion;
	}
	return opcion;
}

//Funcion que lee el movimiento seleccionado por el jugador
void leerJugada(int & col){
	cout << "Introduzca columna en la que desea insertar una ficha:\n";
	col= introduciropcion(1, COLS);
	--col;
}

//Funcion que muestra por pantalla todas
void menuAcabadas(tGestor & gestor){
	int opcion;
	do{
		system("cls");
		int cont = partidasAcabadas(gestor);
		cout << "Seleccione una partida de 1 a " << cont << "(0 para salir): \n";
		mostrarAcabadas(gestor);
		opcion = introduciropcion(0, cont);
		--opcion;
		if(opcion != -1) mostrarStats(gestor, opcion), system("pause");
	} while (opcion != -1);
}


//Menu de una partida, del cual se sale si se selecciona la opcion 0 o la partida se termina
void menuPartida(tGestor & gestor){
	int opcion,col;
	do{
		system ("cls");
		mostrarPartida(gestor);
		cout << "1.- Jugar\n";
		cout << "2.- Abandonar\n";
		cout << "0.- Salir\n";
		cout << "Introduzca una opci�n:";
		opcion = introduciropcion( 0, 2);
		switch (opcion){
		case 1:	if (esSuTurno(gestor)){
			leerJugada(col);
			jugarPartida(gestor, col);
		}
		else cout << "�No es tu turno!\n"; break;
		case 2: abandonarPartida(gestor);
			cout << "Usted ha abandonado la partida.";
			system("pause");
			break;
		case 0:; break;
		}
	} while (opcion != 0 && sigue(gestor));
}

//Funcion que permite la eleccion de una de las partidas en curso
void elegirPartida(tGestor & gestor){
	int indice;
	if (vacia(gestor)){
		cout << "No dispones de partidas en curso en este momento.\n";
		system("pause");
	}
	else{
		cout << "Introduza el �ndice de una partida(1 a " << partidasUsuario(gestor)<< "):";
		indice = introduciropcion(1, partidasUsuario(gestor));
		--indice;
		apuntaPartida(gestor, indice);
		menuPartida(gestor);
	}
}

//Funcion que muestra por pantalla las partidas en curso de un jugador
void mostrarPartidasEnCurso(tGestor & gestor){
	cout <<left<<setw(23)<< "#  T  Jugador 1" << left <<setw(17)<< "Jugador 2"<< "Fecha\n";
	cout << setw(49) <<setfill('-')<<"-"<<'\n';
	int tam = partidasUsuario(gestor);
	for (unsigned int i = 0; i < tam; ++i){
		cout << i+1 << " " << cabecera(gestor, i)<<'\n';
	}
	cout << "\n\n\n";
}

//Menu que permite al jugador gestionar sus partidas
void menuUsuario(tGestor & gestor){
	int opcion;
	if (!generarAcabadas(gestor)) cout << "No se ha podido cargar el archivo historico\n";
	do{
		reiniciar(gestor);
		generarAccesos(gestor);
		system("cls");
		cout << "MENU USUARIO:\n\n";
		mostrarPartidasEnCurso(gestor);
		cout << setfill(' ') << setw(3) << "1.- Ver partida\n";
		cout << setfill(' ') << setw(3) << "2.- Nueva partida\n";
		cout << setfill(' ') << setw(3) << "3.- Partidas por actualizaci�n\n";
		cout << setfill(' ') << setw(3) << "4.- Partidas por turno y fecha\n";
		cout << setfill(' ') << setw(3) << "5.- Estad�sticas de partidas\n";
		cout << setfill(' ') << setw(3) << "0.- Salir\n";
		cout << setfill(' ') << setw(3) << "Elija una opci�n:";
		opcion = introduciropcion(0, 5);
		switch (opcion){
		case 1:elegirPartida(gestor);break;
		case 2: if (nuevaPartida(gestor)) {
					cout << "Se ha creado una nueva partida\n";
					Sleep(800);
					menuPartida(gestor); 
				}
				else if (llena(gestor)) cout << "Ha superado el limite de partidas en curso\n", Sleep(800);
				else cout << "Se encuentra en estado de espera\n", Sleep(800);
				break;
		case 3:ordenar_Fecha(gestor); Sleep(700); break;
		case 4:ordenar_Turno(gestor); Sleep(700); break;
		case 5: menuAcabadas(gestor); break;
		case 0:; break;
		}
	} while (opcion != 0);
	reiniciar(gestor);
	terminarAcabadas(gestor);
}

//Funcion que muestra por pantalla los avisos y el perfil del usuario
void mostrarDatosUsuario(tGestor & gestor){
	string avisos;
	string respuesta;
	if (tieneAvisos(gestor, avisos)){
		cout <<"\n\nTiene avisos:\n"<< avisos << "�Quiere borrar los avisos?(\"SI\" o \"NO\"):";
		if (seleccionareleccion()) limpiarAvisos(gestor);
	}
	cout<<'\n'<<resumenActividad(gestor);
	system("pause");
}

//Funcion con la que se gestiona el inicio de sesion
bool iniciarSesion(tGestor & gestor){
	string nombre, clave; char aux;
	cout << "Nombre de usuario: ";
	cin.get(aux);
	getline(cin, nombre);
	cout << "Clave: ";
	getline(cin, clave);
	return iniciarSesion(gestor, nombre, clave);
}

//Funcion que permite crear nuevos usuarios
bool Crearcuenta(tGestor & gestor){
	string usuario, clave;
	cout << "Introduzca nuevo usuario: \n";
	cin >> usuario;
	cout << "Introduzca contrase�a: \n";
	cin >> clave;
	if (crearCuenta(gestor, usuario, clave)) return true;
	else return false;
}

//Menu principal del programa, que permite iniciar sesion o crear una nueva cuenta
void menuRegistro(tGestor & gestor){
	int opcion;
	bool iniciar = false;
	do{
		system ("cls");
		cout << "Men� Registro:\n";
		cout << "1.- Iniciar Sesi�n.\n";
		cout << "2.- Registrarse.\n";
		cout << "0.- Salir.\n";
		cout << "Elija una opci�n: ";
		opcion = introduciropcion(0, 2);
		switch (opcion){
		case 0:; break;
		case 1: if (!iniciarSesion(gestor)){ 
				cout << "Contrase�a incorrecta o usuario inv�lido\n";
				system ("pause");
				}
				else{ 
					Sleep(800);
					mostrarDatosUsuario(gestor);
					Sleep(800);
					menuUsuario(gestor);
					}
				break;
		case 2: while (!Crearcuenta(gestor)){ cout << "El usuario introducido ya existe, por favor introduzca otro\n"; }
				cout << "Se ha registrado correctamente\n";
				system ("pause");
				break;
		}
	} while (opcion != 0);
}

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	system("chcp 1252");
	tGestor gestor;
	if (arrancar(gestor)){
		menuRegistro(gestor);
		apagar(gestor);
	}
	return 0;
}
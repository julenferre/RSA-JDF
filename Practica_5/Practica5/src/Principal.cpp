/** 
*	Programa principal para navegacion
*/

#include "ControlRobot.h"
#include "Laberinto.h"

using namespace std;


void recorrerLaberintoManual(){
	
	bool fin = false;

	Laberinto *maze;
	maze = new Laberinto("./xml/Laberinto.xml");
	maze->imprimirLaberinto();

	string teclas;
	while(!fin){
		cin >> teclas;

		char orientacion;
		int x,y;

		if(teclas.compare("n")==0){
			maze->orientarRobotNorte();
		}else if(teclas.compare("s")==0){
			maze->orientarRobotSur();
		}else if(teclas.compare("e")==0){
			maze->orientarRobotEste();
		}else if(teclas.compare("w")==0){
			maze->orientarRobotOeste();
		}else if(teclas.compare("g")==0){

			maze->getPosRobot(&x,&y,&orientacion);

			switch(orientacion){
			case NORTE:
				if(maze->esNorteLibre()){
					maze->avanzaNorte();
				}else{
					cout << "No existe un camino en la actual orientacion "<< endl;
				}
				break;
			case SUR:
				if(maze->esSurLibre()){
					maze->avanzaSur();
				}else{
					cout << "No existe un camino en la actual orientacion "<< endl;
				}
				break;
			case ESTE:
				if(maze->esEsteLibre()){
					maze->avanzaEste();
				}else{
					cout << "No existe un camino en la actual orientacion "<< endl;
				}
				break;
			case OESTE:
				if(maze->esOesteLibre()){
					maze->avanzaOeste();
				}else{
					cout << "No existe un camino en la actual orientacion "<< endl;
				}
				break;
			default:
				break;
			}
		}else if(teclas.compare("salir")==0){
			fin = true;
		}else if(teclas.compare("imprimir")==0){
			maze->imprimirCaminoRobot();
		}else{
			cout<<"comando: "<<teclas<<" no reconocido"<<endl;
		}

		maze->getPosRobot(&x,&y,&orientacion);

		if(x==5 & y==5){
			cout << "Has llegado al otro extremo del laberinto!"<<endl;
			fin = true;
		}
		maze->imprimirLaberinto();
	}
	
	maze->imprimirCaminoRobot();
	
	cout << "finaliza el programa" << endl;
}

void recorrerCamino(camino *solucion, Laberinto *maze) {
    ControlRobot robot;
    robot.inicializacion();
    char orientacion;
    int x, y, resultado, dirChoque;

    struct camino* aux = solucion;


    while (aux->siguiente != NULL) {
        dirChoque=0;
        cout << "Nodo Actual => X: " << aux->nodo_actual->x << " Y: " << aux->nodo_actual->y << endl;

        if (aux->nodo_actual->x == aux->siguiente->nodo_actual->x && aux->nodo_actual->y == aux->siguiente->nodo_actual->y + 1) {
            maze->orientarRobotNorte();
        } else if (aux->nodo_actual->x == aux->siguiente->nodo_actual->x && aux->nodo_actual->y == aux->siguiente->nodo_actual->y - 1) {
            maze->orientarRobotSur();
        } else if (aux->nodo_actual->x == aux->siguiente->nodo_actual->x - 1 && aux->nodo_actual->y == aux->siguiente->nodo_actual->y) {
            maze->orientarRobotEste();
        } else if (aux->nodo_actual->x == aux->siguiente->nodo_actual->x + 1 && aux->nodo_actual->y == aux->siguiente->nodo_actual->y) {
            maze->orientarRobotOeste();
        }

        maze->getPosRobot(&x, &y, &orientacion);

        switch (orientacion) {
            case NORTE:
                if (maze->esNorteLibre()) {
                    resultado = maze->avanzaNorte();
                    if (resultado == 0) {
                        maze->avanzaSur();
                        dirChoque=NORTE;
                    }
                } else {
                    cout << "No existe un camino en la actual orientacion " << endl;
                }
                break;
            case SUR:
                if (maze->esSurLibre()) {
                    resultado = maze->avanzaSur();
                    if (resultado == 0) {
                        maze->avanzaNorte();
                        dirChoque=SUR;
                    }
                } else {
                    cout << "No existe un camino en la actual orientacion " << endl;
                }
                break;
            case ESTE:
                if (maze->esEsteLibre()) {
                    resultado = maze->avanzaEste();
                    if (resultado == 0) {
                        maze->avanzaOeste();
                        dirChoque=ESTE;
                    }
                } else {
                    cout << "No existe un camino en la actual orientacion " << endl;
                }
                break;
            case OESTE:
                if (maze->esOesteLibre()) {
                    resultado = maze->avanzaOeste();
                    if (resultado == 0) {
                        maze->avanzaEste();
                        dirChoque=OESTE;
                    }
                } else {
                    cout << "No existe un camino en la actual orientacion " << endl;
                }
                break;
            default:
                break;
        }

        maze->getPosRobot(&x, &y, &orientacion);
        
        if(resultado == 0){
            maze->orientarRobotSur();
            maze->quitarCalle(&aux->nodo_actual, dirChoque);
            camino *solucion = maze->encontrarCamino(x,y,5,5);
            recorrerCamino(solucion, maze);
            goto terminar;
        }
        
        if (x == 5 & y == 5) {
            cout << "Has llegado al otro extremo del laberinto!" << endl;
        }
        maze->imprimirLaberinto();
        aux = aux->siguiente;
    }
    
    maze->imprimirCaminoRobot();
    robot.finalizacion();
    
    terminar:   
    cout << "Terminado" << endl;
}



int main(int argc, char * argv[])
{
//	recorrerLaberintoManual();
	
	
	Laberinto *maze = new Laberinto("./xml/Laberinto_Ext.xml");
	
	// Generamos una solucion entre dos puntos origen [0,0] y destino [5,5]
	camino *solucion = maze->encontrarCamino(0,0,5,5); 
	
	ControlRobot robot;
	
	//robot.cargarMapa(maze);
	recorrerCamino(solucion, maze);
        
	
//	robot.inicializacion();
//	
//	while(!robot.condicionSalida()){ // <-- Mientras no hayamos completado el "camino"
//		robot.leerSensores();		// <-- Detectamos cruces
//		robot.logicaEstados();		// <-- Decidimos que hacer en cada cruce
//		robot.moverActuadores();	// <-- Nos orientamos en el laberinto
//		robot.imprimirInfo();
//	}
//
	robot.finalizacion();
	
	return 0;
}



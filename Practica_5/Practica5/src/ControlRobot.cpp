// ControlRobot .cpp

#include "ControlRobot.h"
#include "Laberinto.h"
#include<iostream>
#include<time.h>
#include<chrono>
#include<ctime>

using namespace std;

// Estados de la l�gica
#define INICIAL 3
#define BUSCA_I 2
#define BUSCA_D 1
#define SIGUE 0

// Estados para los motores
#define GIRAR_DERECHA 		0
#define GIRAR_IZQUIERDA		1
#define RECTO			2
#define PARADO			3

#define DUCT_TAPE_FL(value) (value < 600)
#define DUCT_TAPE_FR(value) (value < 500)
#define DUCT_TAPE_L(value) (value < 450)
#define DUCT_TAPE_R(value) (value < 650)

#define VEL_AVANCE 200
#define VEL_GIRO 80
#define VEL_ROTACION 80
int vel_giro2 = VEL_GIRO;
int distancia_total = 0;
clock_t start;

/**
*	Constructora objeto ControlRobot
*/
ControlRobot::ControlRobot(void)
{
	
}

/**
*	Destructora objeto ControlRobot
*/
ControlRobot::~ControlRobot(void)
{
	
}

/**
* 	Prepara la conexi�n IRobotConnection e inicializa todas
*	las variables que necesitemos en el programa
*/
void ControlRobot::inicializacion(void)
{
	
	int COM_port;
	char puerto[30];
	
	// Solicitamos el puerto COM por entrada est�ndar
	//cout << "Puerto COM: ";
	//cin >> COM_port;
	//sprintf(puerto, "COM%d",COM_port);
	
	sprintf(puerto,"/dev/ttyUSB0");


	robot = new IRobotConnection(puerto);
	
	// Iniciamos la conexi�n
	cout << "Connecting... ";
	robot->connect();
	cout << "Done!!\n" << endl;
	
	// Comando 128 start
	robot->start();
	delay(500); // Esperamos medio segundo a que cambie de modo

	// Comando 132 modo full
	robot->full();
	delay(500); // Esperamos medio segundo a que cambie de modo
	
	estado_actual = INICIAL;
	estado_anterior = INICIAL;
	motores = PARADO;
	
        int s = robot->updateSensor(iRobotSensors::BUTTONS);
        while(s!=1) {
            s = robot->updateSensor(iRobotSensors::BUTTONS);
            delay(100);
        }
        robot->updateSensor(iRobotSensors::DISTANCE);
        start = clock();
}

/**
 *      Se carga el mapa con la ruta más rápida para recorrerlo
 */
camino ControlRobot::cargarMapa(Laberinto *maze) 
{
    return Laberinto.encontrarCamino(0, 0, 5, 5);
}

/**
 *      Se recorre el camino más rápido previamente calculado
 *  
 */
void ControlRobot::recorrerCamino(camino *solucion) 
{
    
}

/**
* 	Calcula si se han dado las condiciones necesarias para terminar el programa
*	return bool: 
*		- true para terminar
*		- false para continuar al menos un ciclo m�s
*/
bool ControlRobot::condicionSalida()
{
        sensores.advance_button = robot->updateSensor(iRobotSensors::BUTTONS);
        if(sensores.advance_button == 4)
            return true; // nos salimos del bucle al pulsar el boton de avance
        else
            return false;// nos mantenemos siempre dentro del bucle*/
}

/**
*	Obtiene y trata la informaci�n de los sensores relevantes al programa, 
*	para ello usa la struct Sensores_iCreate sensores;
*/
void ControlRobot::leerSensores()
{
        sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL );
        sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL );
        
	// Ajustamos el valor al m�ximo permitido por la especificaci�n OI
	if(sensores.front_left>4095) sensores.front_left=4095;
        if(sensores.front_right>4095) sensores.front_right=4095;        

        
	sensores.fl = DUCT_TAPE_FL(sensores.front_left);
        sensores.fr = DUCT_TAPE_FR(sensores.front_right);        
}

/**
*	Contiene la l�gica del programa
*/
void ControlRobot::logicaEstados()
{		
	// Actualizamos los estados: 
	estado_anterior = estado_actual;		
	
        if(sensores.fl) {
            estado_actual = BUSCA_I;
        } else if(sensores.fr){
            estado_actual = BUSCA_D;
        } else {
            estado_actual = SIGUE;
        }
	
	// Se decide que hacer con los parametros del robot
	switch(estado_actual){	
		case SIGUE:
			motores = RECTO;
			break;		
		case BUSCA_D:
                    if (estado_anterior = RECTO) {
                        vel_giro2 = 100;
                    }
                        motores = GIRAR_DERECHA;
			break;
                case BUSCA_I:
                    if (estado_anterior = RECTO) {
                        vel_giro2 = 100;
                    }
                        motores = GIRAR_IZQUIERDA;
			break;
		default:
			break;
	}
	
}

/**
*  	Activa los actuadores correspondientes en funci�n de lo decidido 
*	en la l�gica del programa 
*/
void ControlRobot::moverActuadores()
{
    int vel_avance = VEL_AVANCE;
    int vel_giro = vel_giro2;
    switch(motores){
		case PARADO:
			actuadores.vel_der = 0;
			actuadores.vel_izq = 0;
			break;
		case RECTO:
			actuadores.vel_der = vel_avance;
			actuadores.vel_izq = vel_avance;
			robot->leds( 3, 90,200 );
			break;
		case GIRAR_DERECHA:
			actuadores.vel_der = vel_giro/5;
			actuadores.vel_izq = vel_giro*2;
			robot->leds( 3, 0,0 );
			break;
                case GIRAR_IZQUIERDA:
			actuadores.vel_der = vel_giro*2;
			actuadores.vel_izq = vel_giro/5;
			robot->leds( 3, 0,0 );
			break;
		default:
			break;
	}
	
	robot->driveDirect(actuadores.vel_der, actuadores.vel_izq);
	vel_giro2 = VEL_GIRO;
}

/**
*	Muestra informaci�n relevante al usuario
*/
void ControlRobot::imprimirInfo(void)
{
	char estado[20];
	switch(estado_actual){
		case INICIAL : 	sprintf(estado,"INICIAL");	break;
		case SIGUE : 	sprintf(estado,"SIGUE");	break;
		case BUSCA_D : 	sprintf(estado,"BUSCA_D");	break;
                case BUSCA_I : 	sprintf(estado,"BUSCA_I");	break;
	}
	
	printf("Estado: %s ",estado);
	printf(": %s ", sensores.fl ? "true" : "false");
	printf(" Valor FL: %d",	sensores.front_left);
	printf("\n");
        printf(": %s ", sensores.fr ? "true" : "false");
        printf("\t Valor FD: %d",	sensores.front_right);
        printf("\n");

}

/**
*	Cierra conexiones abiertas
*/
void ControlRobot::finalizacion(void)
{
        robot->driveDirect(0,0);
        distancia_total += robot->updateSensor(iRobotSensors::DISTANCE);
        start = clock() - start ;
        cout << "Distancia total : " << +distancia_total << endl;
        float total = (((float)start)*2/CLOCKS_PER_SEC)*100;
        int t_m = total/60;
        int t_s = total-(t_m*60);
        cout << "Tiempo total : " << +t_m << " min y " << +t_s << " s." << endl;
	robot->disconnect();
	delete robot;
}

void ControlRobot::avanzar() {
    sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
    sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
    
    sensores.fl = DUCT_TAPE_FL(sensores.front_left);
    sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    
    robot->driveDirect(VEL_AVANCE, VEL_AVANCE);
    /*bool corrigiendo = false;
    while (!(sensores.fl && sensores.fr) && !corrigiendo) {        
        if(sensores.fl && !sensores.fr) {
            robot->driveDirect(VEL_AVANCE, -VEL_AVANCE);
            corrigiendo = true;
        } else if (sensores.fr && !sensores.fl) {
            robot->driveDirect(-VEL_AVANCE, VEL_AVANCE);
            corrigiendo = true;
        } else {
            robot->driveDirect(VEL_AVANCE, VEL_AVANCE);
            corrigiendo = false;
        }
        sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
        sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);

        sensores.fl = DUCT_TAPE_FL(sensores.front_left);
        sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    }*/
    while (!(sensores.fl && sensores.fr)) {        
        if(sensores.fl && !sensores.fr) {
            robot->driveDirect(VEL_AVANCE, -VEL_AVANCE);            
        } else if (sensores.fr && !sensores.fl) {
            robot->driveDirect(-VEL_AVANCE, VEL_AVANCE);            
        } else {
            robot->driveDirect(VEL_AVANCE, VEL_AVANCE);            
        }
        sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
        sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
        
        sensores.fl = DUCT_TAPE_FL(sensores.front_left);
        sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    }
    robot->driveDirect(VEL_AVANCE, VEL_AVANCE);
    robot->updateSensor(iRobotSensors::DISTANCE);
    int dr = 0;
    while(dr < 150) {
        dr += robot->updateSensor(iRobotSensors::DISTANCE);
    }
    robot->driveDirect(0, 0);
}

void ControlRobot::girarD() {
    int ar = 0;
    int ang = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    
    robot->driveDirect(-VEL_ROTACION, VEL_ROTACION);
    
    while(ar < 50) {
        ang = robot->updateSensor(iRobotSensors::ANGLE);
        if(ang != 0)
            ar += (65536 - ang);
    }
    
    sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
    sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    
    while(!sensores.fr) {
        sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
        sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    }
    ar = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    while(ar < 10) {
        ang = robot->updateSensor(iRobotSensors::ANGLE);
        if(ang != 0)
            ar += (65536 - ang);
    }
    robot->driveDirect(0,0);
}

void ControlRobot::girarI() {
    int ar = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    
    robot->driveDirect(VEL_ROTACION, -VEL_ROTACION);    
    
    while(ar < 50) {
        ar += robot->updateSensor(iRobotSensors::ANGLE);
    }
    
    sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
    sensores.fl = DUCT_TAPE_FL(sensores.front_left);
    
    while(!sensores.fl) {
        sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
        sensores.fl = DUCT_TAPE_FL(sensores.front_left);
    }
    ar = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    while(ar < 10) {
        ar += robot->updateSensor(iRobotSensors::ANGLE);
    }
    robot->driveDirect(0,0);
}

void ControlRobot::vuelta() {
    int ar = 0;
    int ang = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    
    robot->driveDirect(-VEL_ROTACION, VEL_ROTACION);
    
    while(ar < 140) {
        ang = robot->updateSensor(iRobotSensors::ANGLE);
        if(ang != 0)
            ar += (65536 - ang);
    }
    
    sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
    sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    
    while(!sensores.fr) {
        sensores.front_right = robot->updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
        sensores.fr = DUCT_TAPE_FR(sensores.front_right);
    }
    ar = 0;
    robot->updateSensor(iRobotSensors::ANGLE);
    while(ar < 10) {
        ang = robot->updateSensor(iRobotSensors::ANGLE);
        if(ang != 0)
            ar += (65536 - ang);
    }
    robot->driveDirect(0,0);
}
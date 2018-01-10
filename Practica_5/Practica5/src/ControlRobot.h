// Control Robot.h
#pragma once

#include "IRobotConnection.h"
#include <iostream>


/**
*	 Definici�n de la clase ControlRobot
*/
class ControlRobot {
	
    private:
    	
    	IRobotConnection *robot;
    	
    	struct Sensores_iCreate {
    		// variables para almacenar informaci�n del 
    		// sensor de acantilado frontal izquierdo
			unsigned int front_left, front_right, left, right, advance_button, bumper;
			bool fl,fr, l, r, bp;
		};
		struct Sensores_iCreate sensores;
		
		struct Actuadores_iCreate {
			// variables para el comando Drive direct
			int vel_der;
			int vel_izq;
			// variables para el comando Drive
			int velocidad;
			int giro;
		};
		struct Actuadores_iCreate actuadores;

		char estado_actual;
		char estado_anterior;
		char motores;

    public:
    	ControlRobot(void);
		~ControlRobot(void);
                
    	void inicializacion();
        void cargarMapa();
        void recorrerCamino();
        bool condicionSalida();
    	void leerSensores();
    	void logicaEstados();
    	void moverActuadores();
        bool nodoAlcanzado();
    	void imprimirInfo();
    	void finalizacion();
        
        int avanzar();
        void girarD();
        void girarI();
        void vuelta();
};


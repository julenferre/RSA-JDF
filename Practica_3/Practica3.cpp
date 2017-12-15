/* 
* File:   Practica3.cpp
* Author: jdiez030
*
* Created on 8 de noviembre de 2017, 14:27
*/
#include "Libs/iRobot_framework/IRobotConnection.h"
#define COM "/dev/ttyUSB0"
#include <cstdlib>
#include <string.h> //Para comparacion de strings

using namespace std;

int main(int argc, char** argv) {

	int sensor_value = 0;

	// Creamos un objeto robot
	IRobotConnection robot(COM);

	// Activamos el Verbose Mode
	//robot.setVerboseMode(true);
	robot.setVerboseMode(false);

	// Iniciamos la conexion...
	cout << "Connecting... ";
	if(robot.connect()!=1){ 
		cout << "Error\n" << endl;
		return EXIT_FAILURE;
	}
	cout << "Done!\n" << endl;
	//delay(500);

	// Comando 128 start
	cout << "Send start" << endl;
	robot.start();
	//delay(500);

	// Comando 132 modo full
	//cout << "Send Full mode" << endl;
	robot.full();
	//delay(500);

	/*3.1. Calibración de sensores de choque y caída de ruedas (Bumps & WheelDrops)*/
	/*int i= 0;
	cout << "Comprobar el estado del sensor choque y caida de ruedas en 2 seg" << endl;
	delay(2000);
	robot.song(1,2,"64 10");
	robot.song(2,2,"80 10");
	robot.song(3,2,"100 10");
	while(i < 30){        
		sensor_value = robot.updateSensor(iRobotSensors::BUMPERS_AND_WHEELDROPS);
		cout << "Valor: " << +sensor_value << endl;
		if (sensor_value != 0 && sensor_value < 4) {
			robot.playSong(sensor_value);
		}

		if(sensor_value == 4) {
			robot.leds(0, 0, 255);
		} else if (sensor_value == 8) {
			robot.leds(2, 0, 255);
		} else if (sensor_value == 16) {
			robot.leds(8, 0, 255);
		} else{
			robot.leds(0, 0, 0);
		} 
		i++;
		delay(1000);
	}*/

	/* 3.2. Calibración de sensores de barranco ( Cliffs Signal )*/
	/*int i = 0, media = 0;

	while(i<5) {
		sensor_value = robot.updateSensor(iRobotSensors::CLIFFLEFTSIGNAL);
		cout << "Valor LEFT: " << +sensor_value << endl;
		i++;
		media += sensor_value;
		delay(1000);
	}
	cout << "Media LEFT: " << + (media/5) << endl;
	media = 0;
	i = 0;
	delay(3000);
	while(i<5) {
		sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL);
		cout << "Valor FRONT LEFT: " << +sensor_value << endl;
		i++;
		media += sensor_value;
		delay(1000);
	}
	cout << "Media FRONT LEFT: " << + (media/5) << endl;
	media = 0;
	i = 0;
	delay(3000);
	while(i<5) {
		sensor_value = robot.updateSensor(iRobotSensors::CLIFFFRONTRIGHTSIGNAL);
		cout << "Valor FRONT RIGHT: " << +sensor_value << endl;
		i++;
		media += sensor_value;
		delay(1000);
	}
	cout << "Media FRONT RIGHT: " << + (media/5) << endl;
	media = 0;
	i = 0;
	delay(3000);
	while(i<5) {
		sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);
		cout << "Valor RIGHT: " << +sensor_value << endl;
		i++;
		media += sensor_value;
		delay(1000);
	}
	cout << "Media RIGHT: " << + (media/5) << endl;*/


	/*3.3. Calibración del sensor de distancia a la pared (Wall):*/
	/*int i = 0;    
	while(i < 10) {
		sensor_value = robot.updateSensor(iRobotSensors::WALL);
		cout << "Valor WALL: " << +sensor_value << endl;
		i+;
		delay(1000);
	}*/

	/*3.4. Calibración de sensores de distancia para Dead-Reckoning*/
	int velAvance = 150;
	int velGiro = 150;
	int distancia = atoi(argv[1]);
	char* direccion = argv[2]; 	//d = derecha; i = izquierda

	int i = 0;
	while (i < 4) {	//4 giros	
		//waitDistance() es uno de los métodos críticos; se intentará hacerlo de otro modo
		robot.driveDirect(velAvance, velAvance); //avanzar
		int dr = 0;	//distancia recorrida
		robot.updateSensor(iRobotSensors::DISTANCE);		
		while (dr < distancia) { //hasta recorrer la distancia...
			dr += robot.updateSensor(iRobotSensors::DISTANCE);
			cout << "Valor DISTANCE: " << +dr << endl;
		}
		int ar = 0;
		int ang = 0;
		robot.updateSensoruierd(iRobotSensors::ANGLE);
		if(strcmp(direccion,"d")==0){ //derecha
			robot.driveDirect(-velGiro, velGiro); //girar hacia la derecha                        
			while (ar < 90) { //hasta girar del todo
				//65536	 = 2^16 (16 bits) // Al girar a la derecha, el sensor de angle devuelve 65534
				ang = robot.updateSensoruierd(iRobotSensors::ANGLE);
				ar += (65536 - ang);
				cout << "Valor acumulado: " << +ar << endl;
			}
		} else { //izquierda
			robot.driveDirect(velGiro, -velGiro); //girar hacia la izquierda
			while (ar < 90) { //hasta girar del todo
				ar += robot.updateSensor(iRobotSensors::ANGLE);
				cout << "Valor ANGLE: " << +ar << endl;
			}
		}
		
		i++;
	}

	robot.driveDirect(0, 0); //parar

	return EXIT_SUCCESS;
}

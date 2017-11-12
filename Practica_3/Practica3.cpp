/* 
 * File:   Practica3.cpp
 * Author: jdiez030
 *
 * Created on 8 de noviembre de 2017, 14:27
 */
#include "Libs/iRobot_framework/IRobotConnection.h"
#define COM "/dev/ttyUSB0"
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {

    int sensor_value = 0;

    // Creamos un objeto robot
    IRobotConnection robot(COM);
    
    // Activamos el Verbose Mode
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

	/* 3.1. Calibración de sensores de choque y caída de ruedas (Bumps & WheelDrops)*/
    // Comprobamos el estado del sensor BUMPERS y WHEELDROPS
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
    
    /*int i = 0;
    
	/*3.2. Calibración de sensores de barranco (Cliffs Signal):*/
    while(i<40) {
        sensor_value = robot.updateSensor(iRobotSensors::CLIFFRIGHTSIGNAL);
        cout << "Valor: " << +sensor_value << endl;
        i++;
        delay(1000);
    }*/
    
    
   /* int i = 0, media = 0;
    
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
	
    int i = 0;    
    while(i < 40) {
        sensor_value = robot.updateSensor(iRobotSensors::WALL);
        cout << "Valor WALL: " << +sensor_value << endl;
        i++;
        delay(500);
    } 
	
	/*3.4. Calibración de sensores de distancia para Dead-Reckoning*/
	int distancia = (int)argv[0];
	char direccion = argv[1]; 	//d = derecha; i = izquierda
	
	int i = 0;
	while (i < 4) {	//4 giros	
		//waitDistance() es uno de los métodos críticos; se intentará hacerlo de otro modo
		robot.driveDirect(200, 200); //avanzar
		int dr = 0;	//distancia recorrida		
		while (dr < distancia) { //hasta recorrer la distancia...
			dr += robot.updateSensor(iRobotSensors::DISTANCE);
		}
		if(direccion=='d'){
			robot.driveDirect(200, -200); //girar hacia la derecha
		} else {
			robot.driveDirect(-200, 200); //girar hacia la izquierda
		}
		int ar = 0;	//ángulo recorrido		
		while (ar < 90) { //hasta girar del todo
			dr += robot.updateSensor(iRobotSensors::ANGLE);
		}
		robot.driveDirect(0, 0); //parar
		i++;
	}
    
    return EXIT_SUCCESS;
}


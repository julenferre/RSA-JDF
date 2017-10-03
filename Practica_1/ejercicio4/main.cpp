/* 
 * File:   main.cpp
 * Author: jferrero005
 *
 * Created on 29 de septiembre de 2017, 18:11
 */

#include <cstdlib>   //Para la función system()
#include <unistd.h>  //Para la función sleep()
#include <stdio.h>   //Para la función fopen()
#include <stdlib.h>  //Para la función system()

using namespace std;
 
int main(int argc, char** argv) {
    
    FILE * f;  // Para guardar el archivo a leer
    
    char valor; // Guarda el contenido del archivo leido
    
    while (true) { //Programa infinito
        
        //Abrir el archivo cque almacena el valor del botón
        f = fopen("/sys/class/gpio/gpio15/value", "r");  

        //Guardar el valor del botón en la variable     
        valor = fgetc(f);        
        fclose(f);
        
        //Si el botón está pulsado, encender LED
        if (valor == '0') {
            system("echo 1 > /sys/class/gpio/gpio14/value");
        }
        else { //Si no, apagarlo
            system("echo 0 > /sys/class/gpio/gpio14/value");
        }
    } //while (true)   
    
    return 0;
} //int main()

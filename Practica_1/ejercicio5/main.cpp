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
    
    FILE * f;
    
    bool pulsado = false;
    bool on = false;
    
    char valor;
    
    while (true) {       
        
        f = fopen("/sys/class/gpio/gpio15/value", "r");        
        valor = fgetc(f);        
        fclose(f);
                
        // Estos IF son para evitar el cambio de valor constante
        // al mantener pulsado el botón
        if (valor == '0') {
            pulsado = true;            
        }
        
        if(valor == '1' && pulsado){
            if (on) {
                on = false;
            } else {
                on = true;
            }
            pulsado = false;
        }
        
        if (on) {
            system("echo 1 > /sys/class/gpio/gpio14/value");
        }
        else {
            system("echo 0 > /sys/class/gpio/gpio14/value");
        }
    } //while (true)    
    
    return 0;
} //int main()


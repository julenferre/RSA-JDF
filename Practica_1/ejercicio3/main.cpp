/* 
 * File:   main.cpp
 * Author: jdiez030
 *
 * Created on 27 de septiembre de 2017, 15:51
 */

#include <cstdlib>  //Para la función system()
#include <stdlib.h> //Para la función system()
#include <unistd.h> //Para la función sleep()

using namespace std;

int main(int argc, char** argv) {
    system("echo 1 > /sys/class/gpio/gpio4/value"); //Encender led
    sleep(3);								        //Esperar 3”
    system("echo 0 > /sys/class/gpio/gpio4/value"); //Apagar led
    return 0;
}
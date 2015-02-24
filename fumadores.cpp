// ********************************************************************************************
// FUMADORES
// Solución al problema de los fumadores basada en semáforos.
// Implementado en C/C++ multihebra, usando la funcionalidad de la librería POSIX
// COMPILAR: g++ -o fumadores fumadores.cpp fun_tiempo.c -lrt -lpthread -fpermissive
// OCULTAR WARNINGS -w
//
// Autor: Pedro Fernández Bosch (pedro@pedrobosch.es)
// Distemas Concurrentes y Distribuidos
// Departamento de Lenguajes y Sistemas Informáticos, Universidad de Granada
// Última modificación: 24/02/2015
// ********************************************************************************************

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>                                     // Incluye usleep(...)
#include <stdlib.h>                                     // Incluye rand(...) y srand(...)
#include "fun_tiempo.h"

using namespace std ;

const int num_fum = 3;

sem_t sem_estanquero; 		
sem_t sem_fumador[num_fum]; 
sem_t mutex_pantalla; 		

int fumar() {
    const unsigned miliseg = 100U + (rand() % 1900U) ;  // Calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
    usleep(1000U*miliseg);                              // Retraso bloqueado durante miliseg milisegundos
}

void * estanquero( void * e ) {
    while (true){
        int ing = rand() % num_fum;                     // Produce un ingrediente

        sem_wait(&mutex_pantalla);
            cout << "Ingrediente producido: " << ing << endl << flush;
        sem_post(&mutex_pantalla);

        sem_post(&sem_fumador[ing]);
        sem_wait(&sem_estanquero);
    }
    return NULL ;
}

void * fumador( void *f ) {
    while (true){
        sem_wait(&sem_fumador[(int)f]);

        sem_wait(&mutex_pantalla);
            cout << "El fumador " << (int)f << " puede fumar" << endl << flush;
        sem_post(&mutex_pantalla);

        sem_post(&sem_estanquero);
        fumar();
    }
    return NULL ;
}

int main(int argc, char **argv) {
    struct timespec inicio = ahora() ;                  // Calcular tiempo de inicio	

    sem_init(&sem_estanquero,0,0);
    sem_init(&sem_fumador[num_fum], 0,0);
    sem_init(&mutex_pantalla,0,1);

    pthread_t hebras[1+num_fum];

    pthread_create(&(hebras[0]), NULL, estanquero, NULL);
    for(unsigned i=0; i < num_fum; i++)
        pthread_create(&(hebras[i+1]), NULL, fumador, (void *) i);

    for(unsigned i=0; i < 2; ++i)
        pthread_join(hebras[i], NULL);

    sem_destroy(&sem_estanquero);
    sem_destroy(&sem_fumador[num_fum]);
    sem_destroy(&mutex_pantalla);

    struct timespec fin = ahora();                      // Calcular tiempo de fin
    cout << "Tiempo empleado == " << duracion(&inicio, &fin) << " segundos" << endl; // Tiempo TOTAL
}
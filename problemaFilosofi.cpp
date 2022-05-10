#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int const NUMERO_FILOSOFI = 4;

int statoFilosofo[NUMERO_FILOSOFI];
sem_t semaforo_binario s[NUMERO_FILOSOFI]; //dichiarazione semaforo binario (ogni filosofo ha un semaforo)
pthread_t filosofi[NUMERO_FILOSOFI]; //dichiarazione array di thread di filosofi 
const int PENSA = 0;
const int MANGIA = 1;
const int AFFAMATO = 2;


void schermataIniziale();
void inizializza();
void creaThread(pthread_t filosofi, int &numForchette);
int generaDurataInMs(int min, int max);
int filosofoDestro(int i);
int filosofoSinistro(int i);
void prendiForchetta(int i, int *numForchette);

void wait(int& s);

int main(){
	int numForchette = NUMERO_FILOSOFI;
	inizializza();
	schermataIniziale();
	while(true){
		creaThread(NUMERO_FILOSOFI, numForchette);
	}
	pensa()
	return 0;
}


//Metodo che: imposta stato filosofi a pensa e inizializza semafori 
void inizializza(){
	sem_init(semaforo_binario, 0,0); //inizializzazione dei semafori
	for(int i = 0; i < NUMERO_FILOSOFI; i++){
		statoFilosofo[i] = PENSA:
	}
}

//Metodo crea thread per tutti i filosofi
void creaThread(pthread_t filosofi[NUMERO_FILOSOFI], int &numForchette){
	for(pos = 0; pos < NUMERO_FILOSOFI; pos++){
		pthread_create(&filosofi[i], NULL, filosofo, (*void) i);
	}
}

//Metodo di schermata iniziale
void schermataIniziale(){
	cout << "**** PROBLEMA DEI FILOSOFI A CENA ****" << endl;
	cout << "*  Corso di Sistemi Operativi        *" << endl;
	cout << "**************************************" << endl;
	return;
}

// metodo per la generazione automatica di intervalli di tempo (in ms)
int generaDurataInMs(int min, int max){
	int durataCasuale = rand () % min + max;
    return durataCasuale;
}

// metodi che restituiscono la posizione dei filosofi a destra e a sinistra
// siccome i filosofi si trovano in un tavolo rotondo , il filosofo in pos. 5 avrà alla sua desta il filosofo in pos. 1
int filosofoDestro(int i){
	return (i + 1) % NUMERO_FILOSOFI;
}

//il filosofo in pos. 5 avrà alla sua sinistra il filosofo in pos. 4
int filosofoSinistro(int i){
	return (i + NUMERO_FILOSOFI - 1) % NUMERO_FILOSOFI;    
}



void filosofoStaMangiando(int i, int *numForchette){
	int destro = filosofoDestro(i);
	int sinistro = filosofoSinistro(i);
	if( (statoFilosofo[i] == AFFAMATO) && (statoFilosofo[destro] != MANGIA) && (statoFilosofo [sinistro] != MANGIA) ){
		statoFilosofo[i] = MANGIA;
		wait(numForchette); 
	}
}

void prendiForchetta(int i, int *numForchette){
	statoFilosofo[i] = AFFAMATO;
	cout << "Il filosofo in pos: " + i + " e' affamato";
	filosofoStaMangiando[i];
	
}



void wait(int& s){
	while(s < 0)
		//pthread_exit(0);
	s--;
}

void signal(int& s){
	s++;
}

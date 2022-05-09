#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int const NUMERO_FILOSOFI = 4;
pthread_t filosofi[NUMERO_FILOSOFI];
int statoFilosofo[NUMERO_FILOSOFI];
const int PENSA = 0;
const int MANGIA = 1;
const int AFFAMATO = 2;


void schermataIniziale();
int generaDurataInMs(int min, int max);
int filosofoDestro(int i);
inr filosofoSinistro(int i);
void inizializza();
void wait(int& s);

int main()
{
	int numForchette = NUMERO_FILOSOFI;
	inizializza();
	schermataIniziale();
	

	return 0;
}

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

void inizializza(){
	for(int i = 0; i < NUMERO_FILOSOFI; i++){
		statoFilosofo[i] = PENSA:
	}
}

void filosofoStaMangiando(int i, int *numForchette){
	int destro = filosofoDestro(i);
	int sinistro = filosofoSinistro(i);
	if( (statoFilosofo[i] == AFFAMATO) && (statoFilosofo[destro] != MANGIA) && (statoFilosofo [sinistro] != MANGIA) ){
		statoFilosofo[i] = MANGIA;
		wait(numForchette); 
	}
}

void wait(int& s){
	while(s < 0)
		//pthread_exit(0);
	s--;
}

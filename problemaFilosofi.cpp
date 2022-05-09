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
void inizializza();
int generaDurataInMs(int min, int max);

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

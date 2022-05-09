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

<<<<<<< HEAD

=======
>>>>>>> 89dca570331378fd639f0e320caa01328e9e86fc

void schermataIniziale();
void inizializza();

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
	return;
}

// metodo per la generazione automatica di intervalli di tempo (in ms)
int generaDurataInMs(int min, int max){
	int durataCasuale = rand () % min + max;
    return durataCasuale;
}

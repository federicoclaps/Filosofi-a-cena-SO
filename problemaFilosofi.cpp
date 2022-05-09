#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int const NUMERO_FILOSOFI = 4;

// identificatore di thread
pthread_t filosofi[NUMERO_FILOSOFI];

void schermataIniziale();

int main()
{
	int numForchette = NUMERO_FILOSOFI;
	schermataIniziale();

	return 0;
}

void schermataIniziale(){
	cout << "**** PROBLEMA DEI FILOSOFI A CENA ****" << endl;
	cout << "*  Corso di Sistemi Operativi        *" << endl;
	return;
}

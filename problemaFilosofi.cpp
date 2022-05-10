#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int const NUMERO_FILOSOFI = 5;

int statoFilosofo[NUMERO_FILOSOFI];
sem_t S = 5; //dichiarazione semaforo binario (ogni filosofo ha un semaforo)
pthread_t filosofi[NUMERO_FILOSOFI]; //dichiarazione array di thread di filosofi 
const int PENSA = 0;
const int MANGIA = 1;
const int AFFAMATO = 2;


void schermataIniziale();
void inizializza();
void creaThread(pthread_t filosofi);
int generaDurataInMs(int min, int max);
int filosofoDestro(int i);
int filosofoSinistro(int i);
void prendiForchette(int i);
void rilasciaForchette(int i);
void *filosofo(void *i);
void pensa(int i);
void mangia(int i);
void wait(int& s);
void signal(int& s);

int main(){
	//int numForchette = NUMERO_FILOSOFI;
	inizializza();
	schermataIniziale();
	while(true){
		creaThread(filosofi);
	}
	return 0;
}


//Metodo che: imposta stato filosofi a pensa e inizializza semafori 
void inizializza(){
	sem_init(S, 0,4); //inizializzazione dei semafori a 4
	for(int i = 0; i < NUMERO_FILOSOFI; i++){
		statoFilosofo[i] = PENSA;
	}
}

//Metodo crea thread per tutti i filosofi
void creaThread(pthread_t filosofi[NUMERO_FILOSOFI]){
	for(int i = 0; i < NUMERO_FILOSOFI; i++){
		pthread_create(&filosofi[i], NULL, filosofo, (void *)i);
	}
}

//Metodo di schermata iniziale
void schermataIniziale(){
	cout << "**** PROBLEMA DEI FILOSOFI A CENA ****" << endl;
	cout << "*  Corso di Sistemi Operativi        *" << endl;
	cout << "**************************************" << endl;
	return;
}

// Metodo per la generazione automatica di intervalli di tempo (in ms)
int generaDurataInMs(int min, int max){
	int durataCasuale = rand () % min + max;
    return durataCasuale;
}

//Metodo che restituisce il filosofo a destra del filosofo in pos. i
// ES: (il filosofo in pos. 5 avrà alla sua desta il filosofo in pos. 1)
int filosofoDestro(int i){
	return (i + 1) % NUMERO_FILOSOFI;
}

//Metodo che restituisce il filosofo a sinistra del filosofo in pos. i
//ES: (il filosofo in pos. 5 avrà alla sua sinistra il filosofo in pos. 4)
int filosofoSinistro(int i){
	return (i + NUMERO_FILOSOFI - 1) % NUMERO_FILOSOFI;    
}

//Metodo che imposta lo stato a Mangia e rilascia forchetta
void filosofoStaMangiando(int i){
	int destro = filosofoDestro(i);
	int sinistro = filosofoSinistro(i);
	if( (statoFilosofo[i] == AFFAMATO) && (statoFilosofo[destro] != MANGIA) && (statoFilosofo [sinistro] != MANGIA) ){
		statoFilosofo[i] = MANGIA;
		sem_post(&S); 
	}
}

//Metodo che 
void prendiForchette(int i){
	statoFilosofo[i] = AFFAMATO;
	cout << "Il filosofo in pos: " << i << " e' affamato";
	filosofoStaMangiando(i);	
	sem_wait(&S);
}

void rilasciaForchette(int i){
	statoFilosofo[i] = PENSA;
	int sinistro = filosofoSinistro(i);
	int destro = filosofoDestro(i);
	filosofoStaMangiando(sinistro);
	filosofoStaMangiando(destro);
}

void pensa(int i){
	int durata  = generaDurataInMs(400,600);
	cout << "Il filosofo in posizione: " << i << " PENSA" << "per:" << durata << "(ms)" << endl;
	usleep(durata);
}

void mangia(int i){
	int durata  = generaDurataInMs(400,600);
	cout << "Il filosofo in posizione: " << i << " MANGIA" << "per:" << durata << "(ms)" << endl;
	usleep(durata);
}


void *filosofo(void *i) { 
  while (true) {          
    pensa(*(int*)i);             
    prendiForchette(*(int*)i);        
    mangia(*(int*)i);               
    rilasciaForchette(*(int*)i);         
  }
}

//void wait(int& s){
//	while(s < 0)
//		//pthread_exit(0);
//	s--;
//}

//void signal(int& s){
//	s++;
//}

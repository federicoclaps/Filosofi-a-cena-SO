#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;

int const NUMERO_FILOSOFI = 5;
int const PENSA = 0;
int const MANGIA = 1;
int const AFFAMATO = 2;

int statoFilosofo[NUMERO_FILOSOFI];
sem_t S;                             // dichiarazione semaforo binario (ogni filosofo ha un semaforo)
pthread_t filosofi[NUMERO_FILOSOFI]; // dichiarazione array di thread di filosofi
pthread_mutex_t mutexStampa;         // dichiarazione mutex


void schermataIniziale();
void inizializza();
void creaThread();
int generaDurataInMs(int min, int max);
int filosofoDestro(int i);
int filosofoSinistro(int i);
void prendiForchette(int i);
void rilasciaForchette(int i);
void *filosofo(void *i);
void pensa(int i);
void mangia(int i);
void joinThread();


//Metodo main 
int main(){
  inizializza();
  schermataIniziale();
  creaThread();
  joinThread();
  return 0;
}

// Metodo che: imposta stato filosofi a pensa e inizializza semafori
void inizializza(){
  pthread_mutex_init(&mutexStampa, NULL); //inizializzazione del mutex
  sem_init(&S, 0, NUMERO_FILOSOFI); // inizializzazione dei semafori al numero dei filosofi
  for (int i = 0; i < NUMERO_FILOSOFI; i++){
    statoFilosofo[i] = PENSA;
  }
}

void creaThread(){
  for (unsigned long i = 0; i < NUMERO_FILOSOFI; i++){
    pthread_create(&filosofi[i], NULL, filosofo, (void *)i); 
  }
}

// Metodo di schermata iniziale
void schermataIniziale(){
  cout << "* ************************************* *" << endl;
  cout << "*     PROBLEMA DEI FILOSOFI A CENA      *" << endl;
  cout << "*       Corso di Sistemi Operativi      *" << endl;
  cout << "*  FEDERICO CLAPS - GIUSEPPE DI STEFANO *" << endl;
  cout << "* ************************************* *" << endl;
  return;
}

// Metodo per la generazione automatica di intervalli di tempo (in ms)
int generaDurataInMs(int min, int max){
  int durataCasuale = rand() % min + max;
  return durataCasuale;
}

// Metodo che restituisce il filosofo a destra del filosofo in pos. i
int filosofoDestro(int i){
  return (i + 1) % NUMERO_FILOSOFI;
}

// Metodo che restituisce il filosofo a sinistra del filosofo in pos. i
int filosofoSinistro(int i){
  return (i + NUMERO_FILOSOFI - 1) % NUMERO_FILOSOFI;
}

void filosofoStaMangiando(int i){
  int destro = filosofoDestro(i);
  int sinistro = filosofoSinistro(i);
  if ((statoFilosofo[i] == AFFAMATO) && (statoFilosofo[destro] != MANGIA) && (statoFilosofo[sinistro] != MANGIA)){
    statoFilosofo[i] = MANGIA;
    sem_post(&S);
  }
}


void prendiForchette(int i){
  statoFilosofo[i] = AFFAMATO;
  pthread_mutex_lock(&mutexStampa);      //ingresso regione critica
  usleep(1000000);
  cout << "Il filosofo in posizione: " << i << " E' AFFAMATO " << endl;
  pthread_mutex_unlock(&mutexStampa);    // uscita regione critica
  filosofoStaMangiando(i);
  sem_wait(&S);
  sem_wait(&S);
}

void rilasciaForchette(int i){
  statoFilosofo[i] = PENSA;
  int sinistro = filosofoSinistro(i);
  int destro = filosofoDestro(i);
  filosofoStaMangiando(sinistro);
  filosofoStaMangiando(destro);
  sem_post(&S);
  sem_post(&S);
}

void pensa(int i){
  int durata = generaDurataInMs(400, 600);
  pthread_mutex_lock(&mutexStampa);
  usleep(1000000);
  cout << "Il filosofo in posizione: " << i << "  PENSA "
       << " per " << durata << " (ms) " << endl;
  pthread_mutex_unlock(&mutexStampa);
  usleep(durata);
}
 
void mangia(int i){
  int durata = generaDurataInMs(400, 600);
  pthread_mutex_lock(&mutexStampa);
  usleep(1000000);
  cout << "Il filosofo in posizione: " << i << " MANGIA "<< " per " << durata << " (ms) " << endl;
  pthread_mutex_unlock(&mutexStampa);
  usleep(durata);
}

void *filosofo(void *i){
  while (true) {
    unsigned long threadID = (unsigned long)i;
    pensa(threadID);
    prendiForchette(threadID);
    mangia(threadID);
    rilasciaForchette(threadID);
  }
  
}

void joinThread() {
  for (unsigned long i = 0; i < NUMERO_FILOSOFI; i++){
    pthread_join(filosofi[i], NULL);
  }
}

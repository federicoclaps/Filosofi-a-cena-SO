#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;

int const NUMERO_FILOSOFI = 5;

int statoFilosofo[NUMERO_FILOSOFI];
sem_t S;                             // dichiarazione semaforo binario (ogni filosofo ha un semaforo)
pthread_t filosofi[NUMERO_FILOSOFI]; // dichiarazione array di thread di filosofi
pthread_mutex_t mutexStampa;
const int PENSA = 0;
const int MANGIA = 1;
const int AFFAMATO = 2;

void schermataIniziale();
void inizializza();
// void creaThread(pthread_t* filosofi);
void creaThread();
int generaDurataInMs(int min, int max);
int filosofoDestro(int i);
int filosofoSinistro(int i);
void prendiForchette(int i);
void rilasciaForchette(int i);
void *filosofo(void *i);
void pensa(int i);
void mangia(int i);
void wait(int &s);
void signal(int &s);
void joinThread();
void stampaMessaggio(string stringa1, int varInt, string stringa2);

int main()
{

  // int numForchette = NUMERO_FILOSOFI;
  inizializza();
  schermataIniziale();
  creaThread();
  joinThread();
  return 0;
}

// Metodo che: imposta stato filosofi a pensa e inizializza semafori
void inizializza()
{
  pthread_mutex_init(&mutexStampa, NULL);
  sem_init(&S, 0, NUMERO_FILOSOFI); // inizializzazione dei semafori al numero dei filosofi
  for (int i = 0; i < NUMERO_FILOSOFI; i++)
  {
    statoFilosofo[i] = PENSA;
  }
}


void creaThread()
{
  for (unsigned long i = 0; i < NUMERO_FILOSOFI; i++)
  {
    //usleep(1000000);
    pthread_create(&filosofi[i], NULL, filosofo, (void *)i); 
  }
}


// Metodo di schermata iniziale
void schermataIniziale()
{
  cout << "**** PROBLEMA DEI FILOSOFI A CENA ****" << endl;
  cout << "*    Corso di Sistemi Operativi      *" << endl;
  cout << "**************************************" << endl;
  return;
}

// Metodo per la generazione automatica di intervalli di tempo (in ms)
int generaDurataInMs(int min, int max)
{
  int durataCasuale = rand() % min + max;
  return durataCasuale;
}

// Metodo che restituisce il filosofo a destra del filosofo in pos. i
//  ES: (il filosofo in pos. 5 avrà alla sua desta il filosofo in pos. 1)
int filosofoDestro(int i)
{
  return (i + 1) % NUMERO_FILOSOFI;
}

// Metodo che restituisce il filosofo a sinistra del filosofo in pos. i
// ES: (il filosofo in pos. 5 avrà alla sua sinistra il filosofo in pos. 4)
int filosofoSinistro(int i)
{
  return (i + NUMERO_FILOSOFI - 1) % NUMERO_FILOSOFI;
}

// Metodo che imposta lo stato a Mangia e rilascia forchetta
//  metodo che inserito all'interno di prendiForchette e rilasciaForchette, impedisce la situazione di stallo


void filosofoStaMangiando(int i)
{
  int destro = filosofoDestro(i);
  int sinistro = filosofoSinistro(i);
  if ((statoFilosofo[i] == AFFAMATO) && (statoFilosofo[destro] != MANGIA) && (statoFilosofo[sinistro] != MANGIA))
  {
    statoFilosofo[i] = MANGIA;
    sem_post(&S);
  }
}


// Metodo che


void prendiForchette(int i)
{
  statoFilosofo[i] = AFFAMATO;
  pthread_mutex_lock(&mutexStampa);
  usleep(1000000);
  cout << "Il filosofo in pos. " << i << " e' AFFAMATO " << endl;
  pthread_mutex_unlock(&mutexStampa);
  filosofoStaMangiando(i);
  sem_wait(&S);
  sem_wait(&S);
}

void rilasciaForchette(int i)
{
  statoFilosofo[i] = PENSA;
  int sinistro = filosofoSinistro(i);
  int destro = filosofoDestro(i);
  filosofoStaMangiando(sinistro);
  filosofoStaMangiando(destro);
  sem_post(&S);
  sem_post(&S);
}

void pensa(int i)
{
  int durata = generaDurataInMs(400, 600);
    pthread_mutex_lock(&mutexStampa);
    usleep(1000000);
  cout << "Il filosofo in posizione: " << i << " PENSA "
       << " per " << durata << " (ms) " << endl;
    pthread_mutex_unlock(&mutexStampa);
  usleep(durata);
}
 
void mangia(int i)
{
  int durata = generaDurataInMs(400, 600);
    pthread_mutex_lock(&mutexStampa);
    usleep(1000000);
  cout << "Il filosofo in posizione: " << i << " MANGIA "
       << " per " << durata << " (ms) " << endl;
    pthread_mutex_unlock(&mutexStampa);
  usleep(durata);
}

void *filosofo(void *i)
{
  while (true) {
  unsigned long threadID = (unsigned long)i;
  pensa(threadID);
  prendiForchette(threadID);
  mangia(threadID);
  rilasciaForchette(threadID);
  }
  
}

void joinThread() {
  for (unsigned long i = 0; i < NUMERO_FILOSOFI; i++)
  {
    pthread_join(filosofi[i], NULL);
  }
}

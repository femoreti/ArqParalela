//A C PROGRAM TO IMPLEMENT THE H2O PROBLEM USING SEMAPHORES
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

sem_t smutex,oxyQueue,hydroQueue;
sem_t sBlocker, bmutex;
int bCount=0;
int bTotal;

int oxygen=0,hydregen=0;

pthread_t oxyThread,hydroThread1,hydroThread2;

int ConnectMolecules(void){
    static int i=0;
    i++;
    if((i%3)==0)
        printf("** Molecule no. %d created**\n\n",i/3);
    sleep(2);
    return(0);
}

void Blocker(int n){
    bTotal=n;

    if(sem_init(&sBlocker,0,0)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
    if(sem_init(&bmutex,0,1)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }

}

void Blocker_wait(){

    sem_wait(&bmutex);
    bCount++;
    sem_post(&bmutex);

    if(bCount==bTotal)
        sem_post(&sBlocker);

    sem_wait(&sBlocker);
    sem_post(&sBlocker);
}

void* Oxygen(void* arg){

    while(1){
        sem_wait(&smutex);

        oxygen+=1;

        if(hydregen>=2){
            sem_post(&hydroQueue);
            sem_post(&hydroQueue);
            hydregen-=2;
            sem_post(&oxyQueue);
            oxygen-=1;
        }
        else {
            sem_post(&smutex);
        }

        sem_wait(&oxyQueue);
        printf("Oxygen connected\n");
        ConnectMolecules();

        Blocker_wait();
        sem_post(&smutex);
    }
}

void* Hydrogen(void* arg){
    while(1){
        sem_wait(&smutex);

        hydregen+=1;

        if(hydregen>=2 && oxygen>=1){
            sem_post(&hydroQueue);
            sem_post(&hydroQueue);
            hydregen-=2;
            sem_post(&oxyQueue);
            oxygen-=1;
        }
        else{
            sem_post(&smutex);
        }

        sem_wait(&hydroQueue);

        printf("Hydrogen connected\n");
        ConnectMolecules();

        Blocker_wait();
        }

}

int main(void){

    if(sem_init(&smutex,0,1)==-1){
        perror("error initilalizing semaphore\n");
    }
    if(sem_init(&oxyQueue,0,0)==-1){
        perror("error initilalizing semaphore\n");
    }
    if(sem_init(&hydroQueue,0,0)==-1){
        perror("error initilalizing semaphore\n");
    }

    Blocker(3);

    pthread_create(&oxyThread,0,Oxygen, NULL);
    pthread_create(&hydroThread1,0,Hydrogen, NULL);
    pthread_create(&hydroThread2,0,Hydrogen, NULL);

    for(;;);
    
    return 0;
}
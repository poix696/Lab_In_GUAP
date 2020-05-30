#include <iostream>
#include <cstring> // need this for strerror
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include "lab2.h"

// compile with -lpthreads

#define NUMBER_OF_A_THREADS 1
#define NUMBER_OF_B_THREADS 1
#define NUMBER_OF_C_THREADS 1
#define NUMBER_OF_D_THREADS 1
#define NUMBER_OF_E_THREADS 1
#define NUMBER_OF_F_THREADS 1
#define NUMBER_OF_H_THREADS 1
#define NUMBER_OF_G_THREADS 1
#define NUMBER_OF_K_THREADS 1
#define NUMBER_OF_P_THREADS 1
#define NUMBER_OF_N_THREADS 1
#define NUMBER_OF_M_THREADS 1
#define NUMBER_OF_THREADS (NUMBER_OF_A_THREADS + NUMBER_OF_B_THREADS + NUMBER_OF_C_THREADS + NUMBER_OF_D_THREADS + NUMBER_OF_D_THREADS + NUMBER_OF_E_THREADS + NUMBER_OF_H_THREADS + NUMBER_OF_G_THREADS + NUMBER_OF_K_THREADS + NUMBER_OF_P_THREADS + NUMBER_OF_N_THREADS + NUMBER_OF_M_THREADS)

pthread_t tid[NUMBER_OF_THREADS];
pthread_mutex_t lock;  // critical section lock
sem_t *semC, *semE, *semD, *semF, *semF1, *semH, *semG, *semK, *semK1, *semP, *semM, *semM1, *semN, *semN1;

unsigned int lab2_task_number()
{
return 14;
}

// consumer thread from the producer-consumer problem
void *thread_a(void *ptr)
{
    char const* thread_msg = (char*) ptr;
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << thread_msg << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(60);
}
    sem_post(semC);
    return  ptr;
}

// producer thread from the producer-consumer problem
void *thread_b(void *ptr)
{
    char const* thread_msg = (char*) ptr;
    for (int i = 0; i < 6; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << thread_msg << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(50);
    }
sem_post(semE);
sem_post(semD);
    return ptr;
}

void *thread_c(void *ptr)
{
sem_wait(semC);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 6; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semF);
return ptr;
}

void *thread_d(void *ptr)
{
sem_wait(semD);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 3; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semF1);
return ptr;
}

void *thread_e(void *ptr)
{
sem_wait(semE);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 6; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);

}
sem_post(semH);
sem_post(semG);
return ptr;
}

void *thread_f(void *ptr)
{
sem_wait(semF);
sem_wait(semF1);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 6; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semK1);
sem_post(semM1);
return ptr;
}

void *thread_h(void *ptr)
{
sem_wait(semH);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 3; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semK);
sem_post(semM);
return ptr;
}

void *thread_g(void *ptr)
{
sem_wait(semG);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 6; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semP);
return ptr;
}

void *thread_k(void *ptr)
{
sem_wait(semK);
sem_wait(semK1);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 6; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semP);
sem_post(semN1);
return ptr;
}

void *thread_p(void *ptr)
{
sem_wait(semP);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 3; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
sem_post(semN);
return ptr;
}

void *thread_m(void *ptr)
{
sem_wait(semM);
sem_wait(semM1);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 9; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
return ptr;
}

void *thread_n(void *ptr)
{
sem_wait(semN);
sem_wait(semN1);
char const* thread_msg = (char*) ptr;
for (int i = 0; i < 3; ++i)
{
       pthread_mutex_lock(&lock);
       std::cout<<thread_msg<<std::flush;
       pthread_mutex_unlock(&lock);
       sleep_ms(50);
}
return ptr;
}


int lab2_init()
{
    char const * thread_texts[] = {"a", "b", "c", "d", "e", "f", "h", "g", "k", "p", "m", "n"};
    int err;
    // initilize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    //initialize semaphores
    if ( (semC = sem_open("/my_semaphore14", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #13 init failed" << std::endl;
        return 1;
    }
    if ( (semE = sem_open("/my_semaphore13", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #12 init failed" << std::endl;
        return 1;
    }
     if ( (semD = sem_open("/my_semaphore12", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #11 init failed" << std::endl;
        return 1;
    }
     if ( (semF = sem_open("/my_semaphore11", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #10 init failed" << std::endl;
        return 1;
    }

     if ( (semF1 = sem_open("/my_semaphore10", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #9 init failed" << std::endl;
        return 1;
    }
     if ( (semH = sem_open("/my_semaphore9", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #8 init failed" << std::endl;
        return 1;
    }

     if ( (semG = sem_open("/my_semaphore8", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #7 init failed" << std::endl;
        return 1;
    }
     if ( (semK = sem_open("/my_semaphore7", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #6 init failed" << std::endl;
        return 1;
    }
     if ( (semK1 = sem_open("/my_semaphore6", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #5 init failed" << std::endl;
        return 1;
    }
     if ( (semP = sem_open("/my_semaphore5", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #5 init failed" << std::endl;
        return 1;
    }
    if ( (semM = sem_open("/my_semaphore4", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #4 init failed" << std::endl;
        return 1;
    }
    if ( (semM1 = sem_open("/my_semaphore3", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #3 init failed" << std::endl;
        return 1;
    }
    if ( (semN = sem_open("/my_semaphore2", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #2 init failed" << std::endl;
        return 1;
    }
    if ( (semN1 = sem_open("/my_semaphore1", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        std::cerr << "Semaphore #1 init failed" << std::endl;
        return 1;
    }

    // start the threads
    unsigned int thread_count = 0;
    for (int i = 0; i < NUMBER_OF_A_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_a, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }
    for (int i = 0; i < NUMBER_OF_B_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_b, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_C_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_c, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_D_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_d, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_E_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_e, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_F_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_f, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_H_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_h, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    for (int i = 0; i < NUMBER_OF_G_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_g, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }
    for (int i = 0; i < NUMBER_OF_K_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_k, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }
    for (int i = 0; i < NUMBER_OF_P_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_p, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }
    for (int i = 0; i < NUMBER_OF_M_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_m, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }
    for (int i = 0; i < NUMBER_OF_N_THREADS; ++i) {
        err = pthread_create(&tid[thread_count], NULL, thread_n, (void *) thread_texts[thread_count]);
        if (err != 0)
            std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        else
            ++thread_count;
    }

    // wait for threads to finish
    for (int i = 0; i < thread_count; ++i) {
        pthread_join(tid[i], NULL);
    }
    // destroy mutex
    pthread_mutex_destroy(&lock);
    // close semaphores
    sem_close(semC);
    sem_close(semE);
    sem_close(semD);
    sem_close(semF);
    sem_close(semF1);
    sem_close(semH);
    sem_close(semG);
    sem_close(semK);
    sem_close(semK1);
    sem_close(semP);
    sem_close(semM);
    sem_close(semM1);
    sem_close(semN);
    sem_close(semN1);
    // destroy semaphores
    sem_unlink("/my_semaphore1");
    sem_unlink("/my_semaphore2");
    sem_unlink("/my_semaphore3");
    sem_unlink("/my_semaphore4");
    sem_unlink("/my_semaphore5");
    sem_unlink("/my_semaphore6");
    sem_unlink("/my_semaphore7");
    sem_unlink("/my_semaphore8");
    sem_unlink("/my_semaphore9");
    sem_unlink("/my_semaphore10");
    sem_unlink("/my_semaphore11");
    sem_unlink("/my_semaphore12");
    sem_unlink("/my_semaphore13");
    sem_unlink("/my_semaphore14");
    // print a new line
    std::cout << std::endl;
return 0;
}

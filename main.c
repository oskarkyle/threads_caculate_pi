#include <stdio.h>
#include <pthread.h>
#define MAXTHREAD 2
double step;
int num_step = 1000000;

typedef struct {
    int start;
    int end;
    double sum;
} thread_param;

void* thread_func(void* arg){
    thread_param* thr_arg = (thread_param*) arg;
    int start = thr_arg->start;
    int end = thr_arg->end;
    double x = 0, sum = 0;

    for(int i = start; i < end; i++){
        x = (i + 0.5) * step;
        sum += 4 / (1 + x * x);
    }

    thr_arg->sum = sum;
    return NULL;
}

int main(){
    double sum = 0;
    int i;
    pthread_t thread[MAXTHREAD];
    thread_param thr_arg[MAXTHREAD];
    step = 1.0 / (double)num_step;

    for(i = 0; i < MAXTHREAD; i++){
        thr_arg[i].start = i * (num_step / MAXTHREAD);
        thr_arg[i].end = (i + 1) * (num_step / MAXTHREAD);
        thr_arg[i].sum = sum;

        pthread_create(&thread[i], NULL, thread_func, &thr_arg[i]);
    }

    for(i = 0; i < MAXTHREAD; i++){
        pthread_join(thread[i], NULL);
        sum += thr_arg[i].sum;
    }

   
    printf("pi = %f\n", sum * step);
    return 0;
}
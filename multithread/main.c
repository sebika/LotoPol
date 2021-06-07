#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#include "source/lehmer64.h"

#define MAX_NUM 80
#define DRAW_SIZE 20

#define NUMBERS_TO_EXTRACT 9
#define NUMBERS_TO_WIN 6

#define THREADS 8

int draw[20000][MAX_NUM+1], lines;
int stop;

pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
    int i, j;
	int thread_id = *(int *)arg;

    int number[NUMBERS_TO_EXTRACT];
    int occurence[MAX_NUM+1];

    int mx = -1;
    int best_number[NUMBERS_TO_EXTRACT];

    printf("Thread %d started\n", thread_id);

    for (i = 0; i <= MAX_NUM; i++)
        occurence[i] = 0;

    while (!stop) {
        int invalid = 0;
        for (i = 0; i < NUMBERS_TO_EXTRACT; i++) {
            number[i] = (int)(lehmer64() % 80) + 1;
            occurence[number[i]] += 1;
        }

        for (i = 0; i < NUMBERS_TO_EXTRACT; i++) {
            if (occurence[number[i]] > 1)
                invalid = 1;
            occurence[number[i]] = 0;
        }

        if (invalid)
            continue;

        for (i = 0; i < lines; i++) {
            register int count = 0;
            for (j = 0; j < NUMBERS_TO_EXTRACT; j++) {
                if (draw[i][number[j]])
                    count ++;
            }

            if (count >= NUMBERS_TO_WIN) {
                if (mx < i) {
                    mx = i;
                    for (j = 0; j < NUMBERS_TO_EXTRACT; j++)
                        best_number[j] = number[j];
                }
                break;
            }
        }
    }

    pthread_mutex_lock(&global_mutex);
    printf("Thread %d found: ", thread_id);
    for (i = 0; i < NUMBERS_TO_EXTRACT; i++)
        occurence[best_number[i]] = 1;

    for (i = 0; i <= MAX_NUM; i++)
        if (occurence[i])
            printf("%2d ", i);

    printf("-> %d\n", mx);
    pthread_mutex_unlock(&global_mutex);

    pthread_exit(EXIT_SUCCESS);
}

int main(void) {
    struct timeval tv;
    int i, ret, x;
    FILE *in = fopen("input", "r");

    gettimeofday(&tv, NULL);
    lehmer64_seed(tv.tv_usec);

    lines = 0;
    while (1) {
        ret = fscanf(in, "%d", &x);
        if (ret == -1)
            break;
        draw[lines][x] = 1;

        for (i = 0; i < DRAW_SIZE-1; i++) {
            fscanf(in, "%d", &x);
            draw[lines][x] = 1;
        }

        lines++;
    }

    pthread_t tid[THREADS];
	int thread_id[THREADS];

    for (i = 0; i < THREADS; i++) {
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

    char *command;
    command = malloc(100 * sizeof(char));

    while (1) {
        memset(command, 0, 100);
        scanf("%s", command);
        if (strncmp(command, "exit", 4) == 0) {
            stop = 1;
            break;
        }
    }

    free(command);

	// se asteapta thread-urile
	for (i = 0; i < THREADS; i++) {
		pthread_join(tid[i], NULL);
	}



    return 0;
}

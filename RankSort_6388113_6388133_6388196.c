///////////////////////////////////////////
//       Rank Sort Algorithm
// 6388113 Poomrapee Wareeboutr
// 6388133 Pitchaya  Teerawongpairoj
// 6388196 Sasima    Srijanya
///////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define RANDOM_RANGE 10000

int MAX_SIZE;
int NUM_THREADS;

void generate_list(int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) { 
        arr[i] = rand() % RANDOM_RANGE;
    }
    for (i = 0; i < n; i++) {
        int j = rand() % n;
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

void print_list(int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <array_size> <number_of_threads>\n", argv[0]);
        exit(1);
    }

    MAX_SIZE = atoi(argv[1]);
    NUM_THREADS = atoi(argv[2]);
    printf("array_size: %d\n", MAX_SIZE);
    printf("num_threads: %d\n", NUM_THREADS);

    int n = MAX_SIZE;
    double start, stop;

    int i, j;
    int *arr = (int *)malloc(n * sizeof(int));
    int *rank = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) { rank[i] = 0; }
    generate_list(arr, n);
    // print_list(arr, n);
    start = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    printf("sorting ...\n");
    // parallel section ...
    #pragma omp parallel for private(j)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (arr[j] < arr[i] || (arr[j] == arr[i] && j < i)) {
                rank[i]++;
            }
        }
    }
    // end parallel section ...
    int *sorted = (void *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        sorted[rank[i]] = arr[i];
    }
    stop = omp_get_wtime();
    print_list(sorted, n);
    printf("time: %f\n", stop - start);
    // free allocated memory
    free(arr); free(rank); free(sorted);
}

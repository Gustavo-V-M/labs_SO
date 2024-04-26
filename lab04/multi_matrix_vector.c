#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *x;
int **A;
int *r;
int x_size;
int A_row_count;


void *add_rowwise(void *row_index){
	int *sum = (int*)malloc(sizeof(int));
	for (int i = 0; i < x_size; i++){
		*sum += A[*(int*)row_index][i] * x[i];
	}
	r[*(int*)row_index] = *sum;
	return NULL;
}
int main(int argc, char *argv[]){
	x_size = 5;
	A_row_count = 10;
	x = (int*)malloc(x_size * sizeof(int));
	for (int i = 0; i < x_size; i++){
		x[i] = 1;
	}
	A = (int**)malloc(A_row_count * sizeof(int*));
	for (int i = 0; i < A_row_count; i++){
		A[i] = (int*)malloc(x_size * sizeof(int));
		for (int j = 0; j < x_size; j++){
			A[i][j] = j;
		}
	}

	// refactor the following code segment into a function
	
	pthread_t *threads = (pthread_t*)malloc(A_row_count * sizeof(pthread_t));
	r = (int*)malloc(A_row_count * sizeof(int));
	for (int i = 0; i < A_row_count; i++){
		int *index = (int*)malloc(sizeof(int));
		*index = i;
		int success = pthread_create(
				&(threads[i]),
				NULL,
				add_rowwise,
				(void*)index
				);
		if (success != 0){
			printf("Error on creation of thread %i\n", i);
			return EXIT_FAILURE;
		}
	}
	for (int i = 0; i < A_row_count; i++){
		int success = pthread_join(threads[i], NULL);
		if (success != 0){
			printf("Error on waiting for %i thread to finish\n");
			return EXIT_FAILURE;
		}
	}
	for (int i = 0; i < A_row_count; i++){
		printf("%i\n", r[i]);
	}
	return EXIT_SUCCESS;
}

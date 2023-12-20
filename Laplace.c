#include <stdio.h>
#include <stdlib.h>

float laplace(int N, float* matrix) {
	// base case
	if (N <= 2) {
		//printf("%f * %f - %f * %f\n", matrix[0], matrix[3], matrix[1], matrix[2]);
		return ((matrix[0]*matrix[3]) - (matrix[1]*matrix[2]));
	}
	
	// init variables
	int newMatSize = (N-1)*(N-1); 
	int matSize = (N*N);
	float *newMat = calloc(newMatSize, sizeof(float));
	
	if (newMat == NULL) {
		free(newMat);
		return 0;
	}
	
	int pos;
	float total = 0;
	
	// itterate through top row
	for (int i = 0; i < N; i++) {
		// copy necessary values to new matrix
		pos = 0;
		for (int j = N; j < matSize; j++) {
			if ((j % N) != i) {
				newMat[pos] = matrix[j];
				pos++;
			}
		}
		
		// alternating sign change
		if ((i % 2) == 0) {
			total += (matrix[i] * laplace((N-1), newMat));
		} else {
			total -= (matrix[i] * laplace((N-1), newMat));
		}
	}
	
	free(newMat);
	
	return total;
}

int main(void) {
	
	// get dimensionality input
	int N; 
	scanf("%d", &N);
	
	// init variables
	int matSize = N*N;
	
	float *matrix = calloc(matSize, sizeof(float)); // could use malloc (might be faster)
	if (matrix == NULL) {
		free(matrix);
		return 0;
	}
	
	// get matrix data input
	for (int i = 0; i < matSize; i++) {
		scanf("%f", &matrix[i]);
		//printf("%f\n", matrix[i]);
	}
	
	printf("%f\n", laplace(N, matrix));
	
	free(matrix);
	
	return 0;
}
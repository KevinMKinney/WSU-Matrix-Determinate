#include <stdio.h>
#include <stdlib.h>

float gaussianElimination(int N, double* matrix) {
	// init vars
	double coef, swapTemp = 0;
	int row, top = 0;
	double det = 1;

	for (int i = 0; i < (N-1); i++) {
		for (int j = i+1; j < N; j++) {
			row = (N*j)+i;
			top = (N*i)+i;

			//if diagonal value is 0, swap row with the lowest non-zero row
			if (matrix[top] == 0) {
				for (int k = (N-1); k > 0; k--) {
					if (matrix[(N*k)+i] != 0) {
						for (int l = 0; l < (N-i); l++) {
							swapTemp = matrix[(N*k)+i+l];
							matrix[(N*k)+i+l] = matrix[top+l];
							matrix[top+l] = swapTemp;
						}
						det = -det;
						break;
					}
				}
			}

			if (matrix[row] != 0) {
				coef = -(matrix[top]/matrix[row]);

				if (coef != 0) {
					det /= coef;
				}

				for (int k = 0; k < (N-i); k++) {
					matrix[row+k] = matrix[top+k] + (coef * matrix[row+k]);
				}
			}
		}
	}

	// calculate determinate
	for (int i = 0; i < N; i++) {
		det *= matrix[(N*i)+i];
	}

	return det;
}

int main(void) {

	// get dimensionality input
	int N;
	scanf("%d", &N);

	// init variables
	int matSize = N*N;

	double *matrix = calloc(matSize, sizeof(double)); // could use malloc (might be faster)
	if (matrix == NULL) {
		free(matrix);
		return 0;
	}

	// get matrix data input
	for (int i = 0; i < matSize; i++) {
		scanf("%lf", &matrix[i]);
	}

	printf("%lf\n", gaussianElimination(N, matrix));

	free(matrix);

	return 0;
}

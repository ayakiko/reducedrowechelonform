#include <windows.h>
#include <stdio.h>
#include <math.h>

void printMatrix(double matrix[], int n, int m) {
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < m; k++)
			printf("%f, ", matrix[m * j + k]);
		printf("\n");
	}
}

void toReducedRowEchelonForm(double matrix[], int n, int m) {
	double c, lead;

	for (int j = 0; j < n; j++)
	{
		lead = matrix[m * j + j];

		for (int k = 0; k < m; k++)
			matrix[m * j + k] /= lead;

		for (int i = 0; i < n; i++)
		{
			if (i == j) continue;

			c = matrix[m * i + j] / matrix[m * j + j];

			for (int k = j; k < m; k++) {
				matrix[m * i + k] = matrix[m * i + k] - matrix[m * j + k] * c;
			}
		}
	}
}

int main(int argc, char **argv) {

	double points[] = {
		-1.5,	-1.2,
		-.2,	0,
		1,		0.5,
		5,		1,
		10,		1.2
	};

	double mat[5 * 6] = {0};

	for (int j = 0; j < 5; j++)
	{
		for (int k = 0; k < 5; k++) {
			mat[6 * j + k] = pow(points[2 * j], 5 - k - 1);
		}
		mat[6 * j + 5] = points[2 * j + 1];
	}

	toReducedRowEchelonForm(mat, 5, 6);

	printMatrix(mat, 5, 6);

	return 0;
}

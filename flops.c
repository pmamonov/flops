#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#ifndef DIM
#define DIM 1024
const long long int nop = 1073217024;
#else
#define COUNT
long long int nop = 0;
#endif

void printm(double A[DIM][DIM])
{
	int i,j;
	for (i=0; i<DIM; i++) {
		for (j=0; j<DIM; j++)
			printf("%6.3f", A[i][j]);
		printf("\n");
	}
}

void initm(double A[DIM][DIM])
{
	int i,j;
	srand(38741);
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++)
			A[i][j] = (double)random() / (double)RAND_MAX - 0.5;
}

void dge(double A[DIM][DIM])
{
	int i, j, k;
	double c;
	for (k = 1; k < DIM; k++) {
		for (i = k; i < DIM; i++) {
			c = A[i][k-1] / A[k-1][k-1];
#ifdef COUNT
			nop += 1;
#endif
			for (j = 0; j < DIM; j++) {
				A[i][j] -= c * A[k-1][j];
#ifdef COUNT
				nop += 2;
#endif
			}
		}
	}
}

double X[DIM][DIM];

int main (int argc, char **argv)
{
	double t;
	struct rusage ru;
	printf("FLOPS\n");
	printf("GCC version: " __VERSION__ "\n");
	initm(X);
	getrusage(RUSAGE_SELF, &ru);
	t = ru.ru_utime.tv_sec
		+ ru.ru_stime.tv_sec
		+ ru.ru_utime.tv_usec * 1e-6
		+ ru.ru_stime.tv_usec * 1e-6; 
	dge(X);
	getrusage(RUSAGE_SELF, &ru);
	t =  ru.ru_utime.tv_sec
		+ ru.ru_stime.tv_sec
		+ ru.ru_utime.tv_usec * 1e-6
		+ ru.ru_stime.tv_usec * 1e-6
		- t;
	printf("Ops count: %llu\n", nop);
	printf("Time spent: %.2e sec\n", t);
	printf("MFLOPS: %.2f\n", 1e-6 * nop / t );
#ifdef PRINTM
	printm(X);
#endif
	return 0;
}

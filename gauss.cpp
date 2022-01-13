#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>

double** inputMAT(int*, int*);
double** allocMAT(int, int);
void transform(double**, double*, int, int);
void gauss(double**, int);
void createans(double **, double *, int);
void outputmass(double *, int);
void deleteMAT(double**);
void outputMAT(double**, int, int);

int main()
{
    int const MaxSize = 10;
    double x[MaxSize];
    int n, m;
     double** A = inputMAT(&n, &m);
    outputMAT(A, n, n);
    printf("\n");
    gauss(A, n);
    outputMAT(A, n, n);
    printf("\n");
    createans(A, x, n);
    outputmass(x, n);
    deleteMAT(A);
    getch();
}

double** inputMAT(int *n, int *m) // ввод матрицы
{
    printf("enter length\n");
    scanf("%i", n);
    *m = (*n) + 1;
    double** A = allocMAT(*n, *m);
    printf("enter elements\n");
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            scanf("%lf", A[i] + j);
    return A;
}

double** allocMAT(int n, int m)  // аллокация матрицы
{
    double** mat = new double *[n];
    double* vec = new double [n*m];
    transform(mat, vec, n, m);
    return mat;
}

void outputMAT(double **mat, int n, int m)  // вывод матрицы
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%7.2lf | ", *(mat[i]+j));
        printf("\n");
    }
}

void transform(double **mat, double* vec, int n, int m) // трансформация матрицы
{
    for (int i = 0; i < n; i++)
        mat[i] = vec + i * m;
}

void gauss(double **a, int n)        // создание матрицы треугольного вида
{
    for (int k = 0; k < n - 1; k++)
        for (int j = k + 1; j < n; j++)
        {
            double m = a[j][k] / a[k][k];
            for (int i = 0; i < n + 1; i++)
                a[j][i] = a[j][i] - m * a[k][i];
        }
}
void outputmass(double *arr, int n)               // вывод массива
{
    for (int i=0; i<n; i++) printf("%7.2lf |", arr[i]);
    printf("\n");
}

void createans(double **a, double *x, int n)   // нахождение корней и занесение их в массив
{
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = a[i][n] / a[i][i];
        for (int c = n - 1; c > i; c--)
            x[i] = x[i] - a[i][c] * x[c] / a[i][i];
    }
}

void deleteMAT(double** A)
{
    delete *A;
    delete A;
}
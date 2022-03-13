/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 4 - Structures and Dynamic Arrays
*Percobaan        : -
*Hari dan Tanggal : Rabu, 16 Maret 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoubleArray
{
    double *content;
    int len;
} DoubleArray;

typedef struct DoubleMatrix
{
    double **content;
    int h;
    int w;
} DoubleMatrix;

int calculateValue(DoubleMatrix *table, int i, int j)
{
	return -(table->content[i - 2][0] * table->content[i - 1][j + 1] -
			 table->content[i - 1][0] * table->content[i - 2][j + 1]) /
		   table->content[i - 1][0];
}

void freeDoubleArray(DoubleArray *a)
{
	free(a->content);
	free(a);
}

void freeDoubleMatrix(DoubleMatrix *t)
{
	for (int i = 0; i < t->h; i++)
	{
		free(t->content[i]);
	}
	free(t);
}

int main()
{
	char string[256];
	int isZeroRow, isStable, isNotStable;

	DoubleMatrix *table = (DoubleMatrix *)calloc(sizeof(DoubleMatrix), 1);
	DoubleArray *coeffs = (DoubleArray *)calloc(sizeof(DoubleArray), 1);

	printf("Masukkan koefisien-koefisien : ");
	scanf("%[^\n]s", string);

	// Pengisian array koefisien
	char *numAsString = strtok(string, " ");

	coeffs->content = (double *)calloc(sizeof(double), 0);
	coeffs->len = 0;
	while (numAsString != NULL)
	{
		double coeff = atof(numAsString);
		coeffs->len++;
		coeffs->content = (double *)realloc(coeffs->content, sizeof(double) * coeffs->len);
		coeffs->content[coeffs->len - 1] = coeff;
		numAsString = strtok(NULL, " ");
	}

	table->w = (coeffs->len + 1) / 2;
	table->h = coeffs->len;
	table->content = (double **)calloc(sizeof(double *), table->h);
	for (int i = 0; i < table->h; i++)
	{
		table->content[i] = (double *)calloc(sizeof(double), table->w);
	}

	// Pengisian dua baris pertama tabel routh
	int index = 0;
	int col = 0, row = 0;
	for (int i = 0; i < coeffs->len; i++)
	{
		if (i % 2 == 0 && i != 0)
		{
			row = 0;
			col++;
		}
		table->content[row][col] = coeffs->content[i];
		row++;
	}

	// Pengisian tabel routh
	for (int i = 1; i < table->h; i++)
	{
		if (i != 1)
		{
			for (int j = 0; j < table->w - 1; j++)
			{
				table->content[i][j] = calculateValue(table, i, j);
			}
		}

		// Mengecek apakah baris berisi 0 semua
		isZeroRow = 1;
		for (int j = 0; j < table->w; j++)
		{
			if (table->content[i][j] != 0)
			{
				isZeroRow = 0;
				j = table->w;
			}
		}

		// Mengcek apakah angka pada kolom pertama 0
		int isOnlyFirstColZero = 0;
		if (table->content[i][0] == 0)
		{
			for (int j = 1; j < table->w; j++)
			{
				if (table->content[i][j] != 0)
				{
					isOnlyFirstColZero = 1;
					j = table->w;
				}
			}
		}

		if (isOnlyFirstColZero)
		{
			table->content[i][0] = 10e-100;
		}

		if (isZeroRow)
		{
			i = table->h;
		}
	}

	// Penafsiran tabel routh
	if (isZeroRow)
	{
		printf("Sistem tidak stabil atau stabil marginal\n");
	}
	else
	{
		int isStable = 1;
		for (int i = 0; i < table->h - 1; i++)
		{
			if (table->content[i][0] * table->content[i + 1][0] < 0)
			{
				isStable = 0;
				i = table->h;
			}
		}

		if (isStable)
		{
			printf("Sistem stabil\n");
		}
		else
		{
			printf("Sistem tidak stabil\n");
		}
	}

	// Membebaskan alokasi memory
	freeDoubleArray(coeffs);
	freeDoubleMatrix(table);
	return 0;
}

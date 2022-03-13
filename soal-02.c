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

int main()
{
    char string[256];

    printf("Masukkan koefisien-koefisien : ");
    scanf("%[^\n]s", string);

    // Pembuatan tabel
    // ...

    // Penafsiran tabel
    // ...

    printf("Sistem stabil\n");
    printf("Sistem tidak stabil\n");
    printf("Sistem tidak stabil atau stabil marginal\n");

    return 0;
}

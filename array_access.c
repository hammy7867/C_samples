#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copyij(int size, int src[size][size], int dst[size][size]) {
        int i,j;
        for (i = 0; i < size; i++)
                for (j = 0; j < size; j++)
                        dst[i][j] = src[i][j];
}

void copyji(int size, int src[size][size], int dst[size][size]) {
        int i,j;
        for (j = 0; j < size; j++)
                for (i = 0; i < size; i ++)
                        dst[i][j] = src[i][j];
}

int main() {
        int i,j,size;
        clock_t t;
        time_t x;

        /* Get size of array from user */
        printf("What size of your square matrix?\n");
        scanf("%d", &size);
        printf("\n");

        /*Initialize src and dst arrays */
        srand((unsigned) time(&x));
        int src[size][size];
        int dst1[size][size];
        int dst2[size][size];

        for (i = 0; i < size; i++)
                for (j = 0; j < size; j++)
                        src[i][j] = (rand() % 100);

        /* Call copyij and measure execution time */
        t = clock();

        copyij(size, src, dst1);

        t = clock() - t;
        double copyij_time = ((double)t)/CLOCKS_PER_SEC; //In seconds
        printf("Copyij took %f seconds!\n\n", copyij_time);

        /* Call copyji and measure execution time */
        t = clock();

        copyji(size, src, dst2);

        t = clock() - t;
        double copyji_time = ((double)t)/CLOCKS_PER_SEC; //In seconds
        printf("Copyji took %f seconds!\n\n", copyji_time);
}

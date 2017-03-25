#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int A[], int p, int q, int r) {
        int i,j,k;
        int n1 = q - p + 1;
        int n2 = r - q;

        int L[n1+1];
        int R[n2+1];

        for (i = 1; i <= n1; i++) {
                L[i] = A[p + i - 1];
        }

        for (j = 1; j <= n2; j++) {
                R[j] = A[q + j];
        }

        L[n1+1] = 100;
        R[n2+1] = 100;

        i = j = 1;

        for (k = p; k <= r; k++) {
                if (L[i] <= R[j]) {
                        A[k] = L[i];
                        i = i + 1;
                }
                else {
                        A[k] = R[j];
                        j = j + 1;
                }
        }
}

void merge_sort(int A[], int p, int r) {
        if (p < r) {
                int q = (p + r) / 2;
                merge_sort(A, p, q);
                merge_sort(A, q + 1, r);
                merge(A, p, q, r);
        }
}

void insert_sort(int A[], int size) {
        int i,j;
        int key;

        for (j = 2; j <= size; j++) {
                key = A[j];
                i = j - 1;
                while (i > 0 && A[i] > key) {
                        A[i+1] = A[i];
                        i = i - 1;
                }
                A[i+1] = key;
        }
}

int main() {
        int i;
        clock_t t;
        time_t x;
        int size;

        /* Get size of array from user */
        printf("How many elements would you like to sort?\n");
        scanf("%d", &size);
        printf("\n");
        
        /* Initialize two identitcal arrays with random numbers */
        srand((unsigned) time(&x));
        int Array1[size+1];
        int Array2[size+1];

        for  (i = 1; i <= size; i++){
                Array1[i] = (rand() % 50);
        }

        for  (i = 1; i <= size; i++){
                Array2[i] = Array1[i];
        }

        /* Call to merge_sort, measure execution time */
        t = clock();

        merge_sort(Array1, 1, size);

        t = clock() - t;
        double merge_time = ((double)t)/CLOCKS_PER_SEC; //In seconds
        printf("Merge-sort took %f seconds!\n\n", merge_time);

        printf("First 10 elements of sorted Array 1:\n\n");
        for (i = 1; i <= 10; i++) {
                printf("%d, ", Array1[i]);
        }
        printf("\n\n");

        /* Call to insert_sort, measure execution time */
        t = clock();

        insert_sort(Array2, size);

        t = clock() - t;
        double insert_time = ((double)t)/CLOCKS_PER_SEC; //In seconds
        printf("Insertion-sort took %f seconds!\n\n", insert_time);

        printf("First 10 elements of sorted Array2:\n\n");
        for (i = 1; i <= 10; i ++) {
                printf("%d, ", Array2[i]);
        }
        printf("\n\n");

        if (merge_time < insert_time) {
                printf("Merge-sort won by %f seconds!\n", insert_time-merge_time);
        }
        else if (insert_time < merge_time) {
                printf("Insertion-sort won by %f seconds!\n", merge_time-insert_time);
        }
        else {
                printf("They tied!!!\n");
        }
}

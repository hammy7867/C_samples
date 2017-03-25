#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void max_heapify(int A[], int i, int size) {
        int largest, temp;
        int l = 2 * i;
        int r = 2 * i + 1;

        if ((l <= size) && (A[l] > A[i])) {
                largest = l;
        }

        else {
                largest = i;
        }

        if ((r <= size) && (A[r] > A[largest])) {
                largest = r;
        }

        if (largest != i) {
                temp = A[i];
                A[i] = A[largest];
                A[largest] = temp;
                max_heapify(A, largest, size);
        }
}

void build_max_heap(int A[], int size) {
        int i;

        for (i = size/2; i >= 1; i--) {
                max_heapify(A, i, size);
        }
}

void heap_sort(int A[], int size) {
        int i, temp;
        int newSize = size;

        build_max_heap(A, size);

        for (i = size; i >= 2; i--) {
                temp = A[1];
                A[1] = A[i];
                A[i] = temp;
                newSize = newSize - 1;
                max_heapify(A, 1, newSize);
        }
}

int main() {
        int i;
        int size = 10;
        time_t x;
        int Array[size+1];

        srand((unsigned) time(&x));
        
        for (i = 1; i  <= size; i++) {
                Array[i] = (rand() %50);
                printf("-> %d ", Array[i]);
        }
        printf("\n");

        heap_sort(Array, size);

        printf("Heapified:\n");

        for (i = 1; i <= size; i++) {
                printf("-> %d ", Array[i]);
        }
        printf("\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "quick_sort.h"
#include "common.h"

void swap(int *a, int i, int j)
{
    int temp;

    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(int *a, int low, int high, int size)
{
    int i, j;

    i = low-1;
    j = high+1;
    
    int highlights[2];

    while (1) {

        while (a[++i] < a[high] && i <= high);
        while (a[--j] > a[high] && j >= low);        

        if (i >= j) {
            break;
        } else {
            swap(a, i, j);
            
            highlights[0] = i;
            highlights[1] = j;
            print_int_array_matrix(a, size, highlights, 2);
        }
        // usleep(500);
    }

    highlights[0] = i;
    highlights[1] = j;
    print_int_array_matrix(a, size, highlights, 2);
    swap(a, i, high);
    return i;
}

static void _array_quick_sort(int *a, int low, int high, int size)
{
    if (high-low <= 0) {
        return;
    } else {
        // Pivot value is rightmost element
        int p = partition(a, low, high, size);
        _array_quick_sort(a, low, p-1, size);
        _array_quick_sort(a, p+1, high, size);
    }
}

void array_quick_sort(int *a, int size)
{
    if (size <= 1) 
        return;

    _array_quick_sort(a, 0, size, size);
}


void selection_sort(int *a, int size) 
{
    int i, j, min, temp;
    int highlights[2];

    for (i = 0; i < size-1; i++) {
        min = i;

        for (j = i+1; j < size; j++) {
            if (a[j] < a[min])
                min = j;
        }

        if (min != i) {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;

            highlights[0] = i;
            highlights[1] = min;
            print_int_array_matrix(a, size, highlights, 2);
        }
    }
}

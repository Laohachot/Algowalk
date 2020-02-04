#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "heap_sort.h"
#include "common.h"

/*
    [5, 9] [5, 31]
                                                                2
                                ________________________________|________________________________
                                7                                                               9
                ________________|_______________                                ________________|________________                      
                2                               8                               8                               9
        ________|_______                ________|________               ________|________               ________|________        
        6               6               8               5               7               9               6               7
    ____|____       ____|____       ____|____       ____|____       ____|____       ____|____       ____|____       ____|____
    2       4       2       0       9       8       4       4       2       5       9       0       4       2       4       5

                                                                                                

    [4, 7] [4, 15]
                                3
                ________________|________________
                5                               4
        ________|________               ________|________
        6               1               2               3
    ____|____       ____|____       ____|____       ____|____
    2       0       4       3       8       9       10      4       
                                               


    [3, 5] [3, 7]
                3
        ________|________
        5               4
    ____|____       ____|____
    6       1       2       3       



    [2, 3] [2, 3]
        3
    ____|____
    5       4           



    [1, 1] [1, 1]
    3

    2^n-1


*/

#define left(i)  (2 * (i) + 1)
#define right(i) (2 * (i) + 2)
#define parent(i)     (((i) - 1) / 2)

static int biggest_child(int *a, int i, int size)
{
    int biggest;

    biggest = left(i);

    if (right(i) < size && a[left(i)] < a[right(i)])
        biggest = right(i);

    return biggest;
}

/*
 * Creates max heap
 */
static void siftdown(int *a, int i, int size, int realsize)
{
    int biggest, firstparent, j;
    firstparent = a[i];
    
    int highlights[2];

    while (left(i) < size) {
        biggest = biggest_child(a, i, size);

        if (a[i] >= a[biggest]) {
            break;
        } 
        // print stuff
        highlights[0] = i;
        highlights[1] = biggest;
        print_int_array_matrix(a, realsize, highlights, 2);

        a[i] = a[biggest];
        i = biggest;
    }
    
    a[i] = firstparent;
}

static void heapify(int *a, int size, int realsize)
{
    for (int i = parent(size); i >= 0; i--) {
        siftdown(a, i, size, realsize);
    }
}

void array_heap_sort(int *a, int size)
{
    int i, temp;

    heapify(a, size-1, size);

    for (i = size-1; i > 0; i--) {
        
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, size);
    }

}

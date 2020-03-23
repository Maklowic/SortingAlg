#pragma once


/*Quick sort (sortowanie szybkie):
    left  - first element of the array[] to start sorting,
    right - last element of the array[].*/

// This function is all about swaping 2 elements of an array
template <typename Type>
void Swap(Type* array, int x1, int x2) {

    Type y = array[x1];
    array[x1] = array[x2];
    array[x2] = y;
}

//Function responsible for creating pivot
template<typename Type>
int Partition(Type* array, int left, int right) {

    Type pivot = array[(left + right) / 2];  //always in the middle
    int i = left - 1;
    int j = right + 1;

    while (1)
    {
        do {
            ++i;
        } while (array[i] < pivot);

        do {
            --j;
        } while (array[j] > pivot);

        if (i >= j) {
            return j;
        }

        Swap(array, i, j);
    }
}

//The implementation of Quicksort 
template<typename Type>
void Quicksort(Type* array, int left, int right) {

    if (left < right) {

        int pivot = Partition(array, left, right);
        Quicksort(array, left, pivot);
        Quicksort(array, pivot + 1, right);
    }
}

// This function is an ivert to function Partition
template <typename Type>
int InvertPartition(Type* array, int left, int right) {

    Type pivot = array[(right + left) / 2]; //always in the middle
    int i = left - 1;
    int j = right + 1;

    while (1) {
        do {
            ++i;
        } while (array[i] > pivot);

        do {
            --j;
        } while (array[j] < pivot);

        if (i >= j) {
            return j;
        }
        Swap(array, i, j);
    }
}

// This function is an ivert to function Quicksort
template<typename Type>
void InvertQuicksort(Type* array, int left, int right) {

    if (left < right) {

        int pivot = InvertPartition(array, left, right);
        InvertQuicksort(array, left, pivot);
        InvertQuicksort(array, pivot + 1, right);
    }
}

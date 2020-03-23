#pragma once
#include <math.h>
#include "QuickSort.h"

/*Heap sort (sortowanie przez kopcowanie)*/

template <typename Type>
void Heapify(Type* array, int heap_size, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && array[left] > array[largest]) {
        largest = left;
    }
    if (right < heap_size && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        Swap(array, i, largest);
        Heapify(array, heap_size, largest);
    }
}

/* left  - first element of the array[] to start sorting,
   right - last element of the array[].*/
template <typename Type>
void Heapsort(Type* array, int left, int right) {

    ++right;

    Type* tmp = new Type[right - left];
    for (int i = 0; i < (right - left); ++i) {
        tmp[i] = array[i + left];
    }

    for (int i = ((right - left) / 2) - 1; i >= 0; --i) {
        Heapify(tmp, (right - left), i);
    }
    for (int i = (right - left) - 1; i >= 0; --i) {
        Swap(tmp, 0, i);
        Heapify(tmp, i, 0);
    }

    for (int i = 0; i < (right- left); ++i) {
        array[i + left] = tmp[i];
    }
    delete[] tmp;
}

/*Insertion sort (sortowanie przez wstawianie):
    left  - first element of the array[] to start sorting,
    right - last element of the array[].*/
template <typename Type>
void Insertionsort(Type* array, int left, int right) {
    
    right++;

    int i = left;
    while (i < right) {

        int k = i;
        while (k > 0 && array[k - 1] > array[k]) {
            Swap(array, k, k - 1);
            --k;
        }
        ++i;
    }
}

/*Intro sort (sortowanie introspektywe):
    left  - first element of the array[] to start sorting,
    right - last element of the array[].*/
template <typename Type>
void IntrosortHybrid(Type* array, int left, int right, int maxdepth) {
    int size = right - left + 1;
    if (size <= 16) {
        Insertionsort(array, left, right);
    }
    else if (maxdepth == 0) {
        Heapsort(array, left, right);
    }
    else if (left < right) {
        int pivot = Partition(array, left, right);
        IntrosortHybrid(array, left, pivot, --maxdepth);
        IntrosortHybrid(array, pivot + 1, right, --maxdepth);
    }
}

template <typename Type>
void Introsort(Type* array, int left, int right) {

    int maxdepth = (int)log(right - left + 1) * 2;

    IntrosortHybrid(array, left, right, maxdepth);
}


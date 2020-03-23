#pragma once


/*MergeSort (sortowanie przez scalanie)
    left  - first element of the array[] to start sorting,
    right - last element of the array[].*/

    //Shredding array into smaller arrays
template <typename Type>
void Merge(Type* array, int left, int middle, int right) {

    Type* tmp = new Type[right - left + 1];
    int k = 0;
    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right) {
        if (array[i] <= array[j]) {
            tmp[k] = array[i];
            ++i;
        }
        else {
            tmp[k] = array[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle) {

        tmp[k] = array[i];
        ++i;
        ++k;
    }
    while (j <= right) {

        tmp[k] = array[j];
        ++j;
        ++k;
    }
    for (i = left; i <= right; ++i) {
        array[i] = tmp[i - left];
    }
    delete[] tmp;
}

// Implementation of Merge sorting
template <typename Type>
void Mergesort(Type* array, int left, int right) {

    if (left < right) {

        int middle = left + ((right - left) / 2);
        Mergesort(array, left, middle);
        Mergesort(array, middle + 1, right);
        Merge(array, left, middle, right);
    }
}

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>

#include "Mergesort.h"
#include "Quicksort.h"
#include "Introsort.h"

#define ARRAY_SIZE   5
#define ARRAY_NUMBER 100
#define TYPE int

using namespace std;

long array_length[5] = { 10000, 50000, 100000, 500000, 1000000 };

template <typename Type >
Type*** Array_create() {

    Type*** array = new Type**[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = new Type*[ARRAY_NUMBER];
        cout << "Creating " << ARRAY_NUMBER << " arrays of length " << array_length[i] << endl;

        for (int j = 0; j < ARRAY_NUMBER; ++j) {
            array[i][j] = new Type[array_length[i]];
            for (int k = 0; k < array_length[i]; ++k) {
                array[i][j][k] = rand();
            }
        }
    }
    return array;
}

template <typename Type>
void Array_delete(Type*** array) {

    if (array != nullptr) {
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            for (int j = 0; j < ARRAY_NUMBER; ++j) {
                delete[] array[i][j];
            }
            delete[] array[i];
            cout << "Arrays of length " << array_length[i] << " have been deleted."<<endl;
        }
        delete[] array;
    }
}

/* checks if arrays are sorted */
template <typename Type>
void Array_sorted(Type* array, int length) {

    bool sorted = true;
    for (int i = 0; i < length - 1; ++i) {
        if (array[i] > array[i + 1]) {
            sorted = false;
        }
    }
    switch (sorted) {

        case true: {
            cout << "  Sorted." << endl;
            break;
        }
        case false: {
            cout << "  NOT sorted." << endl;
            break;
        }
    }
}

/* checks if arrays are reverse sorted */
template <typename Type>
void Array_rev_sorted(Type* array, int length) {

    bool sorted = true;
    for (int i = 0; i < length - 1; ++i) {
        if (array[i] < array[i + 1]) {
            sorted = false;
        }
    }
    switch (sorted) {

        case true: {
            cout << " Reverse sorted." << endl;
            break;
        }
        case false: {
            cout << " NOT reverse sorted."<<endl;
            break;
        }
    }
}

/* Function - is a sorting function and takes 3 parameters: 
        1. Type* array - Type is from template.
        2. int left    - lefting index of the array.
        3. int right   - last index of the array.
   array is a 3 dimention array of elements, which first dimention is length of an array ARRAY_SIZE,
   secound is a index of an array ARRAY_NUMBER and third is for arrays elements. */
template <typename Function, typename Type>
void Array_do_sorting(Function fun, Type*** array) {

    ofstream file;
    if (fun == Quicksort) {
        file.open("result_Quicksort.csv");
    }
    if (fun == Mergesort) {
        file.open("result_Mergesort.csv");
    }
    if (fun == Introsort) {
        file.open("result_Introsort.csv");
    }

    /* double percent is helping to create arrays with percent elements sorted */
    double percent[] = { 0.25, 0.5, 0.75, 0.95, 0.99, 0.997 };

    chrono::duration<int, micro> span;
    chrono::duration<double, micro> MIN, MAX;

    Type*** tmp = new Type**[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        tmp[i] = new Type * [ARRAY_NUMBER];
        for (int j = 0; j < ARRAY_NUMBER; ++j) {
            tmp[i][j] = new Type[array_length[i]];
            for (int k = 0; k < array_length[i]; ++k) {
                tmp[i][j][k] = array[i][j][k];
            }
        }
    }
    file << "Ilosc danych;Czas sortowania 100 tablic;Minimum;Maximum" << endl;
    file << "0w ";
    MIN = MIN.max();
    MAX = MAX.zero();
    span = span.zero();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_NUMBER; ++j) {
            auto left = chrono::high_resolution_clock::now();
            fun(tmp[i][j], 0, array_length[i] - 1);
            auto right = chrono::high_resolution_clock::now();
            span += chrono::duration_cast <chrono::microseconds>(right - left);

            if (chrono::duration_cast<chrono::microseconds>(right - left) > MAX) {

                MAX = chrono::duration_cast<chrono::microseconds>(right - left);
            }
            if (chrono::duration_cast<chrono::microseconds>(right - left) < MIN) {

                MIN = chrono::duration_cast<chrono::microseconds>(right - left);
            }
        }
        file << ";" << array_length[i] << ";" << span.count() << ";" << MIN.count() << ";" << MAX.count() << endl;
        MIN = MIN.max();
        MAX = MAX.zero();
        span = span.zero();
    }

    // percent is the % of already sorted part of array
    for (int idx = 0; idx < 6; ++idx) {
        file << percent[idx];

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            for (int j = 0; j < ARRAY_NUMBER; ++j) {
                for (int k = 0; k < array_length[i]; ++k) {
                    tmp[i][j][k] = array[i][j][k];
                }
            }
        }

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            for (int j = 0; j < ARRAY_NUMBER; ++j) {

                fun(tmp[i][j], 0, (int)(array_length[i] * percent[idx]) - 1);
                auto left2 = chrono::high_resolution_clock::now();
                fun(tmp[i][j], 0, array_length[i] - 1);
                auto right2 = chrono::high_resolution_clock::now();
                span += chrono::duration_cast<chrono::microseconds>(right2 - left2);

                if (chrono::duration_cast<chrono::microseconds>(right2 - left2) > MAX) {

                    MAX = chrono::duration_cast<chrono::microseconds> (right2 - left2);
                }
                if (chrono::duration_cast<chrono::microseconds>(right2 - left2) < MIN) {

                    MIN = chrono::duration_cast<chrono::microseconds>(right2 - left2);
                }
            }
            file << ";" << array_length[i] << ";" << span.count() << ";" << MIN.count() << ";" << MAX.count() << endl;
            MIN = MIN.max();
            MAX = MAX.zero();
            span = span.zero();
        }
    }
    file << "Reverse";
    /* sorting the invert sorted array */
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_NUMBER; ++j) {
            for (int k = 0; k < array_length[i]; ++k) {

                tmp[i][j][k] = array[i][j][k];
            }
        }
    }
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_NUMBER; ++j) {
            InvertQuicksort(tmp[i][j], 0, array_length[i] - 1);
            auto left2 = chrono::high_resolution_clock::now();
            fun(tmp[i][j], 0, array_length[i] - 1);
            auto right2 = chrono::high_resolution_clock::now();
            span += chrono::duration_cast<chrono::microseconds>(right2 - left2);

            if (chrono::duration_cast<chrono::microseconds>(right2 - left2) > MAX) {

                MAX = chrono::duration_cast<chrono::microseconds>(right2 - left2);
            }
            if (chrono::duration_cast<chrono::microseconds>(right2 - left2) < MIN) {

                MIN = chrono::duration_cast<chrono::microseconds>(right2 - left2);
            }
        }
        file << ";" << array_length[i] << ";" << span.count() << ";" << MIN.count()
            << ";" << MAX.count() << endl;
        MIN = MIN.max();
        MAX = MAX.zero();
        span = span.zero();
    }
    Array_delete(tmp);
    cout << "Tmp deleted" << endl;
    file.close();
}

int main() {
    srand((unsigned int)time(NULL));

    int option;


    TYPE*** arrays = Array_create<TYPE>();
    do {
        cout << "|=================== MENU ===================|" << endl;
        cout << "|      Choose option:                        |" << endl;
        cout << "|  1. Merge Sort (sortowanie przez scalanie) |" << endl;
        cout << "|  2. Quick Sort (sortowanie szybkie)        |" << endl;
        cout << "|  3. Introsort  (sortowanie introspektywne) |" << endl;
        cout << "|  4. Recreating arrays to sort              |" << endl;
      //cout << "|  5. Display                                |" << endl;
        cout << "|                                            |" << endl;
        cout << "|  0. Exit                                   |" << endl;
        cout << "|============================================|" << endl;
        cout << "   Your choice:  ";
        cin >> option;
        cin.clear();
        cin.ignore(1000, '\n');

        switch (option) {
            case 1: {
                Array_do_sorting(Mergesort<TYPE>, arrays);
                break;
            }
            case 2: {
                Array_do_sorting(Quicksort<TYPE>, arrays);
                break;
            }
            case 3: {
                Array_do_sorting(Introsort<TYPE>, arrays);
                break;
            }
            case 4: {
                Array_delete(arrays);
                arrays = Array_create<TYPE>();
                break;
            }
            case 0: {
                Array_delete(arrays);
                cout << "Deleted every array!" << endl;
                return 0;
            }
            default: {
                cerr << "Error: Incorect option! Try again." << endl;
                option = -1;
                break;
            } 
        }
    } while (option != 0);
}






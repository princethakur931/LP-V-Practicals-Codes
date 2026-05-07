#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Merge Function
void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> temp;

    int i = l;
    int j = m + 1;

    while (i <= m && j <= r) {

        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= m)
        temp.push_back(arr[i++]);

    while (j <= r)
        temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[l + k] = temp[k];
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {

    if (l < r) {

        int m = (l + r) / 2;

        #pragma omp parallel sections
        {

            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Print Array
void printArray(vector<int>& arr) {

    for (int x : arr)
        cout << x << " ";

    cout << endl;
}

// Main Function
int main() {

    vector<int> arr = {5, 2, 9, 1, 3};

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;

    cout << "Original Array:\n";
    printArray(arr);

    parallelBubbleSort(arr1, arr1.size());

    cout << "\nParallel Bubble Sort:\n";
    printArray(arr1);

    parallelMergeSort(arr2, 0, arr2.size() - 1);

    cout << "\nParallel Merge Sort:\n";
    printArray(arr2);

    return 0;
}
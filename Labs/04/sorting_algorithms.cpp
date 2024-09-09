#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for(int j = 0; j < n - i -1; ++j) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}

void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for(int j = i + 1; j < n; ++j) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if(minIdx != i) {
            swap(arr[minIdx], arr[i]);
        }
    }
}

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int key = arr[i], j;            
            for (j = i; j >= gap && arr[j - gap] > key; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = key;
        }
    }
}

void combSort(int arr[], int n) {
    int gap = n;
    
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = static_cast<int>(gap / 1.3);
        if(gap < 1) gap = 1;
        
        swapped = false;

        for (int i = 0; i < n - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 5;
    int arr[n] = {9, 13, 3, 2, 5};

    cout << "Before sorting Array" << endl;
    printArray(arr, n);

    // bubbleSort(arr, n);
    // selectionSort(arr, n);
    // insertionSort(arr, n);
    // shellSort(arr, n);
    combSort(arr, n);

    cout << endl << "After sorting Array" << endl;
    printArray(arr, n);
}

#include <iostream>

using namespace std;

int getMax(int arr[], int n) {
    int maxi = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > maxi) {
            maxi = arr[i];
        }
    }
    return maxi;
}

void ascendingCountSort(int arr[], int n, int exp) {
    int count[10] = {0};
    int output[n] = {0};

    for(int i = 0; i < n; ++i) {
        ++count[(arr[i] / exp) % 10];
    }

    for(int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for(int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        --count[(arr[i] / exp) % 10];
    }

    for(int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void descendingCountSort(int arr[], int n, int exp) {
    int count[10] = {0};
    int output[n] = {0};

    for(int i = 0; i < n; ++i) {
        ++count[(arr[i] / exp) % 10];
    }

    for(int i = 8; i >= 0; --i) {
        count[i] += count[i + 1];
    }

    for(int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        --count[(arr[i] / exp) % 10];
    }

    for(int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void ascendingRadixSort(int arr[], int n) {
    int m = getMax(arr, n);

    for(int exp = 1; m / exp > 0; exp *= 10) {
        ascendingCountSort(arr, n, exp);
    }
}

void descendingRadixSort(int arr[], int n) {
    int m = getMax(arr, n);

    for(int exp = 1; m / exp > 0; exp *= 10) {
        descendingCountSort(arr, n, exp);
    }
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {36, 987, 654, 2, 20, 99, 456, 957, 555, 420, 66, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Given Array : ";
    printArray(arr, n);

    ascendingRadixSort(arr, n);

    cout << endl << "Ascending order : ";
    printArray(arr, n);

    descendingRadixSort(arr, n);
    
    cout << endl << "Descending order : ";
    printArray(arr, n);

    return 0;
}

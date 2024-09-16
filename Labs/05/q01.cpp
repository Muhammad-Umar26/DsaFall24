#include <iostream>

using namespace std;

void sort(int arr[], int n, int i = 0, int j = 1) {
    if(i == n - 1 || j == n) {
        return;
    }

    if(arr[i] > arr[j]) {
        swap(arr[i], arr[j]);
    }

    sort(arr, n, i, j + 1);

    sort(arr, n, i + 1, i + 2);
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {4, 8, 2, 3, 7, 5, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Before sorting" << endl;
    printArray(arr, n);

    sort(arr, n);

    cout << endl << "After sorting" << endl;
    printArray(arr, n);

    return 0;
}

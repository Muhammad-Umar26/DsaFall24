#include <iostream>

using namespace std;

int binarySearch(int arr[], int n, int target, int low, int high) {
    if(low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if(arr[mid] == target) return mid;

    arr[mid] < target ? low = mid + 1 : high = mid - 1;

    return binarySearch(arr, n, target, low, high);
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {1, 3, 7, 10, 12, 16, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 16;

    cout << "Given Array" << endl;
    printArray(arr, n);

    int index = binarySearch(arr, n, target, 0, n - 1);

    if(index != -1) {
        cout << endl << target << " found at index " << index;
    } else {
        cout << endl << target << " not found in given array";
    }
}

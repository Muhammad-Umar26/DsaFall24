#include <iostream>

using namespace std;

int linearSearch(int arr[], int n, int target) {
    for(int i = 0; i < n; ++i) {
        if(arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        
        if(arr[mid] == target) return mid;
        
        arr[mid] < target ? low = mid + 1 : high = mid - 1;
    }
    return -1;
}

int interpolationSearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        
        if(arr[pos] == target) return pos;
        
        arr[pos] < target ? low = pos + 1 : high = pos - 1;
    }
    return -1;
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 7;
    int arr[n] = {1, 3, 7, 10, 12, 16, 17};
    int target = 16;

    cout << "Given Array" << endl;
    printArray(arr, n);
    
    // int index = linearSearch(arr, n, target);
    // int index = binarySearch(arr, n, target);
    int index = interpolationSearch(arr, n, target);

    if(index != -1) {
        cout << endl << target << " found at index " << index;
    } else {
        cout << endl << target << " not found in given array";
    }
}

#include <iostream>

using namespace std;

int main() {
    int** jaggedArray = new int*[5];

    for(int i = 0, c = 1; i < 5; ++i) {
        jaggedArray[i] = new int[2 * (i + 1)];

        for(int j = 0; j < 2 * (i + 1); ++j) {
            jaggedArray[i][j] = c++;
        }
    }

    cout << "Before resizing" << endl;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 2 * (i + 1); ++j) {
            cout << jaggedArray[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < 5; ++i) {
        int* temp = new int[10];

        for(int j = 0; j < 10; ++j) {
            temp[j] = j < 2 * (i + 1) ? jaggedArray[i][j] : 0;
        }
        delete [] jaggedArray[i];
        jaggedArray[i] = temp;
    }

    cout << endl << "After resizing" << endl;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 10; ++j) {
            cout << jaggedArray[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < 5; ++i) {
        delete [] jaggedArray[i];
    }
    delete [] jaggedArray;

    return 0;
}

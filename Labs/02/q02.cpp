#include <iostream>

using namespace std;

int main() {
    int m1 = 2, n1 = 3, m2 = 3, n2 = 2;
    int matrix1[m1][n1] = {{1, 2, 3}, {4, 5, 6}};
    int matrix2[m2][n2] = {{7, 8}, {9, 10}, {11, 12}};
    int ans[m1][n2];
    
    if(n1 != m2) {
        cout << "Multiplication is not possible" << endl;
        return 0;
    }

    for(int i = 0; i < m1; ++i) {
        for(int j = 0; j < n2; ++j) {
            ans[i][j] = 0;
            for(int k = 0; k < n1; ++k) {
                ans[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    for(int i = 0; i < m1; ++i) {
        for(int j = 0; j < n2; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

#include <iostream>

using namespace std;

int nthFibonacci(int n) {
    if(n <= 2) return n - 1;

    return nthFibonacci(n - 1) + nthFibonacci(n - 2);
}

int main() {
    int n = 8;

    cout << n << "th Fibonacci number : " << nthFibonacci(n);

    return 0;
}

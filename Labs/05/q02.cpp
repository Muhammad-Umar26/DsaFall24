#include <iostream>

using namespace std;

int tailRecursionFactorial(int n, int ans = 1) {
    if(n < 2) return ans;

    return tailRecursionFactorial(n - 1, ans * n);
}

int nonTailRecursionFactorial(int n) {
    if(n < 2) return 1;

    return n * nonTailRecursionFactorial(n - 1);
}

int main() {
    int m = 5, n = 6;

    cout << "Factorial of " << m << " using tail recursion = " << tailRecursionFactorial(m) << endl;
    cout << "Factorial of " << n << " using non-tail recursion = " << nonTailRecursionFactorial(n) << endl;

    return 0;
}

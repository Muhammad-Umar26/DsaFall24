#include <iostream>
#include <vector>

using namespace std;

bool canPlace(vector<string>& board, int row, int col) {
    for(int i = row - 1, j = col - 1, k = col + 1; i >= 0; --i) {
        if(board[i][col] == 'Q' || (j >= 0 && board[i][j--] == 'Q') || (k < board.size() && board[i][k++] == 'Q')) {
            return false;
        }
    }
    return true;
}

bool solveNQueen(vector<string>& board, int row = 0) {
    if(row == board.size()) return true;

    for(int i = 0; i < board.size(); ++i) {
        if(canPlace(board, row, i)) {
            board[row][i] = 'Q';
            if(solveNQueen(board, row + 1)) {
                return true;
            }
            board[row][i] = '.';
        }
    }
    return false;
}

int main() {
    int n;

    cout << "Enter value of n : ";
    cin >> n;

    vector<string> board(n, string(n, '.'));

    if(solveNQueen(board)) {
        for(string& row : board) {
            for(char& c : row) {
                cout << c << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No possible solution for n equals to " << n << endl;
    }

    return 0;
}

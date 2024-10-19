#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<char>>& field, int row, int col) {
    if(row == -1 || row == field.size() || col == -1 || col == field.size() || field[row][col] == 'W' || field[row][col] == 'V') return 0;
    
    field[row][col] = 'V';
    
    return 1 + dfs(field, row + 1, col) + dfs(field, row - 1, col) + dfs(field, row, col + 1) + dfs(field, row, col - 1);
}

int largestForest(vector<vector<char>> field) {
    int maxSize = 0;
    for(int i = 0; i < field.size(); ++i) {
        for(int j = 0; j < field[i].size(); ++j) {
            if(field[i][j] == 'T') {
                maxSize = max(maxSize, dfs(field, i, j));
            }
        }
    }
    return maxSize;
}

int main() {
    vector<vector<char>> field = {
        {'T', 'T', 'T', 'W', 'W'},
        {'T', 'W', 'W', 'T', 'T'},
        {'T', 'W', 'W', 'T', 'T'},
        {'T', 'W', 'T', 'T', 'T'},
        {'W', 'W', 'T', 'T', 'T'},
    };
    
    cout << "Largest forest size : " << largestForest(field) << endl;
    
    return 0;
}

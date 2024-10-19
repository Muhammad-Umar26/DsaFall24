#include <iostream>
#include <vector>

using namespace std;

bool canMove(vector<vector<int>>& matrix, int row, int col) {
    return row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size() && matrix[row][col] == 1;
}

void ratInMaze(vector<vector<int>>& matrix, vector<string>& paths, string path = "", int row = 0, int col = 0) {
    if(row == matrix.size() - 1 && col == matrix[0].size() - 1) {
        paths.push_back(path);
        return;
    }

    if(canMove(matrix, row, col)) {
        matrix[row][col] = -1;

        ratInMaze(matrix, paths, path + 'D', row + 1, col);
        ratInMaze(matrix, paths, path + 'U', row - 1, col);
        ratInMaze(matrix, paths, path + 'R', row, col + 1);
        ratInMaze(matrix, paths, path + 'L', row, col - 1);
    
        matrix[row][col] = 1;
    }
}

int main() {
    vector<vector<int>> matrix = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1},
    };

    vector<string> paths;
    ratInMaze(matrix, paths);

    for(string& s : paths) {
        cout << s << endl;
    }

    return 0;
}

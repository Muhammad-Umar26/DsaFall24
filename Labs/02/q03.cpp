#include <iostream>

using namespace std;

bool haveCommonFriend(bool arr[][5], int person1, int person2) {
    for(int i = 0; i < 5; ++i) {
        if(i != person1 && i != person2 && arr[person1][i] && arr[person2][i]) {
            return true;
        }
    }
    return false;
}

int main () {
    bool arr[5][5] = {
        {false, true, false, true, true},
        {true, false, true, false, true},
        {false, true, false, false, false},
        {true, false, false, false, true},
        {true, true, false, true, false}
    };

    int person1 = 0, person2 = 4;

    if(haveCommonFriend(arr, person1, person2)) {
        cout << person1 << " and " << person2 << " have common friend(s)" << endl;
    } else {
        cout << person1 << " and " << person2 << " dont have common friends" << endl;
    }
    
    return 0;
}

#include <iostream>

#define size 10

using namespace std;

class Runner {
    string name;
    int finishTime;

    public:
        Runner() {}
        
        Runner(string name, int finishTime) : name(name), finishTime(finishTime) {}

        const string getName() {
            return name;
        }

        const int getFinishTime() {
            return finishTime;
        }
};

void merge(Runner runners[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = 0, length = high - low + 1;

    Runner* temp = new Runner[length];

    while(i <= mid || j <= high) {
        if(i <= mid && (j > high || runners[i].getFinishTime() <= runners[j].getFinishTime())) {
            temp[k++] = runners[i++];
        } else {
            temp[k++] = runners[j++];
        }
    }

    for(int index = 0; index < length; ++index) {
        runners[low + index] = temp[index];
    }

    delete [] temp;
}

void mergeSort(Runner runners[], int low, int high) {
    if(low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(runners, low, mid);
        mergeSort(runners, mid + 1, high);
        merge(runners, low, mid, high);
    }
}

void displayTop5(Runner runners[], int totalRunners) {
    cout << endl << "Top 5 fastest runners:" << endl;
    for(int i = 0; i < min(totalRunners, 5); ++i) {
        cout << i + 1 << ". " << runners[i].getName() << " - " << runners[i].getFinishTime() << " sesconds" << endl;
    }
}

int main() {
    int totalRunners = 10;

    Runner runners[totalRunners];

    cout << "Enter details of participants" << endl;
    for(int i = 0; i < totalRunners; ++i) {
        string name;
        int finishTime;

        cout << "Enter name and finish time for runner " << i + 1 << ": ";
        cin >> name >> finishTime;
        
        runners[i] = Runner(name, finishTime);
    }

    mergeSort(runners, 0, totalRunners - 1);

    displayTop5(runners, totalRunners);

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class Heap { // Min Heap
    vector<int> arr;

    public:
        void insert(int val) {
            arr.push_back(val);

            for(int i = arr.size() - 1, parent; i; i = parent) {
                parent = (i - 1) / 2;

                if(arr[i] < arr[parent]) {
                    swap(arr[i], arr[parent]);
                } else {
                    return;
                }
            }
        }

        void deleteVal() {
            if(arr.empty()) return;

            arr.front() = arr.back();
            arr.pop_back();

            for(int i = 0, smallest; i < arr.size(); i = smallest) {
                int left = 2 * i + 1, right = 2 * i + 2;
                smallest = i;

                if(left < arr.size() && arr[left] < arr[smallest]) {
                    smallest = left;
                }

                if(right < arr.size() && arr[right] < arr[smallest]) {
                    smallest = right;
                }

                if(smallest != i) {
                    swap(arr[i], arr[smallest]);
                } else {
                    return;
                }
            }
        }

        int size() {
            return arr.size();
        }

        bool empty() {
            return arr.empty();
        }

        int top() {
            return arr.empty() ? -1 : arr[0];
        }

        void print() {
            for(int& a : arr) {
                cout << a << " ";
            }
            cout << endl;
        }
};

vector<int> findKLargestElements(vector<int>& nums, int k) {
    Heap minHeap;
    for(int& num : nums) {
        minHeap.insert(num);

        if(minHeap.size() > k) minHeap.deleteVal();
    }

    vector<int> ans;
    while(!minHeap.empty()) {
        ans.push_back(minHeap.top());
        minHeap.deleteVal();
    }
    return ans;
}

int main() {
    vector<int> nums = {10, 4, 3, 50, 23, 90};
    int k = 3;

    cout << "Input array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Value of k: " << k << endl;

    vector<int> kLargest = findKLargestElements(nums, k);

    cout << "The " << k << " largest elements are: ";
    for (int num : kLargest) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

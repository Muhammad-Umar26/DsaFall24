#include <iostream>
#include <vector>

using namespace std;

class Heap { // Max Heap
    vector<pair<int, int>> arr;

    public:
        void insert(int val, int index) {
            arr.push_back({val, index});

            for(int i = arr.size() - 1, parent; i; i = parent) {
                parent = (i - 1) / 2;

                if(arr[i].first > arr[parent].first) {
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

            for(int i = 0, largest; i < arr.size(); i = largest) {
                int left = 2 * i + 1, right = 2 * i + 2;
                largest = i;

                if(left < arr.size() && arr[left].first > arr[largest].first) {
                    largest = left;
                }

                if(right < arr.size() && arr[right].first > arr[largest].first) {
                    largest = right;
                }

                if(largest != i) {
                    swap(arr[i], arr[largest]);
                } else {
                    return;
                } 
            }
        }

        bool empty() {
            return arr.empty();
        }

        pair<int, int> top() {
            return arr.empty() ? make_pair(-1, -1) : arr.front();
        }
};

vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    if(nums.empty()) return {};

    Heap maxHeap;
    for(int i = 0; i < k; ++i) {
        maxHeap.insert(nums[i], i);
    }

    vector<int> ans;
    ans.push_back(maxHeap.top().first);

    for(int i = k; i < nums.size(); ++i) {
        while(!maxHeap.empty() && maxHeap.top().second <= i - k) {
            maxHeap.deleteVal();
        }
        maxHeap.insert(nums[i], i);

        ans.push_back(maxHeap.top().first);
    }
    return ans;
}

int main() {
    vector<int> nums = {33, 38, 46, 24, 26, 6, 42, 28};
    int k = 2;

    cout << "Input array : ";
    for (int& num : nums) {
        cout << num << " ";
    }
    
    cout << endl << "Window size (k) : " << k << endl;

    vector<int> ans = slidingWindowMaximum(nums, k);

    cout << "Sliding window maximums : ";
    for (int& maxVal : ans) {
        cout << maxVal << " ";
    }
    cout << endl;

    return 0;
}

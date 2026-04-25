#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int s = 0;
        int n = arr.size();
        int e = n - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;
            if (arr[mid] < arr[mid + 1]) {
                s = mid + 1;
            } else {
                e = mid;
            }
        }
        return s;
    }
};

int main() {
    Solution obj;
    
    vector<int> arr = {0, 2, 5, 3, 1}; // example mountain array
    
    int peakIndex = obj.peakIndexInMountainArray(arr);
    
    cout << "Peak index: " << peakIndex << endl;
    
    return 0;
}
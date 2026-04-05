#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int max_area = 0;

        while (left < right) {

            max_area = max(max_area, min(height[left], height[right]) * (right - left));

        
            if (height[left] < height[right])
                ++left;   
            else
                --right;  
        }

        return max_area;
    }
};

int main() {
    Solution sol;
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << sol.maxArea(heights) << endl;  
    return 0;
}
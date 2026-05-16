#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st;

        for (int i = 2 * n - 1; i >= 0; i--) {
            int idx = i % n;

            while (!st.empty() && st.top() <= nums[idx]) {
                st.pop();
            }

            if (i < n) {
                ans[idx] = st.empty() ? -1 : st.top();
            }

            st.push(nums[idx]);
        }

        return ans;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {1, 2, 1};

    vector<int> res = obj.nextGreaterElements(nums);

    for (int x : res) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
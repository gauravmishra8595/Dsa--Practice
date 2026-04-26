#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> mp;
    mp.reserve(nums2.size());

    vector<int> st; 


    for (int i = nums2.size() - 1; i >= 0; i--) {
        while (!st.empty() && st.back() <= nums2[i]) {
            st.pop_back();
        }

        mp[nums2[i]] = st.empty() ? -1 : st.back();
        st.push_back(nums2[i]);
    }

    // Build result for nums1
    vector<int> ans(nums1.size());
    for (int i = 0; i < nums1.size(); i++) {
        ans[i] = mp[nums1[i]];
    }

    return ans;
}

int main() {
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};

    vector<int> result = nextGreaterElement(nums1, nums2);

    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

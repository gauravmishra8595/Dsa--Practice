#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        vector<int> nums;
        int fact = 1;

        // build numbers and factorial (n!)
        for (int i = 1; i <= n; i++)
        {
            nums.push_back(i);
            fact *= i;
        }

        k = k - 1; // convert to 0-based index
        string ans = "";

        for (int i = n; i >= 1; i--)
        {
            fact /= i;          // block size
            int idx = k / fact; // which number to pick
            k %= fact;

            ans += to_string(nums[idx]);
            nums.erase(nums.begin() + idx);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    int n = 4, k = 9;

    string result = sol.getPermutation(n, k);

    cout << "Permutation Sequence:\n";
    cout << result << endl;

    return 0;
}
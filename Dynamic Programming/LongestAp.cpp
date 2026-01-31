#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestAP(int A[], int n) {
        if (n <= 1) return n;

        vector<unordered_map<int,int>> dp(n);
        int ans = 2;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int diff = A[i] - A[j];

                if (dp[j].count(diff))
                    dp[i][diff] = dp[j][diff] + 1;
                else
                    dp[i][diff] = 2;

                ans = max(ans, dp[i][diff]);
            }
        }
        return ans;
    }
};

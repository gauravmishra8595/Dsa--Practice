#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int i = 0, j = 0;
        int count = 0;

        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i]) {
                count++;
                i++;
                j++;
            } else {
                j++;
            }
        }

        return count;
    }
};

int main() {
    Solution obj;

    vector<int> g = {1, 2, 3};   // greed factors
    vector<int> s = {1, 1};      // cookie sizes

    int result = obj.findContentChildren(g, s);

    cout << "Number of content children: " << result << endl;

    return 0;
}
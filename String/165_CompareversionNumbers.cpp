#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int compareVersion(string version1, string version2)
    {
        int n = version1.size();
        int m = version2.size();

        int i = 0, j = 0;

        while (i < n || j < m)
        {

            int num1 = 0, num2 = 0;

            // extract number from version1
            while (i < n && version1[i] != '.')
            {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }

            // extract number from version2
            while (j < m && version2[j] != '.')
            {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }

            // compare current revision
            if (num1 > num2)
                return 1;
            if (num1 < num2)
                return -1;

            // skip dots
            if (i < n && version1[i] == '.')
                i++;
            if (j < m && version2[j] == '.')
                j++;
        }

        return 0;
    }
};

int main()
{
    Solution sol;

    string version1, version2;
    cin >> version1 >> version2;

    cout << sol.compareVersion(version1, version2) << endl;

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (O(n + m) space, O(n + m) time)
========================================================
Idea:
- Split both strings by '.'
- Convert each part into integer
- Store in arrays
- Compare arrays index by index

Example:
"1.0.1" -> [1,0,1]
"1"     -> [1]

Then compare:
for i = 0 to max size:
    compare v1[i] and v2[i]

Problem:
- Extra space used for arrays
- Slower due to string splitting

--------------------------------------------------------

========================================================
OPTIMAL APPROACH (Two Pointers) - USED ABOVE
========================================================
Idea:
- Do NOT split string
- Use two pointers i and j
- Extract number on the fly between dots
- Compare each revision immediately

Why it works:
- Each segment is independent (separated by '.')
- Missing segments are treated as 0

Time Complexity: O(n + m)
Space Complexity: O(1)

Key Insight:
"1.0" == "1.0.0.0" because missing parts are treated as zero
========================================================
*/
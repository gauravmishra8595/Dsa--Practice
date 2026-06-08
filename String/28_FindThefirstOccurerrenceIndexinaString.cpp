#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int n = haystack.size();
        int m = needle.size();

        if (m == 0)
            return 0;

        for (int i = 0; i <= n - m; i++)
        {
            int j = 0;

            while (j < m && haystack[i + j] == needle[j])
            {
                j++;
            }

            if (j == m)
            {
                return i;
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;

    string haystack, needle;

    cout << "Enter haystack: ";
    getline(cin, haystack);

    cout << "Enter needle: ";
    getline(cin, needle);

    int result = sol.strStr(haystack, needle);

    cout << "Index of first occurrence: " << result << endl;

    return 0;
}
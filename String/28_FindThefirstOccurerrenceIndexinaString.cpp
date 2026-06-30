#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {

        // If needle is empty
        if (needle.empty())
            return 0;

        int n = haystack.size();
        int m = needle.size();

        // Check every possible starting position
        for (int i = 0; i <= n - m; i++)
        {

            int j = 0;

            // Compare characters
            while (j < m && haystack[i + j] == needle[j])
            {
                j++;
            }

            // Complete match found
            if (j == m)
                return i;
        }

        return -1;
    }
};

int main()
{

    string haystack, needle;

    cout << "Enter haystack string: ";
    cin >> haystack;

    cout << "Enter needle string: ";
    cin >> needle;

    Solution obj;

    int ans = obj.strStr(haystack, needle);

    cout << "First Occurrence Index = " << ans << endl;

    return 0;
}

/*
==========================
Brute Force Approach
==========================

Idea:

1. Try every possible starting position in haystack.
2. Compare the substring character by character.
3. If all characters match, return the starting index.
4. If no match is found, return -1.

Pseudo Code

for every possible index i

    compare haystack starting from i
    with needle

    if complete match
        return i

return -1

Time Complexity:
O((N - M + 1) * M)

N = Length of haystack
M = Length of needle

Worst Case:
O(N * M)

Space Complexity:
O(1)

--------------------------------------------------

Brute Force Code

int strStr(string haystack, string needle)
{
    int n = haystack.size();
    int m = needle.size();

    for(int i = 0; i <= n - m; i++)
    {
        int j = 0;

        while(j < m && haystack[i + j] == needle[j])
        {
            j++;
        }

        if(j == m)
            return i;
    }

    return -1;
}

==================================================
Optimal Approach (Implemented Above)
==================================================

Idea:

1. Traverse every valid starting position.
2. Compare characters one by one.
3. Return the first index where the entire needle matches.
4. If no match exists, return -1.

Example:

Haystack = "sadbutsad"
Needle   = "sad"

Compare from index 0
"sad" == "sad"

Answer = 0

Example:

Haystack = "leetcode"
Needle   = "leeto"

No complete match found.

Answer = -1

Time Complexity:
O((N - M + 1) * M)

Worst Case:
O(N * M)

Space Complexity:
O(1)

Note:

This is the standard interview solution.

For very large strings, algorithms like
KMP (Knuth-Morris-Pratt),
Rabin-Karp,
or Boyer-Moore can improve the worst-case time complexity.

LeetCode Problem:
28. Find the Index of the First Occurrence in a String
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> freq;

        for (char c : s)
        {
            freq[c]++;
        }

        priority_queue<pair<int, char>> pq;

        for (auto &it : freq)
        {
            pq.push({it.second, it.first});
        }

        string result = "";

        while (!pq.empty())
        {
            auto [f, ch] = pq.top();
            pq.pop();

            result.append(f, ch);
        }

        return result;
    }
};
    int main()
    {
        Solution obj;

        string s;
        cout << "Enter string: ";
        cin >> s;

        string ans = obj.frequencySort(s);

        cout << "Output: " << ans << endl;

        return 0;
    }
    /*
    =========================
    BRUTE FORCE APPROACH
    =========================
    1. Count frequency of characters
    2. Store in vector of pairs
    3. Sort by frequency (descending)
    4. Build result string

    Time Complexity: O(n log n)
    Space Complexity: O(n)
    */
    // string frequencySortBrute(string s)
    // {
    //     unordered_map<char, int> freq;

    //     for (char c : s)
    //     {
    //         freq[c]++;
    //     }

    //     vector<pair<char, int>> vec(freq.begin(), freq.end());

    //     sort(vec.begin(), vec.end(), [](auto &a, auto &b)
    //          { return a.second > b.second; });

    //     string result = "";

    //     for (auto &p : vec)
    //     {
    //         result.append(p.second, p.first);
    //     }

    //     return result;
    // }

    /*
    =========================
    OPTIMAL APPROACH (HEAP)
    =========================
    1. Count frequency
    2. Push (frequency, character) into max heap
    3. Pop heap and build result string

    Time Complexity: O(n log n)
    Space Complexity: O(n)
    */
   

/*
=========================
MAIN FUNCTION
=========================
*/

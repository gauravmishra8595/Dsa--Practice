#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int n = temperatures.size();

        vector<int> answer(n, 0);

        stack<int> st; // Stores indices

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--)
        {
            // Remove all smaller or equal temperatures
            while (!st.empty() && temperatures[st.top()] <= temperatures[i])
            {
                st.pop();
            }

            // Next warmer day exists
            if (!st.empty())
            {
                answer[i] = st.top() - i;
            }

            // Push current index
            st.push(i);
        }

        return answer;
    }
};

int main()
{
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    Solution obj;

    vector<int> result = obj.dailyTemperatures(temperatures);

    cout << "Output: ";

    for (int x : result)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

/*
=========================================
LeetCode 739 : Daily Temperatures
=========================================

Problem:

You are given an array temperatures.

For each day, find how many days
you have to wait until a warmer
temperature occurs.

If there is no future warmer day,
answer is 0.

Example:

Input:
temperatures = [73,74,75,71,69,72,76,73]

Output:
[1,1,4,2,1,1,0,0]

Explanation:

73 -> wait 1 day (74)
74 -> wait 1 day (75)
75 -> wait 4 days (76)
71 -> wait 2 days (72)
69 -> wait 1 day (72)
72 -> wait 1 day (76)
76 -> no warmer day
73 -> no warmer day

=========================================
Brute Force Approach
=========================================

Idea:

For every day:

1. Move towards the right.
2. Find the first warmer temperature.
3. Store the number of days.
4. If none found, answer = 0.

Algorithm:

For each index i

    Traverse j = i+1 to n-1

    If temperature[j] > temperature[i]

        answer[i] = j-i

        break

Otherwise answer[i] = 0

Code:

vector<int> dailyTemperatures(vector<int>& temperatures)
{
    int n = temperatures.size();

    vector<int> ans(n,0);

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(temperatures[j] > temperatures[i])
            {
                ans[i]=j-i;
                break;
            }
        }
    }

    return ans;
}

Time Complexity : O(N²)

Space Complexity : O(1)

=========================================
Optimal Approach (Monotonic Stack)
=========================================

Idea:

Instead of searching every time,
keep indices in a stack.

Traverse from right to left.

Remove all temperatures that are
smaller than or equal to the current
temperature because they can never
be the answer.

The stack top will always be the
nearest warmer temperature.

Store the distance and push the
current index.

Example:

temperatures =

[73,74,75,71,69,72,76,73]

Traverse from right.

Stack stores indices.

Current = 72

Stack Top = 76

Answer = distance = 1

Continue similarly.

=========================================
Dry Run
=========================================

temperatures =

[30,40,50,60]

Start from right.

60

Stack:
[60]

Answer = 0

--------------------------------

50

Top = 60

Warmer found

Answer = 1

Stack:

60
50

--------------------------------

40

Top = 50

Answer = 1

Stack:

60
50
40

--------------------------------

30

Top = 40

Answer = 1

Output:

[1,1,1,0]

=========================================
Time & Space Complexity
=========================================

Brute Force:

Time  : O(N²)

Space : O(1)

Optimal (Monotonic Stack):

Time  : O(N)

Each index is pushed and popped
only once.

Space : O(N)

=========================================
Interview Tip
=========================================

Whenever you see:

"Next Greater"
"Next Smaller"
"Previous Greater"
"Previous Smaller"

or

"Nearest Greater"

Think:

MONOTONIC STACK

Daily Temperatures is one of the
most famous applications of the
Monotonic Stack pattern.

Related Problems:

LeetCode 496
LeetCode 503
LeetCode 84
LeetCode 85

=========================================
*/

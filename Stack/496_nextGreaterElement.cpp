#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution
{
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> nextGreater;
        stack<int> st;

        // Find next greater element for every number in nums2
        for (int num : nums2)
        {
            while (!st.empty() && st.top() < num)
            {
                nextGreater[st.top()] = num;
                st.pop();
            }

            st.push(num);
        }

        // Remaining elements have no greater element
        while (!st.empty())
        {
            nextGreater[st.top()] = -1;
            st.pop();
        }

        vector<int> answer;

        for (int num : nums1)
        {
            answer.push_back(nextGreater[num]);
        }

        return answer;
    }
};

int main()
{
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};

    Solution obj;

    vector<int> result = obj.nextGreaterElement(nums1, nums2);

    cout << "Output: ";

    for (int num : result)
    {
        cout << num << " ";
    }

    cout << endl;

    return 0;
}

/*
=========================================
LeetCode 496 : Next Greater Element I
=========================================

Problem:

You are given two arrays:

nums1 and nums2

nums1 is a subset of nums2.

For every element in nums1,
find the first greater element
appearing to its right in nums2.

If no greater element exists,
return -1.

Example:

Input:
nums1 = [4,1,2]
nums2 = [1,3,4,2]

Output:
[-1,3,-1]

Explanation:

4 -> No greater element
1 -> Next greater is 3
2 -> No greater element

=========================================
Brute Force Approach
=========================================

Idea:

For every element in nums1:

1. Find its position in nums2.
2. Move towards the right.
3. Find the first greater element.
4. If not found, answer = -1.

Algorithm:

For each element x in nums1:

    Find index of x in nums2

    Traverse right side

    First element > x
    becomes answer

Otherwise answer = -1

Code:

vector<int> nextGreaterElement(vector<int>& nums1,
                               vector<int>& nums2)
{
    vector<int> ans;

    for (int x : nums1)
    {
        int idx = -1;

        for (int i = 0; i < nums2.size(); i++)
        {
            if (nums2[i] == x)
            {
                idx = i;
                break;
            }
        }

        int greater = -1;

        for (int j = idx + 1; j < nums2.size(); j++)
        {
            if (nums2[j] > x)
            {
                greater = nums2[j];
                break;
            }
        }

        ans.push_back(greater);
    }

    return ans;
}

Time Complexity: O(N * M)

N = size of nums1
M = size of nums2

Space Complexity: O(1)

=========================================
Optimal Approach (Monotonic Stack)
=========================================

Idea:

Instead of searching repeatedly,
precompute Next Greater Element
for every element in nums2.

Use a decreasing stack.

Whenever current element is greater
than stack top:

Current element becomes the
Next Greater Element of stack top.

Example:

nums2 = [1,3,4,2]

Stack:

1

3 arrives:
3 > 1
NGE(1) = 3

4 arrives:
4 > 3
NGE(3) = 4

2 arrives:
Push

Remaining:
NGE(4) = -1
NGE(2) = -1

Map:

1 -> 3
3 -> 4
4 -> -1
2 -> -1

Now answer nums1 in O(1).

=========================================
Dry Run
=========================================

nums1 = [2,4]

nums2 = [1,2,3,4]

Processing nums2:

Stack: []

1 -> push

Stack: [1]

2 -> NGE(1)=2

Stack: [2]

3 -> NGE(2)=3

Stack: [3]

4 -> NGE(3)=4

Stack: [4]

Remaining:

NGE(4)=-1

Map:

1 -> 2
2 -> 3
3 -> 4
4 -> -1

Answer:

2 -> 3
4 -> -1

Output:

[3,-1]

=========================================
Time & Space Complexity
=========================================

Brute Force:

Time  : O(N * M)
Space : O(1)

Optimal (Stack + HashMap):

Time  : O(N + M)

Each element is pushed and popped
at most once.

Space : O(M)

HashMap + Stack

=========================================
Interview Tip
=========================================

Whenever you see:

"Next Greater"
"Next Smaller"
"Previous Greater"
"Previous Smaller"

Think:

MONOTONIC STACK

This is the standard optimal pattern
for all Next Greater Element problems.

Related Problems:

LeetCode 503
LeetCode 739
LeetCode 84
LeetCode 85

=========================================
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        stack<int> st;

        vector<int> left(n);
        vector<int> right(n);

        for (int i = n - 1; i >= 0; i--)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();

            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        while (!st.empty())
            st.pop();

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();

            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            int width = right[i] - left[i] - 1;
            ans = max(ans, heights[i] * width);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> heights = {2, 1, 5, 6, 2, 3};

    cout << "Largest Rectangle Area: "
         << obj.largestRectangleArea(heights) << endl;

    return 0;
}

/*
=========================================
LeetCode 84: Largest Rectangle in Histogram
=========================================

BRUTE FORCE APPROACH
=========================================

Idea:
For every bar, expand left and right
until a smaller bar is found.

Steps:
1. Pick each index i
2. Move left until height >= current
3. Move right until height >= current
4. Compute area = height[i] * width

Time Complexity: O(n^2)
Space Complexity: O(1)

-----------------------------------------

Code:

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int left = i;
        int right = i;

        while (left > 0 && heights[left - 1] >= heights[i])
            left--;

        while (right < n - 1 && heights[right + 1] >= heights[i])
            right++;

        int width = right - left + 1;
        ans = max(ans, heights[i] * width);
    }

    return ans;
}

=========================================
OPTIMAL APPROACH (Monotonic Stack)
=========================================

Idea:
For each bar, find:
- First smaller element on LEFT
- First smaller element on RIGHT

These give boundaries of rectangle.

Then:
width = right[i] - left[i] - 1
area  = heights[i] * width

-----------------------------------------

Why Stack?
We use monotonic increasing stack:
to efficiently find next smaller element.

-----------------------------------------

Steps:
1. Find next smaller on right
2. Find next smaller on left
3. Compute max area using width formula

-----------------------------------------

Time Complexity: O(n)
Space Complexity: O(n)

=========================================
PATTERN:
=========================================

"Next Smaller Element + Monotonic Stack"

Very important for:
- Histogram problems
- Stock span
- Trapping rain water
- Subarray boundaries

=========================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> resultArray(vector<int> &nums)
    {
        vector<int> arr1, arr2;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        for (int i = 2; i < nums.size(); i++)
        {
            if (arr1.back() > arr2.back())
                arr1.push_back(nums[i]);
            else
                arr2.push_back(nums[i]);
        }

        for (int x : arr2)
            arr1.push_back(x);
        return arr1;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {2, 1, 3, 4, 5};
    vector<int> ans = sol.resultArray(nums);
    for (int x : ans)
        cout << x << " ";

    cout << '\n';

    return 0;
}

/*
================================================================================
PROBLEM STATEMENT
================================================================================

Given an array nums, split it into two arrays arr1 and arr2.

Initially:
    arr1 = [nums[0]]
    arr2 = [nums[1]]

For every element nums[i], where i >= 2:
    - If the last element of arr1 is greater than the last element of arr2,
      append nums[i] to arr1.
    - Otherwise, append nums[i] to arr2.

Finally, concatenate arr2 to the end of arr1 and return the result.

================================================================================
EXAMPLE
================================================================================

Input:
    nums = [2, 1, 3, 4, 5]

Process:
    arr1 = [2]
    arr2 = [1]

    nums[2] = 3:
        2 > 1  -> arr1 = [2, 3]

    nums[3] = 4:
        3 > 1  -> arr1 = [2, 3, 4]

    nums[4] = 5:
        4 > 1  -> arr1 = [2, 3, 4, 5]

Finally:
    arr1 + arr2
    = [2, 3, 4, 5] + [1]
    = [2, 3, 4, 5, 1]

Output:
    [2, 3, 4, 5, 1]

================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
    Simulate the process directly while repeatedly finding the last elements
    of both arrays. Since vectors provide O(1) access to their last elements,
    the straightforward simulation is already efficient.

Pseudo Code:

    create arr1 and arr2

    push nums[0] into arr1
    push nums[1] into arr2

    for i = 2 to n - 1:
        if last(arr1) > last(arr2):
            push nums[i] into arr1
        else:
            push nums[i] into arr2

    append all elements of arr2 to arr1

    return arr1

Complete Brute Force Code:

    class Solution
    {
    public:
        vector<int> resultArray(vector<int>& nums)
        {
            vector<int> arr1, arr2;

            arr1.push_back(nums[0]);
            arr2.push_back(nums[1]);

            for (int i = 2; i < nums.size(); i++)
            {
                if (arr1[arr1.size() - 1] > arr2[arr2.size() - 1])
                    arr1.push_back(nums[i]);
                else
                    arr2.push_back(nums[i]);
            }

            for (int x : arr2)
                arr1.push_back(x);

            return arr1;
        }
    };

Time Complexity:
    O(n)

Space Complexity:
    O(n)

================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
    We only need the last element of arr1 and arr2 to decide where the next
    element should go.

    Therefore, there is no need for any searching, sorting, or extra processing.

Intuition:
    Maintain two vectors exactly according to the rule.

    At every step:
        arr1.back() -> last element of arr1
        arr2.back() -> last element of arr2

    Compare them and append the current element to the appropriate vector.

    At the end, append arr2 to arr1.

Pseudo Code:

    arr1 = [nums[0]]
    arr2 = [nums[1]]

    for each nums[i], i >= 2:
        if arr1.back() > arr2.back():
            add nums[i] to arr1
        else:
            add nums[i] to arr2

    append arr2 to arr1

    return arr1

Complete Optimal Code:

    #include <bits/stdc++.h>
    using namespace std;

    class Solution
    {
    public:
        vector<int> resultArray(vector<int>& nums)
        {
            vector<int> arr1, arr2;

            arr1.push_back(nums[0]);
            arr2.push_back(nums[1]);

            for (int i = 2; i < nums.size(); i++)
            {
                if (arr1.back() > arr2.back())
                    arr1.push_back(nums[i]);
                else
                    arr2.push_back(nums[i]);
            }

            for (int x : arr2)
                arr1.push_back(x);

            return arr1;
        }
    };

Time Complexity:
    O(n)

Space Complexity:
    O(n)

================================================================================
DRY RUN WITH EXAMPLE
================================================================================

nums = [2, 1, 3, 4, 5]

Initial:
    arr1 = [2]
    arr2 = [1]

i = 2, nums[i] = 3:
    arr1.back() = 2
    arr2.back() = 1

    2 > 1 -> put 3 in arr1

    arr1 = [2, 3]
    arr2 = [1]

i = 3, nums[i] = 4:
    arr1.back() = 3
    arr2.back() = 1

    3 > 1 -> put 4 in arr1

    arr1 = [2, 3, 4]
    arr2 = [1]

i = 4, nums[i] = 5:
    arr1.back() = 4
    arr2.back() = 1

    4 > 1 -> put 5 in arr1

    arr1 = [2, 3, 4, 5]
    arr2 = [1]

Append arr2 to arr1:

    [2, 3, 4, 5] + [1]

Answer:
    [2, 3, 4, 5, 1]

================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
    Simulation / Two-Array Construction

Key Observation:
    Only the last element of each array matters for every decision.
    vector::back() gives this element in O(1).

Common Mistakes:
    1. Starting the loop from index 0 instead of index 2.
    2. Forgetting to initialize arr1 with nums[0].
    3. Forgetting to initialize arr2 with nums[1].
    4. Using >= instead of >.
    5. Forgetting to append arr2 to arr1 at the end.
    6. Accidentally sorting either array.

When to Use This Approach:
    Use this direct simulation whenever the problem explicitly defines how
    elements are distributed based on the current last elements/state of
    multiple containers.

================================================================================
*/
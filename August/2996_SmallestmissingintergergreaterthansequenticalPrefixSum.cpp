#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int missingInteger(vector<int> &nums)
    {
        unordered_set<int> st(nums.begin(), nums.end());

        int sum = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == nums[i - 1] + 1)
                sum += nums[i];
            else
                break;
        }

        while (st.count(sum))
            sum++;

        return sum;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 2, 3, 2, 5};

    int ans = obj.missingInteger(nums);

    cout << "Smallest Missing Integer : " << ans << endl;

    return 0;
}

/*

*==================================================*
*                    LEETCODE 2996                 *
*==================================================*

*==================================================*
*                 Problem Statement                 *
*==================================================*

*You are given a 0-indexed array nums.*

*A sequential prefix is a prefix of nums where every element*
*after the first is exactly 1 greater than the previous element.*

*Find the smallest integer x such that:*

*    x >= sum of the sequential prefix

*and x does not exist in nums.*

*-------------------------------------------------*
*Example*
*-------------------------------------------------*

*Input:*
*nums = {1,2,3,2,5}*

*Output:*
*6*

*Explanation:*

*Sequential prefix = {1,2,3}*

*Sum = 1 + 2 + 3 = 6*

*6 is not present in nums.*

*Therefore, answer = 6.*

*==================================================*
*               Brute Force Approach               *
*==================================================*

*Idea*
*----*

*1. Find the sequential prefix.*
*2. Calculate its sum.*
*3. Start from the sum.*
*4. For every candidate, scan the entire array*
*   to check whether it exists.*
*5. The first missing candidate is the answer.*

*-------------------------------------------------*
*Pseudo Code*
*-------------------------------------------------*

*sum = nums[0]*

*for i = 1 to n-1*
*    if nums[i] == nums[i-1] + 1*
*        sum += nums[i]*
*    else*
*        break*

*answer = sum*

*while answer exists in nums*
*    answer++*

*return answer*

*-------------------------------------------------*
*Complete Brute Force Code*
*-------------------------------------------------*

*class Solution {*
*public:*
*    int missingInteger(vector<int>& nums) {*
*        int sum = nums[0];*

*        for (int i = 1; i < nums.size(); i++) {*
*            if (nums[i] == nums[i - 1] + 1)*
*                sum += nums[i];*
*            else*
*                break;*
*        }*

*        int answer = sum;*

*        while (true) {*
*            bool found = false;*

*            for (int num : nums) {*
*                if (num == answer) {*
*                    found = true;*
*                    break;*
*                }*
*            }*

*            if (!found)*
*                return answer;*

*            answer++;*
*        }*
*    }*
*};*

*-------------------------------------------------*
*Time Complexity*
*-------------------------------------------------*

*O(n^2) in the worst case.*

*-------------------------------------------------*
*Space Complexity*
*-------------------------------------------------*

*O(1)*

*==================================================*
*                Optimal Approach                  *
*                  (Hash Set)                      *
*==================================================*

*Observation*
*-----------*

*We need to repeatedly check whether the current*
*number exists in nums.*

*Searching directly in the array takes O(n).*

*Using an unordered_set gives average O(1) lookup.*

*-------------------------------------------------*
*Intuition*
*-------------------------------------------------*

*First calculate the sum of the sequential prefix.*

*Then start from this sum.*

*If the number exists in the hash set, increment it.*

*The first number that does not exist is the answer.*

*-------------------------------------------------*
*Pseudo Code*
*-------------------------------------------------*

*Create hash set containing all elements.*

*sum = nums[0]*

*for i = 1 to n-1*
*    if nums[i] == nums[i-1] + 1*
*        sum += nums[i]*
*    else*
*        break*

*while sum exists in hash set*
*    sum++*

*return sum*

*-------------------------------------------------*
*Complete Optimal Code*
*-------------------------------------------------*

*class Solution {*
*public:*
*    int missingInteger(vector<int>& nums) {*
*        unordered_set<int> st(nums.begin(), nums.end());*

*        int sum = nums[0];*

*        for (int i = 1; i < nums.size(); i++) {*
*            if (nums[i] == nums[i - 1] + 1)*
*                sum += nums[i];*
*            else*
*                break;*
*        }*

*        while (st.count(sum))*
*            sum++;*

*        return sum;*
*    }*
*};*

*-------------------------------------------------*
*Time Complexity*
*-------------------------------------------------*

*Building hash set = O(n) average*

*Finding sequential prefix = O(n)*

*Finding missing integer = O(n) worst case*

*Overall = O(n) average.*

*-------------------------------------------------*
*Space Complexity*
*-------------------------------------------------*

*O(n) because of the hash set.*

*==================================================*
*                     Dry Run                     *
*==================================================*

*nums = {1,2,3,2,5}*

*Hash Set:*

*    {1,2,3,5}*

*Start:*

*    sum = 1*

*Check nums[1]:*

*    2 == 1 + 1*

*    sum = 1 + 2 = 3*

*Check nums[2]:*

*    3 == 2 + 1*

*    sum = 3 + 3 = 6*

*Check nums[3]:*

*    2 != 3 + 1*

*Sequential prefix ends.*

*Sequential prefix:*

*    {1,2,3}*

*Prefix Sum:*

*    6*

*Now check hash set:*

*    6 -> absent*

*Therefore:*

*    Answer = 6*

*==================================================*
*                 Interview Notes                 *
*==================================================*

*Pattern*
*-------*

*Sequential Prefix + Hash Set*

*-------------------------------------------------*
*Key Observation*
*-------------------------------------------------*

*The sequential prefix ends at the first index i where:*

*    nums[i] != nums[i-1] + 1*

*After calculating its sum, use a hash set to*
*perform fast membership checks.*

*-------------------------------------------------*
*Common Mistakes*
*-------------------------------------------------*

*1. Finding a subsequence instead of a prefix.*

*2. Sorting the array.*

*3. Continuing after the sequential prefix breaks.*

*4. Using linear search repeatedly, resulting in O(n^2).*

*5. Forgetting that answer starts from the prefix sum.*

*6. Missing the fact that duplicate values do not matter*
*   for hash-set membership checking.*

*-------------------------------------------------*
*When to use this approach*
*-------------------------------------------------*

*Use this approach when:*

*- A sequential/consecutive prefix is involved.*
*- We need the sum of that prefix.*
*- Multiple existence checks are required.*
*- Fast membership lookup is useful.*

*Core Pattern:*

*    Sequential Prefix*
*          ↓*
*       Prefix Sum*
*          ↓*
*       Hash Set*
*          ↓*
*   Check sum, sum+1...*
*          ↓*
*    First Missing Number*

*==================================================*

*/
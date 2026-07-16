#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    while (b)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);

        int mx = 0;
        for(int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            prefixGcd[i] = gcd(nums[i], mx);
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long ans = 0;
        int l = 0, r = n - 1;

        while(l < r) {
            ans += gcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }

        return ans;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {6, 4, 8, 2};

    cout << obj.gcdSum(nums) << endl;

    return 0;
}

/*

======================== PROBLEM STATEMENT ========================

You are given an integer array nums of length n.

Construct an array prefixGcd where:

mxi = maximum element from nums[0...i]
prefixGcd[i] = gcd(nums[i], mxi)

After constructing prefixGcd:

1. Sort it.
2. Pair the smallest with the largest.
3. Compute gcd of every pair.
4. If n is odd, ignore the middle element.
5. Return the sum of gcds of all pairs.

==================================================================

Example

Input:
nums = [6,4,8,2]

prefixGcd:
[6,2,8,2]

Sorted:
[2,2,6,8]

Pairs:
(2,8) -> gcd = 2
(2,6) -> gcd = 2

Answer = 4

==================================================================
BRUTE FORCE APPROACH
==================================================================

Idea

1. Construct prefixGcd.
2. Sort it.
3. Pair smallest with largest.
4. Compute gcd for every pair.

Although this is already efficient, we can consider repeatedly finding
minimum and maximum using linear search as a brute-force pairing.

Pseudo Code

Construct prefixGcd
Sort
while(elements remain):
    pick smallest
    pick largest
    ans += gcd(smallest, largest)

Complete Brute Force Code

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        vector<int> pre;

        int mx = 0;
        for(int x : nums){
            mx = max(mx, x);
            pre.push_back(gcd(x, mx));
        }

        sort(pre.begin(), pre.end());

        long long ans = 0;

        while(pre.size() > 1){
            ans += gcd(pre.front(), pre.back());
            pre.erase(pre.begin());
            pre.pop_back();
        }

        return ans;
    }
};

Time Complexity

Sorting : O(n log n)

Erase from front:
O(n)

Overall:
O(n^2)

Space Complexity

O(n)

==================================================================
OPTIMAL APPROACH
==================================================================

Observation

Only the sorted order matters for pairing.

Once sorted, smallest always pairs with largest.

No need to erase elements.

---------------------------------------------------------------

Intuition

Maintain two pointers.

Left -> smallest
Right -> largest

Compute gcd and move both pointers.

---------------------------------------------------------------

Pseudo Code

Construct prefixGcd

Sort prefixGcd

l = 0
r = n-1

while(l < r)
    ans += gcd(prefixGcd[l], prefixGcd[r])
    l++
    r--

return ans

---------------------------------------------------------------

Complete Optimal Code

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefixGcd(n);

        int mx = 0;

        for(int i=0;i<n;i++){
            mx=max(mx,nums[i]);
            prefixGcd[i]=gcd(nums[i],mx);
        }

        sort(prefixGcd.begin(),prefixGcd.end());

        long long ans=0;

        int l=0;
        int r=n-1;

        while(l<r){
            ans+=gcd(prefixGcd[l],prefixGcd[r]);
            l++;
            r--;
        }

        return ans;
    }
};

Time Complexity

Building prefix array : O(n log A)

Sorting : O(n log n)

Pairing : O(n log A)

Overall

O(n log n)

Space Complexity

O(n)

==================================================================
DRY RUN
==================================================================

nums

[6,4,8,2]

Step 1

mx=6
gcd(6,6)=6

mx=6
gcd(4,6)=2

mx=8
gcd(8,8)=8

mx=8
gcd(2,8)=2

prefixGcd

[6,2,8,2]

Sort

[2,2,6,8]

Pairs

2 8

gcd=2

2 6

gcd=2

Answer

4

==================================================================
INTERVIEW NOTES
==================================================================

Pattern

✔ Prefix Processing
✔ Sorting
✔ Two Pointers
✔ GCD

---------------------------------------------------------------

Key Observation

The pairing order is fixed after sorting.

Smallest always pairs with largest.

---------------------------------------------------------------

Common Mistakes

1. Forgetting to update prefix maximum.

2. Pairing adjacent elements instead.

3. Forgetting odd middle element is ignored.

4. Using erase() leading to O(n^2).

---------------------------------------------------------------

When to use this approach

Whenever:

• Prefix information is needed.
• Pairing depends only on sorted order.
• Two-pointer pairing is sufficient.
• Need optimal O(n log n) solution.

==================================================================

*/
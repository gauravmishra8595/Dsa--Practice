#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int best = 2;
        int left = 0;
        int product = 1;

        for (int right = 0; right < nums.size(); right++) {
            int x = nums[right];

            while (gcd(product, x) > 1) {
                product /= nums[left];
                left++;
            }

            product *= x;

            best = max(best, right - left + 1);
        }

        return best;
    }
};

int main() {
    Solution sol;

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << sol.maxLength(nums) << endl;

    return 0;
}

/*
============================================================
                  LEETCODE 3411
       MAXIMUM SUBARRAY WITH EQUAL PRODUCTS
============================================================

1. PROBLEM STATEMENT
--------------------

Given an array of positive integers nums.

An array is called product equivalent if:

    Product(arr) = LCM(arr) * GCD(arr)

Return the length of the longest product-equivalent
contiguous subarray.

CONSTRAINTS:
    2 <= nums.length <= 100
    1 <= nums[i] <= 10

------------------------------------------------------------

2. EXAMPLES
-----------

Example 1:
Input:
[1,2,1,2,1,1,1]

Output:
5

Explanation:
The longest product-equivalent subarray is
[1,2,1,1,1].

Example 2:
Input:
[2,3,4,5,6]

Output:
3

Explanation:
The longest valid subarray is [3,4,5].

Example 3:
Input:
[1,2,3,1,4,5,1]

Output:
5

------------------------------------------------------------

3. BRUTE FORCE APPROACH
-----------------------

IDEA:
Generate every possible contiguous subarray.

For each subarray:
1. Calculate product.
2. Calculate GCD.
3. Calculate LCM.
4. Check whether:

       product == gcd * lcm

5. Update maximum length.

PSEUDO CODE:

ans = 0

for i = 0 to n-1:

    for j = i to n-1:

        product = 1
        gcdVal = 0
        lcmVal = 1

        for k = i to j:

            product *= nums[k]

            gcdVal = gcd(gcdVal, nums[k])

            lcmVal = lcm(lcmVal, nums[k])

        if product == gcdVal * lcmVal:
            ans = max(ans, j-i+1)

return ans

COMPLETE BRUTE FORCE CODE:

    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {

                long long product = 1;
                long long g = 0;
                long long l = 1;

                for (int k = i; k <= j; k++) {

                    product *= nums[k];

                    g = gcd(g, (long long)nums[k]);

                    l = lcm(l, (long long)nums[k]);
                }

                if (product == g * l) {
                    ans = max(ans, j-i+1);
                }
            }
        }

        return ans;
    }

TIME COMPLEXITY:
O(N^3 * log M)

SPACE COMPLEXITY:
O(1)

Note:
Direct product calculation can cause integer
overflow for sufficiently large inputs.

------------------------------------------------------------

4. OPTIMAL APPROACH
-------------------

APPROACH:
Sliding Window + GCD

OBSERVATION:

For two positive integers:

    a * b = gcd(a,b) * lcm(a,b)

For a subarray of length >= 3, product equivalence
holds if and only if every pair of elements
is coprime.

Therefore, we need to maintain a window in which
all elements are pairwise coprime.

IMPORTANT:

    gcd(product, x) == 1

means the incoming element x is coprime with
every element represented by product.

INTUITION:

1. Maintain a sliding window [left, right].
2. Maintain the product of all elements in
   the current window.
3. Expand the window by adding nums[right].
4. Check gcd(product, nums[right]).
5. If GCD > 1, shrink the window from the left.
6. Divide the outgoing element from product.
7. Continue until the new element is coprime
   with the remaining window.
8. Multiply the new element into product.
9. Update the maximum window length.

Initialize best = 2 because every subarray
of length 1 or 2 is product equivalent.

PSEUDO CODE:

best = 2
left = 0
product = 1

for right = 0 to n-1:

    x = nums[right]

    while gcd(product, x) > 1:

        product = product / nums[left]

        left++

    product = product * x

    best = max(best, right-left+1)

return best

COMPLETE OPTIMAL CODE:

    int maxLength(vector<int>& nums) {

        int best = 2;
        int left = 0;
        int product = 1;

        for (int right = 0; right < nums.size(); right++) {

            int x = nums[right];

            while (gcd(product, x) > 1) {

                product /= nums[left];

                left++;
            }

            product *= x;

            best = max(best, right-left+1);
        }

        return best;
    }

TIME COMPLEXITY:

O(N * log P)

N = Number of elements.
P = Maximum product maintained in the window.

Each element enters and leaves the window
at most once.

SPACE COMPLEXITY:

O(1)

Only a few variables are maintained.

------------------------------------------------------------

5. DRY RUN WITH EXAMPLE
-----------------------

Input:

nums = [2,3,4,5,6]

Initially:

best = 2
left = 0
product = 1

right = 0:

x = 2

gcd(1,2) = 1

product = 1 * 2 = 2

Window = [2]
best = 2

right = 1:

x = 3

gcd(2,3) = 1

product = 2 * 3 = 6

Window = [2,3]
best = 2

right = 2:

x = 4

gcd(6,4) = 2

Not valid.

Remove nums[left] = 2

product = 6 / 2 = 3
left = 1

Now:

gcd(3,4) = 1

product = 3 * 4 = 12

Window = [3,4]
best = 2

right = 3:

x = 5

gcd(12,5) = 1

product = 12 * 5 = 60

Window = [3,4,5]
best = 3

right = 4:

x = 6

gcd(60,6) = 6

Not valid.

Remove nums[left] = 3

product = 60 / 3 = 20
left = 2

gcd(20,6) = 2

Not valid.

Remove nums[left] = 4

product = 20 / 4 = 5
left = 3

Now:

gcd(5,6) = 1

product = 5 * 6 = 30

Window = [5,6]
best = 3

FINAL ANSWER:

    3

------------------------------------------------------------

6. INTERVIEW NOTES
------------------

PATTERN:
Sliding Window + GCD + Number Theory

KEY OBSERVATION:

Instead of calculating product, GCD and LCM
for every subarray, use:

    gcd(product, newElement) == 1

to check whether the new element is coprime
with every element in the current window.

COMMON MISTAKES:

1. Forgetting to divide the outgoing element
   from product when shrinking the window.

2. Forgetting to update left after removing
   an element.

3. Checking only the GCD of the entire array
   instead of pairwise coprimality.

4. Forgetting that subarrays of length 2
   are always product equivalent.

5. Using an insufficient integer type for
   product in problems with larger constraints.

6. Confusing a subarray with a subsequence.

WHEN TO USE THIS APPROACH:

1. When solving longest valid subarray problems.
2. When adding an element can violate a condition.
3. When removing elements from the left restores
   the validity of the window.
4. When GCD can represent pairwise coprimality
   through the product of current elements.

IMPORTANT CONSTRAINT NOTE:

Here nums[i] <= 10 and nums.length <= 100.

The maximum possible product is:

    10^100

However, the sliding window contains pairwise
coprime elements, so its product is bounded
by the product of distinct primes up to 10.

For this problem, int is sufficient.

============================================================
                    END OF NOTES
============================================================
*/

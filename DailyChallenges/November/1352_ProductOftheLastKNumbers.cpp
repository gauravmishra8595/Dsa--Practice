#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers
{
private:
    vector<int> prefix;

public:
    ProductOfNumbers()
    {
        prefix.push_back(1);
    }

    void add(int num)
    {
        if (num == 0)
        {
            prefix.clear();
            prefix.push_back(1);
        }
        else
        {
            prefix.push_back(prefix.back() * num);
        }
    }

    int getProduct(int k)
    {
        int n = prefix.size();

        if (k >= n)
        {
            return 0;
        }

        return prefix.back() / prefix[n - k - 1];
    }
};

int main()
{
    ProductOfNumbers obj;

    obj.add(3);
    obj.add(0);
    obj.add(2);
    obj.add(5);
    obj.add(4);

    cout << obj.getProduct(2) << endl; // 20
    cout << obj.getProduct(3) << endl; // 40
    cout << obj.getProduct(4) << endl; // 0

    obj.add(8);

    cout << obj.getProduct(2) << endl; // 32

    return 0;
}

/*

============================================================
                 LEETCODE 1352
          PRODUCT OF THE LAST K NUMBERS
============================================================

PROBLEM STATEMENT:
------------------
Design a data structure that supports:

1. add(num):
   Adds the integer num to the stream.

2. getProduct(k):
   Returns the product of the last k numbers.

The product of any sequence containing zero is zero.

EXAMPLE:
--------
Input:
["ProductOfNumbers", "add", "add", "add", "add",
 "add", "getProduct", "getProduct", "getProduct",
 "add", "getProduct"]

[[], [3], [0], [2], [5], [4], [2], [3], [4], [8], [2]]

Output:
[null, null, null, null, null, null, 20, 40, 0, null, 32]


============================================================
                 BRUTE FORCE APPROACH
============================================================

IDEA:
-----
Store all inserted numbers in a vector.

Whenever getProduct(k) is called:
Traverse the last k elements and calculate their product.

PSEUDO CODE:
------------
add(num):
    push num into array

getProduct(k):
    product = 1

    for i = n-k to n-1:
        product *= arr[i]

    return product


COMPLETE BRUTE FORCE CODE:
--------------------------

class ProductOfNumbers {
private:
    vector<int> arr;

public:
    ProductOfNumbers() {}

    void add(int num) {
        arr.push_back(num);
    }

    int getProduct(int k) {
        int product = 1;

        int n = arr.size();

        for (int i = n-k; i < n; i++) {
            product *= arr[i];
        }

        return product;
    }
};


TIME COMPLEXITY:
----------------
add():
    O(1)

getProduct(k):
    O(k)

SPACE COMPLEXITY:
-----------------
O(n)

Where n = number of inserted elements.


============================================================
                  OPTIMAL APPROACH
============================================================

OBSERVATION:
------------
Consider the array:

[3, 2, 5, 4]

Prefix products:

[3, 6, 30, 120]

Product of last 2 numbers:

120 / 6 = 20

Product of last 3 numbers:

120 / 3 = 40

Therefore:

Product of last k elements =
    prefix.back() / prefix[n-k-1]


INTUITION:
---------
Use prefix products instead of calculating the product
again and again.

Maintain a prefix product array.

Initially:
prefix = [1]

For every non-zero number:
    prefix.push_back(prefix.back() * num)

SPECIAL CASE: ZERO
------------------
Division by zero is not possible.

Whenever zero arrives:
    Reset the prefix array to [1].

This means all products before the most recent zero
are no longer needed.

If k >= prefix.size():
    The requested range contains a zero.

Otherwise:
    Answer = prefix.back() / prefix[n-k-1]


PSEUDO CODE:
------------
Initialize:
    prefix = [1]

add(num):
    if num == 0:
        reset prefix to [1]
    else:
        prefix.push(prefix.back() * num)

getProduct(k):
    n = prefix.size()

    if k >= n:
        return 0

    return prefix[n-1] / prefix[n-k-1]


COMPLETE OPTIMAL CODE:
----------------------

class ProductOfNumbers {
private:
    vector<int> prefix;

public:
    ProductOfNumbers() {
        prefix.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            prefix.clear();
            prefix.push_back(1);
        } else {
            prefix.push_back(prefix.back() * num);
        }
    }

    int getProduct(int k) {
        int n = prefix.size();

        if (k >= n) {
            return 0;
        }

        return prefix.back() / prefix[n-k-1];
    }
};


TIME COMPLEXITY:
----------------
add(num):
    O(1)

getProduct(k):
    O(1)

SPACE COMPLEXITY:
-----------------
O(n)

Where n = number of non-zero elements after the
most recent zero.


============================================================
                    DRY RUN
============================================================

Operations:

add(3)
add(0)
add(2)
add(5)
add(4)

STEP 1:
-------
add(3)

prefix = [1, 3]

STEP 2:
-------
add(0)

Reset prefix.

prefix = [1]

STEP 3:
-------
add(2)

prefix = [1, 2]

STEP 4:
-------
add(5)

prefix = [1, 2, 10]

STEP 5:
-------
add(4)

prefix = [1, 2, 10, 40]


QUERY 1:
--------
getProduct(2)

n = 4

Answer = prefix[3] / prefix[1]

       = 40 / 2

       = 20

QUERY 2:
--------
getProduct(3)

Answer = prefix[3] / prefix[0]

       = 40 / 1

       = 40

QUERY 3:
--------
getProduct(4)

k >= n

Answer = 0

Because the last four numbers contain zero.


STEP 6:
-------
add(8)

prefix = [1, 2, 10, 40, 320]


QUERY 4:
--------
getProduct(2)

Answer = prefix[4] / prefix[2]

       = 320 / 10

       = 32


FINAL OUTPUT:
-------------
20
40
0
32


============================================================
                    INTERVIEW NOTES
============================================================

1. PATTERN:
-----------
Prefix Product / Prefix Sum style technique.

2. KEY OBSERVATION:
-------------------
The product of a subarray can be obtained by dividing
two prefix products.

Zeros require resetting the prefix product array.

3. COMMON MISTAKES:
-------------------
- Forgetting to handle zero.
- Dividing by zero.
- Using the wrong prefix index.
- Forgetting the initial prefix value of 1.
- Returning a product that includes elements before
  the most recent zero.

IMPORTANT CONSTRAINT NOTE:
--------------------------
LeetCode 1352 guarantees that the product of the
last k numbers fits in a 32-bit integer.

However, the cumulative prefix product can overflow
even when the requested answer fits in 32 bits.

For a fully general implementation, use a data structure
that avoids relying on potentially overflowing cumulative
products, such as a segment tree.

4. WHEN TO USE THIS APPROACH:
-----------------------------
Use this technique when:

- You need products of the last k elements.
- Elements are inserted dynamically.
- You need O(1) product queries.
- Zero can be handled by resetting the prefix state.

============================================================
                    END OF NOTES
============================================================

*/

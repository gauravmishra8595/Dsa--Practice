#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;

        for (int bill : bills) {
            if (bill == 5) {
                five++;
            }
            else if (bill == 10) {
                if (five == 0) return false;

                five--;
                ten++;
            }
            else { // bill == 20
                // Prefer one $10 + one $5.
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                // Otherwise use three $5 bills.
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution sol;

    vector<int> bills1 = {5, 5, 5, 10, 20};
    cout << sol.lemonadeChange(bills1) << '\n'; // 1

    vector<int> bills2 = {5, 5, 10, 10, 20};
    cout << sol.lemonadeChange(bills2) << '\n'; // 0

    vector<int> bills3 = {10};
    cout << sol.lemonadeChange(bills3) << '\n'; // 0

    return 0;
}

/*
================================================================================
                    LEETCODE 860 - LEMONADE CHANGE
================================================================================

Problem Statement:
------------------
At a lemonade stand, each lemonade costs $5.

Customers come one by one and pay using one of:

    $5, $10, or $20

You must give the correct change to every customer.

Initially, you have no money.

Return true if you can provide the correct change to every customer,
otherwise return false.


Example:
--------
Input:
    bills = [5, 5, 5, 10, 20]

Process:

Customer 1 pays $5:
    No change needed.
    $5 -> 1

Customer 2 pays $5:
    No change needed.
    $5 -> 2

Customer 3 pays $5:
    No change needed.
    $5 -> 3

Customer 4 pays $10:
    Need $5 change.
    Use one $5.
    $5 -> 2
    $10 -> 1

Customer 5 pays $20:
    Need $15 change.
    Give one $10 + one $5.
    $10 -> 0
    $5 -> 1

Answer:
    true


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
For every customer, determine whether we can make the required change.

The possible changes are:

    $5 customer  -> $0 change
    $10 customer -> $5 change
    $20 customer -> $15 change

For a $20 bill, we can give:

    $10 + $5

or:

    $5 + $5 + $5

A straightforward approach can try all possible combinations of available
bills to determine whether the required change can be formed.

Since the only denominations are $5, $10, and $20, we can simply check
all possible combinations.


Pseudo Code:
------------
five = 0
ten = 0

for each bill:

    if bill == 5:
        five++

    else if bill == 10:
        if five == 0:
            return false
        five--

    else if bill == 20:
        if ten > 0 AND five > 0:
            ten--
            five--
        else if five >= 3:
            five -= 3
        else:
            return false

return true


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> money;

        for (int bill : bills) {
            if (bill == 5) {
                money.push_back(5);
            }
            else if (bill == 10) {
                bool found = false;

                for (int i = 0; i < (int)money.size(); ++i) {
                    if (money[i] == 5) {
                        money.erase(money.begin() + i);
                        found = true;
                        break;
                    }
                }

                if (!found) return false;

                money.push_back(10);
            }
            else {
                bool found10 = false;
                bool found5 = false;
                int pos10 = -1, pos5 = -1;

                for (int i = 0; i < (int)money.size(); ++i) {
                    if (money[i] == 10 && !found10) {
                        found10 = true;
                        pos10 = i;
                    }

                    if (money[i] == 5 && !found5) {
                        found5 = true;
                        pos5 = i;
                    }
                }

                if (found10 && found5) {
                    if (pos10 > pos5) {
                        money.erase(money.begin() + pos10);
                        money.erase(money.begin() + pos5);
                    }
                    else {
                        money.erase(money.begin() + pos5);
                        money.erase(money.begin() + pos10);
                    }
                }
                else {
                    int count5 = 0;

                    for (int x : money) {
                        if (x == 5) count5++;
                    }

                    if (count5 < 3) return false;

                    int removed = 0;

                    for (int i = (int)money.size() - 1; i >= 0 && removed < 3; --i) {
                        if (money[i] == 5) {
                            money.erase(money.begin() + i);
                            removed++;
                        }
                    }
                }

                money.push_back(20);
            }
        }

        return true;
    }
};
*/

// Time Complexity:
// ----------------
// O(n^2) in the worst case because searching/removing bills from a vector
// can take O(n) for each customer.


// Space Complexity:
// -----------------
// O(n) for storing the received bills.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// Only $5 and $10 bills are useful for giving change.

// A $20 bill can never be used to give change because the required change
// is at most $15.

// Therefore, we only need to maintain:

//     five = number of $5 bills
//     ten  = number of $10 bills


// Intuition:
// ----------
// For a $10 bill:

//     Required change = $5

// So we must have one $5 bill.

// For a $20 bill:

//     Required change = $15

// There are two possibilities:

//     1. $10 + $5
//     2. $5 + $5 + $5

// We should ALWAYS prefer:

//     $10 + $5

// over:

//     $5 + $5 + $5

// Why?

// Because $5 bills are more valuable for future $10 customers.

// A future $10 customer can only receive a $5 bill as change.

// A $10 bill cannot be used to give change for a $10 customer.

// Therefore, preserve $5 bills whenever possible.


// Pseudo Code:
// ------------
// five = 0
// ten = 0

// for bill in bills:

//     if bill == 5:
//         five++

//     else if bill == 10:
//         if five == 0:
//             return false

//         five--
//         ten++

//     else:
//         // bill == 20

//         if ten > 0 AND five > 0:
//             ten--
//             five--

//         else if five >= 3:
//             five -= 3

//         else:
//             return false

// return true


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;

        for (int bill : bills) {

            if (bill == 5) {
                five++;
            }

            else if (bill == 10) {
                if (five == 0) return false;

                five--;
                ten++;
            }

            else { // bill == 20

                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// Each customer is processed exactly once.


// Space Complexity:
// -----------------
// O(1)

// Only two counters are maintained:

//     five
//     ten


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// Example:
//     bills = [5, 5, 5, 10, 20]


// Initial:
//     five = 0
//     ten = 0


// Customer 1:
//     bill = 5

//     No change required.

//     five = 1
//     ten = 0


// Customer 2:
//     bill = 5

//     No change required.

//     five = 2
//     ten = 0


// Customer 3:
//     bill = 5

//     No change required.

//     five = 3
//     ten = 0


// Customer 4:
//     bill = 10

//     Need $5 change.

//     five > 0

//     Give one $5:

//     five = 2
//     ten = 1


// Customer 5:
//     bill = 20

//     Need $15 change.

//     We have:
//         one $10
//         two $5

//     Prefer:
//         $10 + $5

//     After giving change:

//     five = 1
//     ten = 0


// All customers received correct change.

// Answer = true.


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Greedy Algorithm


// Key Observation:
// ----------------
// For a $20 bill, if possible, use:

//     $10 + $5

// instead of:

//     $5 + $5 + $5

// because $5 bills are more useful for future customers paying $10.


// Common Mistakes:
// ----------------
// 1. Using three $5 bills for a $20 customer when $10 + $5 is available.

// 2. Forgetting that a $10 customer requires exactly one $5 bill.

// 3. Tracking $20 bills even though they are never useful for giving change.

// 4. Returning true immediately after receiving a $20 without checking
//    whether $15 change can actually be produced.

// 5. Using brute force when only two counters are sufficient.


// When to Use This Approach:
// --------------------------
// Use this greedy pattern when:

// - Customers arrive sequentially.
// - Decisions must be made immediately.
// - Current choices affect future possibilities.
// - There is a clear locally optimal choice that preserves more useful
//   resources for the future.

// Here, preserving $5 bills is the key greedy decision.

// General Greedy Rule:

//     For $20:
//         Prefer $10 + $5
//         Otherwise use 5 + 5 + 5

// This gives the optimal O(n) time and O(1) space solution.


// ================================================================================
// */

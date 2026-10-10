#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalGas = 0, totalCost = 0;
        int start = 0, currGas = 0;

        for (int i = 0; i < (int)gas.size(); i++) {
            totalGas += gas[i];
            totalCost += cost[i];
            currGas += gas[i] - cost[i];

            if (currGas < 0) {
                start = i + 1;
                currGas = 0;
            }
        }

        return (totalGas < totalCost) ? -1 : start;
    }
};

int main() {
    Solution sol;

    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    cout << sol.canCompleteCircuit(gas, cost) << '\n';

    return 0;
}

/*
============================================================
LEETCODE 134: GAS STATION
============================================================

PROBLEM STATEMENT
-----------------
There are n gas stations arranged in a circular route.

gas[i] represents the gas available at station i.
cost[i] represents the gas required to travel from station i
to the next station.

A car starts with an empty tank. Find the starting station
index from which the car can complete the entire circuit.
Return -1 if it is impossible.

EXAMPLE
-------
gas  = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]

Output: 3

Explanation:
Start at station 3:
- Station 3: gain 4 - 1 = 3
- Station 4: gain 5 - 2 = 3; tank = 6
- Station 0: gain 1 - 3 = -2; tank = 4
- Station 1: gain 2 - 4 = -2; tank = 2
- Station 2: gain 3 - 5 = -2; tank = 0

The circuit is completed.

BRUTE FORCE APPROACH
--------------------

Idea:
- Try every station as a starting point.
- Simulate travelling through all n stations.
- If the tank becomes negative, that starting point fails.
- Return the first valid starting station.

Pseudo Code:
    for start from 0 to n - 1:
        tank = 0
        valid = true

        for step from 0 to n - 1:
            i = (start + step) % n
            tank += gas[i] - cost[i]

            if tank < 0:
                valid = false
                break

        if valid:
            return start

    return -1

Complete Brute Force Code (comments only):

    class BruteForceSolution {
    public:
        int canCompleteCircuit(vector<int>& gas,
                               vector<int>& cost) {
            int n = gas.size();

            for (int start = 0; start < n; start++) {
                int tank = 0;
                bool valid = true;

                for (int step = 0; step < n; step++) {
                    int i = (start + step) % n;
                    tank += gas[i] - cost[i];

                    if (tank < 0) {
                        valid = false;
                        break;
                    }
                }

                if (valid) return start;
            }

            return -1;
        }
    };

Time Complexity:
    O(n^2)

Space Complexity:
    O(1)

OPTIMAL APPROACH
----------------

Observation:
- If total gas is less than total cost, completing the circuit
  is impossible.
- If the current tank becomes negative at station i, no station
  between the current start and i can be a valid start.
- Therefore, the next candidate start is i + 1.

Intuition:
- Track the total gas and total cost for the entire circuit.
- Track the current gas balance from the candidate start.
- Whenever the current balance becomes negative, discard the
  current candidate and reset the balance.
- If total gas is sufficient, the final candidate is valid.

Pseudo Code:
    totalGas = 0
    totalCost = 0
    currGas = 0
    start = 0

    for i from 0 to n - 1:
        totalGas += gas[i]
        totalCost += cost[i]
        currGas += gas[i] - cost[i]

        if currGas < 0:
            start = i + 1
            currGas = 0

    if totalGas < totalCost:
        return -1

    return start

Complete Optimal Code (comments only):

    class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas,
                               vector<int>& cost) {
            int totalGas = 0, totalCost = 0;
            int start = 0, currGas = 0;

            for (int i = 0; i < (int)gas.size(); i++) {
                totalGas += gas[i];
                totalCost += cost[i];
                currGas += gas[i] - cost[i];

                if (currGas < 0) {
                    start = i + 1;
                    currGas = 0;
                }
            }

            return totalGas < totalCost ? -1 : start;
        }
    };

Time Complexity:
    O(n)

Space Complexity:
    O(1)

DRY RUN
-------

gas  = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]

Initially:
    totalGas = 0
    totalCost = 0
    currGas = 0
    start = 0

i = 0:
    gain = 1 - 3 = -2
    currGas = -2
    currGas < 0
    start = 1, currGas = 0

i = 1:
    gain = 2 - 4 = -2
    currGas = -2
    start = 2, currGas = 0

i = 2:
    gain = 3 - 5 = -2
    currGas = -2
    start = 3, currGas = 0

i = 3:
    gain = 4 - 1 = 3
    currGas = 3
    start remains 3

i = 4:
    gain = 5 - 2 = 3
    currGas = 6
    start remains 3

Totals:
    totalGas = 15
    totalCost = 15

Since totalGas >= totalCost:
    return start = 3

Output:
    3

INTERVIEW NOTES
---------------

Pattern:
    Greedy / Reset-on-Failure

Key Observation:
    If a journey starting at s fails at i, no station from s
    through i can be a valid starting point.

Common Mistakes:
    1. Forgetting to check totalGas < totalCost.
    2. Resetting currGas without updating start.
    3. Using the wrong index when simulating the circular route.
    4. Returning -1 whenever currGas becomes negative.
       A local failure does not imply global impossibility.
    5. Using int when constraints could cause integer overflow;
       use long long for totals if necessary.

When to Use This Approach:
    - A circular route must be completed.
    - Each position contributes a gain or loss.
    - A negative running balance invalidates a range of starts.
    - A global sum condition determines whether a solution exists.

============================================================
*/
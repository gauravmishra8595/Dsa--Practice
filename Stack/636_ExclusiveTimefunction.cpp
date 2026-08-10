#include <bits/stdc++.h>
using namespace std;

// LeetCode 636: Exclusive Time of Functions
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ans(n, 0);
        stack<int> st;
        int prevTime = 0;

        for (string& log : logs) {
            int p1 = log.find(':');
            int p2 = log.find(':', p1 + 1);

            int id = stoi(log.substr(0, p1));
            string type = log.substr(p1 + 1, p2 - p1 - 1);
            int time = stoi(log.substr(p2 + 1));

            if (type == "start") {
                if (!st.empty())
                    ans[st.top()] += time - prevTime;

                st.push(id);
                prevTime = time;
            } 
            else {
                ans[st.top()] += time - prevTime + 1;
                st.pop();

                prevTime = time + 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    int n = 2;
    vector<string> logs = {
        "0:start:0",
        "1:start:2",
        "1:end:5",
        "0:end:6"
    };

    vector<int> ans = sol.exclusiveTime(n, logs);

    for (int x : ans)
        cout << x << " ";

    cout << '\n';

    return 0;
}

/*
================================================================================
LeetCode 636 - Exclusive Time of Functions
================================================================================

Problem Statement:
------------------
There are n functions running on a single-threaded CPU.

Each function has a unique ID from 0 to n - 1.

The CPU logs function execution in the following format:

    "function_id:start_or_end:timestamp"

A function can call another function, creating a nested execution.

For every function, calculate its exclusive time:
the total time spent executing that function itself, excluding the time spent
executing functions that it called.

Important:
----------
"start" timestamp is inclusive.
"end" timestamp is also inclusive.

Return an array where ans[i] is the exclusive execution time of function i.


Example:
--------
Input:
n = 2

logs = [
    "0:start:0",
    "1:start:2",
    "1:end:5",
    "0:end:6"
]

Output:
[3, 4]

Explanation:

Function 0 runs at:
    time 0
    time 1

Function 1 runs from:
    time 2 through time 5

Function 0 resumes at:
    time 6

Therefore:

Function 0:
    0, 1, 6
    => 3 units

Function 1:
    2, 3, 4, 5
    => 4 units

Answer:
    [3, 4]


================================================================================
Brute Force Approach
================================================================================

Idea:
-----
Simulate every individual timestamp.

For each time unit, determine which function is currently running by processing
start and end events.

The function at the top of the stack is the currently executing function.

This approach works, but it can be inefficient because timestamps can be very
large. We do not need to process every individual time unit.

Pseudo Code:
------------
function exclusiveTime(n, logs):
    create ans[n]
    create stack

    for every timestamp from minimum time to maximum time:
        process all events at this timestamp
        current function = stack.top()
        add 1 to current function

    return ans

Complete brute force code (inside comments only):
--------------------------------------------------

// class SolutionBruteForce {
// public:
//     vector<int> exclusiveTime(int n, vector<string>& logs) {
//
//         vector<int> ans(n, 0);
//         stack<int> st;
//
//         int logIndex = 0;
//         int lastTime = stoi(logs[0].substr(logs[0].rfind(':') + 1));
//
//         // This is a conceptual brute-force simulation.
//         // It processes each individual time unit.
//
//         for (int t = lastTime; logIndex < logs.size(); t++) {
//
//             // Process all start/end events at current timestamp.
//             while (logIndex < logs.size()) {
//
//                 string log = logs[logIndex];
//
//                 int p1 = log.find(':');
//                 int p2 = log.find(':', p1 + 1);
//
//                 int id = stoi(log.substr(0, p1));
//                 string type = log.substr(p1 + 1, p2 - p1 - 1);
//                 int time = stoi(log.substr(p2 + 1));
//
//                 if (time != t)
//                     break;
//
//                 if (type == "start")
//                     st.push(id);
//                 else
//                     ; // End event is handled after this timestamp.
//
//                 logIndex++;
//             }
//
//             if (!st.empty())
//                 ans[st.top()]++;
//
//             // End events need to remove the finished function.
//             // A full implementation would maintain pending end events.
//
//             // This illustrates why direct timestamp simulation is
//             // unnecessarily complicated and inefficient.
//         }
//
//         return ans;
//     }
// };

Time Complexity:
----------------
O(T + L)

where:
    T = range of timestamps
    L = number of logs

This can be very large if timestamps are large.

Space Complexity:
-----------------
O(n) for the stack and answer array.


================================================================================
Optimal Approach
================================================================================

Observation:
------------
Only the moments when a function starts or ends matter.

We do NOT need to process every individual timestamp.

Maintain:

    stack<int> st

The stack stores currently active functions.

The function at the top is always the function currently executing.

Also maintain:

    prevTime

which represents the first timestamp that has not yet been accounted for.


Intuition:
----------
Consider:

    0:start:0
    1:start:2

Function 0 was running from time 0 up to time 1.

When function 1 starts at time 2:

    elapsed = 2 - prevTime
            = 2 - 0
            = 2

So we add 2 to function 0.

Then function 1 becomes the active function.

Now consider:

    1:end:5

Function 1 executes from time 2 through time 5.

Because the end timestamp is inclusive:

    elapsed = 5 - 2 + 1
            = 4

After function 1 finishes, the next unprocessed timestamp is:

    5 + 1 = 6

So:

    prevTime = time + 1


Key Rule:
---------
At a START event:

    Current function gets:
        time - prevTime

    Then push the new function.

At an END event:

    Current function gets:
        time - prevTime + 1

    Then pop the function.

    prevTime = time + 1


Pseudo Code:
------------
function exclusiveTime(n, logs):

    ans = array of n zeros
    stack = empty
    prevTime = 0

    for every log:

        parse id, type, time

        if type == "start":

            if stack is not empty:
                ans[stack.top()] += time - prevTime

            push id

            prevTime = time

        else:

            ans[stack.top()] += time - prevTime + 1

            pop stack

            prevTime = time + 1

    return ans


Complete optimal code (inside comments only):
----------------------------------------------

/*
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ans(n, 0);
        stack<int> st;
        int prevTime = 0;

        for (string& log : logs) {
            int p1 = log.find(':');
            int p2 = log.find(':', p1 + 1);

            int id = stoi(log.substr(0, p1));
            string type = log.substr(p1 + 1, p2 - p1 - 1);
            int time = stoi(log.substr(p2 + 1));

            if (type == "start") {
                if (!st.empty())
                    ans[st.top()] += time - prevTime;

                st.push(id);
                prevTime = time;
            }
            else {
                ans[st.top()] += time - prevTime + 1;
                st.pop();

                prevTime = time + 1;
            }
        }

        return ans;
    }
};
*/

// Time Complexity:
// ----------------
// O(L)

// where L = number of logs.

// Every log is processed exactly once.

// String parsing also takes O(length of log), which is effectively linear in the
// total input size.

// Space Complexity:
// -----------------
// O(n)

// The stack can contain at most n active functions, and the answer array has
// size n.


// ================================================================================
// Dry Run with Example
// ================================================================================

// n = 2

// logs:
//     0:start:0
//     1:start:2
//     1:end:5
//     0:end:6

// Initial:

// ans = [0, 0]
// stack = []
// prevTime = 0


// --------------------------------------------------
// Log: 0:start:0
// --------------------------------------------------

// Function 0 starts at time 0.

// Stack is empty, so nobody was running before it.

// Push 0.

// stack = [0]
// prevTime = 0

// ans = [0, 0]


// --------------------------------------------------
// Log: 1:start:2
// --------------------------------------------------

// Function 1 starts at time 2.

// Function 0 was running from:

//     time 0 to time 1

// Duration:

//     2 - 0 = 2

// Add 2 to function 0.

// ans = [2, 0]

// Push function 1.

// stack = [0, 1]

// prevTime = 2


// --------------------------------------------------
// Log: 1:end:5
// --------------------------------------------------

// Function 1 ends at time 5.

// Since end timestamp is inclusive:

//     duration = 5 - 2 + 1
//              = 4

// ans = [2, 4]

// Pop function 1.

// stack = [0]

// Next unprocessed time:

//     prevTime = 5 + 1
//              = 6


// --------------------------------------------------
// Log: 0:end:6
// --------------------------------------------------

// Function 0 ends at time 6.

// Duration:

//     6 - 6 + 1
//     = 1

// ans = [3, 4]

// Pop function 0.

// stack = []

// Final Answer:

//     [3, 4]


// ================================================================================
// Interview Notes
// ================================================================================

// Pattern:
// --------
// Stack + Interval / Event Simulation

// Key Observation:
// ----------------
// The stack represents the currently active nested function calls.

// The top of the stack is always the function consuming CPU time.

// Instead of processing every timestamp, process only START and END events.

// The most important formula is:

// START:
//     current function += currentTime - previousTime

// END:
//     current function += currentTime - previousTime + 1

// After END:
//     previousTime = currentTime + 1


// Common Mistakes:
// ----------------
// 1. Forgetting that the END timestamp is inclusive.

//    Wrong:
//        time - prevTime

//    Correct:
//        time - prevTime + 1

// 2. Forgetting to update prevTime after an END.

//    Correct:
//        prevTime = time + 1

// 3. Adding time to the newly started function instead of the previously
//    running function.

// 4. Forgetting that the stack top represents the currently executing function.

// 5. Popping before calculating the ending function's duration.

// 6. Processing every timestamp instead of only processing events.

// 7. Getting confused by nested function calls.

// Example:

//     0:start:0
//     1:start:2

// At time 2, function 0 stops executing because function 1 starts.


// When to use this approach:
// --------------------------
// Use this pattern when:

// - Events are nested.
// - A "start" event activates something.
// - An "end" event deactivates it.
// - The most recently started active item must finish first.
// - You need to calculate time/cost between events.

// Typical pattern:

//     Start -> Push
//     End   -> Calculate + Pop

// This is a classic stack-based event simulation problem.


// ================================================================================
// */
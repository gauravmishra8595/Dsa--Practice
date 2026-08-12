#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countStudents(vector<int> &students, vector<int> &sandwiches)
    {
        int count[2] = {0, 0};

        for (int student : students)
        {
            count[student]++;
        }

        for (int sandwich : sandwiches)
        {
            if (count[sandwich] == 0)
                break;

            count[sandwich]--;
        }

        return count[0] + count[1];
    }
};

int main()
{
    Solution obj;

    vector<int> students = {1, 1, 0, 0};
    vector<int> sandwiches = {0, 1, 0, 1};

    cout << "Students Unable to Eat: "
         << obj.countStudents(students, sandwiches)
         << endl;

    return 0;
}

/*
=========================================*
LeetCode 1700: Number of Students Unable
to Eat Lunch
=========================================*

Problem Statement:
------------------
There are n students in a queue and n sandwiches in a stack.

Each student prefers either:

0 -> Circular sandwich
1 -> Square sandwich

Rules:

1. The student at the front checks the top sandwich.
2. If the student prefers it, they take it and leave.
3. Otherwise, they move to the end of the queue.

Return the number of students who are unable to eat.

=========================================*
Example:
=========================================*

Input:

students   = [1,1,0,0]
sandwiches = [0,1,0,1]

Output:

0

=========================================*
Brute Force Approach
=========================================*

Idea:
-----
Use a queue and simulate the process.

If the front student does not want the current
sandwich, move that student to the back.

If nobody takes the sandwich after one complete
round, stop the process.

Pseudo Code:
------------

Create queue using students.

For every sandwich:

    Try every student currently in queue.

    If student wants sandwich:
        Remove student.
        Move to next sandwich.
        Break.

    Otherwise:
        Move student to back.

    If nobody took sandwich:
        Break.

Return queue size.

Complete Brute Force Code:
--------------------------

int countStudents(vector<int>& students,
                  vector<int>& sandwiches)
{
    queue<int> q;

    for (int student : students)
        q.push(student);

    int index = 0;

    while (!q.empty() && index < sandwiches.size())
    {
        int size = q.size();
        bool eaten = false;

        for (int i = 0; i < size; i++)
        {
            int student = q.front();
            q.pop();

            if (student == sandwiches[index])
            {
                index++;
                eaten = true;
                break;
            }

            q.push(student);
        }

        if (!eaten)
            break;
    }

    return q.size();
}

Time Complexity:
----------------
O(n²)

Space Complexity:
-----------------
O(n)

=========================================*
Optimal Approach
=========================================*

Observation:
------------
There are only two types of students:

0 -> Want sandwich 0
1 -> Want sandwich 1

So we only need to count how many students
want each type.

count[0] -> Students wanting 0
count[1] -> Students wanting 1

Intuition:
----------
If at least one student wants the current sandwich,
that student will eventually reach the front and
take the sandwich.

Therefore, we do not need to simulate the queue.

If:

count[sandwich] == 0

then nobody wants the current sandwich, so the
process stops.

Pseudo Code:
------------

count[0] = 0
count[1] = 0

For every student:
    count[student]++

For every sandwich:
    If count[sandwich] == 0:
        break

    count[sandwich]--

Return count[0] + count[1]

Complete Optimal Code:
----------------------

class Solution
{
public:
    int countStudents(vector<int>& students,
                      vector<int>& sandwiches)
    {
        int count[2] = {0, 0};

        for (int student : students)
        {
            count[student]++;
        }

        for (int sandwich : sandwiches)
        {
            if (count[sandwich] == 0)
                break;

            count[sandwich]--;
        }

        return count[0] + count[1];
    }
};

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)

=========================================*
Dry Run
=========================================*

students   = [1,1,0,0]
sandwiches = [0,1,0,1]

Initial:

count[0] = 2
count[1] = 2

Sandwich = 0

count[0] = 2
One student eats.

count[0] = 1

Sandwich = 1

count[1] = 2
One student eats.

count[1] = 1

Sandwich = 0

count[0] = 1
One student eats.

count[0] = 0

Sandwich = 1

count[1] = 1
One student eats.

count[1] = 0

Final:

count[0] + count[1] = 0

Answer = 0

=========================================*
Interview Notes:
=========================================*

Pattern:
--------
Frequency Counting + Greedy

Key Observation:
----------------
If at least one student wants the current sandwich,
that sandwich will eventually be eaten.

If nobody wants it, the process stops.

Common Mistakes:
----------------
1. Simulating the queue unnecessarily.
2. Forgetting to stop when count[sandwich] == 0.
3. Returning the number of sandwiches instead of
   the remaining students.
4. Using O(n) extra space unnecessarily.

When to use this approach:
--------------------------
Use frequency counting when:

- There are only a few possible categories.
- Exact ordering does not affect the result.
- Only frequency information is required.

=========================================*
Complexity Summary:
=========================================*

Brute Force:
Time  -> O(n²)
Space -> O(n)

Optimal:
Time  -> O(n)
Space -> O(1)

=========================================*
Interview Tip:
=========================================*

Instead of simulating the queue, count the
students who prefer each sandwich type.

Since there are only two types, two counters
are enough.

=========================================*
*/
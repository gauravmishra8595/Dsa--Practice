#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string countAndSay(int n)
    {
        // Base case
        string ans = "1";

        // Generate strings from 2 to n
        for (int i = 2; i <= n; i++)
        {
            string previous = ans;
            ans = "";

            int length = previous.size();
            int j = 0;

            while (j < length)
            {
                int count = j;

                // Count consecutive same characters
                while (count < length &&
                       previous[count] == previous[j])
                {
                    count++;
                }

                // Append frequency
                ans += to_string(count - j);

                // Append digit
                ans += previous[j];

                // Move to next group
                j = count;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    int n;
    cin >> n;

    cout << sol.countAndSay(n);

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (Recursive)
========================================================

Idea:
- Generate the previous term recursively.
- Scan the previous string.
- Count consecutive digits.
- Form the current string.
- Repeat until nth term.

Example:

n = 5

countAndSay(4)
      |
      v
"1211"

Read:
1 -> one 1  -> 11
2 -> one 2  -> 12
11 -> two 1 -> 21

Result = "111221"

Pseudo Code:

string countAndSay(n)
{
    if(n == 1)
        return "1";

    previous = countAndSay(n-1);

    return build(previous);
}

Problems:
---------
• Uses recursion stack.
• Function call overhead.
• Slightly slower than iterative solution.

Time Complexity:
O(n × L)

Space Complexity:
O(n + L)

where
n = recursion depth
L = maximum generated string length

========================================================
OPTIMAL APPROACH (Iterative) - USED ABOVE
========================================================

Idea:
Instead of recursion, generate every term one by one.

Start with

ans = "1"

For every iteration:

1. Store previous string.
2. Traverse previous string once.
3. Count consecutive equal digits.
4. Append

   frequency + digit

5. Continue until entire string is processed.

Example:

Previous = "111221"

Read:

111 -> 31
22  -> 22
1   -> 11

Answer

312211

--------------------------------------------------------

Dry Run (n = 5)

Initially

ans = "1"

Iteration 2

Previous = "1"

One '1'

ans = "11"

--------------------------------

Iteration 3

Previous = "11"

Two '1'

ans = "21"

--------------------------------

Iteration 4

Previous = "21"

One '2'
One '1'

ans = "1211"

--------------------------------

Iteration 5

Previous = "1211"

One '1'
One '2'
Two '1'

ans = "111221"

Final Answer

111221

========================================================

Why is this Optimal?

✔ No recursion
✔ No extra arrays
✔ Single traversal of each generated string
✔ Constant extra space (excluding answer string)
✔ Faster due to no recursive calls

Time Complexity:
O(n × L)

where
n = number of iterations
L = length of the generated string

Space Complexity:
O(L)

Only the previous and current strings are stored.

========================================================*/
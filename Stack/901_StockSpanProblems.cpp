#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class StockSpanner
{
private:
    stack<pair<int, int>> st;
    // Stores {price, span}

public:
    StockSpanner()
    {
        // Constructor
    }

    int next(int price)
    {

        int span = 1;
        // Every stock has at least a span of 1 (today itself).

        while (!st.empty() && st.top().first <= price)
        {

            span += st.top().second;
            // Add the span of the popped element because
            // all those previous days are also <= current price.

            st.pop();
        }

        st.push({price, span});
        // Store the current price along with its computed span.

        return span;
    }
};

int main()
{

    StockSpanner obj;

    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};

    cout << "Stock Spans:\n";

    for (int price : prices)
    {
        cout << obj.next(price) << " ";
    }

    cout << endl;

    return 0;
}

/*
===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
For every new stock price, keep moving backwards
until you find a price greater than the current price.

Example:

Prices:
100 80 60 70 60 75 85

Current Price = 85

Start from previous day

75 <= 85  -> count++
60 <= 85  -> count++
70 <= 85  -> count++
60 <= 85  -> count++
80 <= 85  -> count++
100 > 85  -> Stop

Answer = 6


Pseudo Code:

span = 1

for(i = currentIndex-1; i >= 0; i--)
{
    if(price[i] <= currentPrice)
        span++;
    else
        break;
}

Time Complexity:
Worst Case = O(N) for one query

If there are N queries:

O(N²)

Not efficient.


===========================================================
OPTIMAL APPROACH (MONOTONIC STACK)
===========================================================

Observation:

Suppose we have processed

100 80 60 70 60 75

When current price = 85

We know

75 <= 85

The span of 75 is already 4.

Those 4 days are

60
70
60
75

Since

75 <= 85

All four days automatically satisfy

dayPrice <= 85

Instead of checking them individually,
we directly add span = 4.

This avoids repeated comparisons.


===========================================================
WHY STORE (PRICE, SPAN)?
===========================================================

Stack stores

(price, span)

Example Stack

(100,1)
(80,1)
(75,4)

Notice

60
70
60

are removed.

Reason:

75 already represents all of them.

Future larger prices don't need to visit
those elements individually.


===========================================================
WHY MONOTONIC STACK?
===========================================================

The stack always remains in decreasing order
of stock prices.

Example

Insert 100

Stack

100


Insert 80

100
80


Insert 60

100
80
60


Insert 70

70 is greater than 60

Pop 60

Stack

100
80

Push 70

100
80
70

Still decreasing.


===========================================================
ALGORITHM
===========================================================

next(price)

span = 1

while stack is not empty
and top.price <= current price

    span += top.span
    pop

push(current price, span)

return span


===========================================================
TIME COMPLEXITY
===========================================================

Each stock price is

Pushed exactly once.

Popped at most once.

Suppose there are N prices.

Push Operations = N

Pop Operations <= N

Total Operations <= 2N

Overall Complexity = O(N)

Per query (Amortized) = O(1)


===========================================================
SPACE COMPLEXITY
===========================================================

Worst Case

Prices are strictly decreasing

100
90
80
70
60

Nothing gets popped.

Stack stores every element.

Space Complexity = O(N)

===========================================================
*/
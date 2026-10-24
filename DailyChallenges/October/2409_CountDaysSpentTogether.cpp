#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int findDayOfYear(string date, vector<int> &cumMonthDays)
    {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        return cumMonthDays[month - 1] + day;
    }
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob)
    {
        vector<int> monthDays = {31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};

        vector<int> cumMonthDays(13, 0);

        for (int i = 1; i <= 12; i++)
        {
            cumMonthDays[i] = cumMonthDays[i - 1] + monthDays[i - 1];
        }

        int aliceStart = findDayOfYear(arriveAlice, cumMonthDays);
        int aliceEnd = findDayOfYear(leaveAlice, cumMonthDays);
        int bobStart = findDayOfYear(arriveBob, cumMonthDays);
        int bobEnd = findDayOfYear(leaveBob, cumMonthDays);

        int overlap = min(aliceEnd, bobEnd) -
                      max(aliceStart, bobStart) + 1;

        return max(0, overlap);
    }
};

int main()
{
    Solution sol;

    string arriveAlice = "08-15";
    string leaveAlice = "08-18";
    string arriveBob = "08-16";
    string leaveBob = "08-19";

    cout << sol.countDaysTogether(
                arriveAlice, leaveAlice, arriveBob, leaveBob)
         << '\n';

    return 0;
}

/*
===============================================================================
                    COUNT DAYS SPENT TOGETHER
===============================================================================

1. PROBLEM STATEMENT
--------------------
Alice and Bob each have an arrival date and a departure date in MM-DD format.
Find the number of calendar days on which both Alice and Bob are present.

Both arrival and departure dates are inclusive.

Return 0 if their date ranges do not overlap.

Assumption: All dates belong to the same non-leap year.

2. EXAMPLE
----------
Input:
Alice: 08-15 to 08-18
Bob:   08-16 to 08-19

Output:
3

Explanation:
Both are present on August 16, 17, and 18.


3. BRUTE FORCE APPROACH
-----------------------

Idea:
-----
Convert each date into a month and day. Iterate through every calendar day
of the year and count the days that lie within both people's date ranges.

Alternatively, enumerate the days in Alice's stay and count those that
also belong to Bob's stay.

Pseudo Code:
------------
1. Convert all four dates into day-of-year values.
2. Initialize count = 0.
3. For each day from Alice's arrival to Alice's departure:
       If day >= Bob's arrival AND day <= Bob's departure:
           Increment count.
4. Return count.

Complete Brute Force Code:
--------------------------

int countDaysTogetherBruteForce(
    string arriveAlice, string leaveAlice,
    string arriveBob, string leaveBob) {

    vector<int> monthDays = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    vector<int> cumMonthDays(13, 0);

    for (int i = 1; i <= 12; i++) {
        cumMonthDays[i] =
            cumMonthDays[i - 1] + monthDays[i - 1];
    }

    auto convert = [&](string date) {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        return cumMonthDays[month - 1] + day;
    };

    int aliceStart = convert(arriveAlice);
    int aliceEnd = convert(leaveAlice);
    int bobStart = convert(arriveBob);
    int bobEnd = convert(leaveBob);

    int count = 0;

    for (int day = aliceStart; day <= aliceEnd; day++) {
        if (day >= bobStart && day <= bobEnd) {
            count++;
        }
    }

    return count;
}

Time Complexity:
----------------
O(D), where D is the number of days in Alice's stay.
Since D <= 366, this is bounded by O(1) under the fixed calendar constraint.

Space Complexity:
-----------------
O(1), because only fixed-size arrays and variables are used.


4. OPTIMAL APPROACH
-------------------

Observation:
------------
Every date can be converted into a unique day number in the year.

For example:
January 1  -> day 1
February 1 -> day 32
March 1    -> day 60

The overlapping interval begins at the later arrival date and ends at
the earlier departure date.

Intuition:
----------
Let:
    start = max(Alice's arrival, Bob's arrival)
    end   = min(Alice's departure, Bob's departure)

If start <= end, the number of shared days is:

    end - start + 1

The +1 is necessary because both endpoints are inclusive.

If start > end, there is no overlap, so return 0.

Prefix sums of month lengths allow us to convert any MM-DD date into
a day-of-year value in constant time.

Pseudo Code:
------------
1. Build cumulative month-day counts.
2. Convert all four dates into day-of-year values.
3. start = max(aliceStart, bobStart).
4. end = min(aliceEnd, bobEnd).
5. Return max(0, end - start + 1).

Complete Optimal Code:
----------------------

class Solution {
public:
    int findDayOfYear(string date, vector<int>& cumMonthDays) {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));

        return cumMonthDays[month - 1] + day;
    }

    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        vector<int> monthDays = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        vector<int> cumMonthDays(13, 0);

        for (int i = 1; i <= 12; i++) {
            cumMonthDays[i] =
                cumMonthDays[i - 1] + monthDays[i - 1];
        }

        int aliceStart =
            findDayOfYear(arriveAlice, cumMonthDays);
        int aliceEnd =
            findDayOfYear(leaveAlice, cumMonthDays);
        int bobStart =
            findDayOfYear(arriveBob, cumMonthDays);
        int bobEnd =
            findDayOfYear(leaveBob, cumMonthDays);

        int overlap = min(aliceEnd, bobEnd) -
                      max(aliceStart, bobStart) + 1;

        return max(0, overlap);
    }
};

Time Complexity:
----------------
O(1), because the calendar has a fixed number of months and all date
conversions and overlap calculations take constant time.

Space Complexity:
-----------------
O(1), because the month arrays have fixed size.


5. DRY RUN
----------

Input:
Alice: 08-15 to 08-18
Bob:   08-16 to 08-19

Cumulative days before August = 212

Date Conversion:
----------------
Alice arrival = 212 + 15 = 227
Alice departure = 212 + 18 = 230

Bob arrival = 212 + 16 = 228
Bob departure = 212 + 19 = 231

Overlap Calculation:
--------------------
start = max(227, 228) = 228
end   = min(230, 231) = 230

overlap = end - start + 1
        = 230 - 228 + 1
        = 3

Output:
-------
3

Shared dates: August 16, August 17, August 18.


6. INTERVIEW NOTES
------------------

Pattern:
--------
Interval Intersection / Range Overlap.

Key Observation:
----------------
The intersection of two inclusive intervals [A1, A2] and [B1, B2] is:

    [max(A1, B1), min(A2, B2)]

The overlap count is:

    max(0, min(A2, B2) - max(A1, B1) + 1)

Common Mistakes:
----------------
1. Extracting the day from the wrong substring.
   Month: date.substr(0, 2)
   Day:   date.substr(3, 2)

2. Forgetting +1 for inclusive endpoints.

3. Forgetting to return 0 when the intervals do not overlap.

4. Using cumMonthDays[month] instead of cumMonthDays[month - 1]
   when adding the day-of-month.

5. Forgetting that the standard problem assumes a non-leap year.

6. Miscalculating cumulative month lengths. Use:
   cumMonthDays[i] = cumMonthDays[i - 1] + monthDays[i - 1].

When to Use This Approach:
--------------------------
Use interval intersection when:
- Two people have availability periods.
- Two date ranges need to be compared.
- You need the number of shared days or overlapping time units.
- Inclusive intervals must be handled efficiently.

The same formula works for integer ranges, schedules, booking windows,
and many other interval-overlap problems.

===============================================================================
*/
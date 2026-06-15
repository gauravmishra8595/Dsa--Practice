#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool lemonadeChange(vector<int> &bills)
    {
        int five = 0, ten = 0;

        for (int bill : bills)
        {
            if (bill == 5)
            {
                five++;
            }
            else if (bill == 10)
            {
                if (five == 0)
                    return false;
                five--;
                ten++;
            }
            else
            { // bill == 20
                // prefer 10 + 5
                if (ten > 0 && five > 0)
                {
                    ten--;
                    five--;
                }
                else if (five >= 3)
                {
                    five -= 3;
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;

    vector<int> bills1 = {5, 5, 5, 10, 20};
    vector<int> bills2 = {5, 5, 10, 10, 20};
    vector<int> bills3 = {5, 10, 20};

    cout << boolalpha;

    cout << "Test 1: " << sol.lemonadeChange(bills1) << endl;
    cout << "Test 2: " << sol.lemonadeChange(bills2) << endl;
    cout << "Test 3: " << sol.lemonadeChange(bills3) << endl;

    return 0;
}
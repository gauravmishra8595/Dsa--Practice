#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> finalPrices(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> st;

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && prices[st.back()] >= prices[i])
            {
                prices[st.back()] -= prices[i];
                st.pop_back();
            }

            st.push_back(i);
        }

        return prices;
    }
};

int main()
{
    Solution obj;

    vector<int> prices = {8, 4, 6, 2, 3};

    vector<int> ans = obj.finalPrices(prices);

    cout << "Final Prices : ";

    for (int x : ans)
        cout << x << " ";

    cout << endl;

    return 0;
}

/*

*==================================================*
*                    LEETCODE 1475                 *
*==================================================*

*              Final Prices With a Special Discount*
*==================================================*

*==================================================*
*                 Problem Statement                 *
*==================================================*

*You are given an integer array prices where prices[i] is the*
*price of the ith item in a shop.*

*There is a special discount for each item.*

*For the ith item, the discount is equal to prices[j], where j*
*is the smallest index such that:*

*    j > i*

*and*

*    prices[j] <= prices[i]*

*If such a j does not exist, there is no discount.*

*Return the final prices after applying the special discount.*

*-------------------------------------------------*
*Example*
*-------------------------------------------------*

*Input:*
*prices = {8,4,6,2,3}*

*Output:*
*{4,2,4,2,3}*

*Explanation:*

*For 8:*
*Next smaller/equal price = 4*
*Final price = 8 - 4 = 4*

*For 4:*
*Next smaller/equal price = 2*
*Final price = 4 - 2 = 2*

*For 6:*
*Next smaller/equal price = 2*
*Final price = 6 - 2 = 4*

*For 2:*
*Next smaller/equal price = none*
*Final price = 2*

*For 3:*
*Next smaller/equal price = none*
*Final price = 3*

*Answer = {4,2,4,2,3}*

*==================================================*
*               Brute Force Approach               *
*==================================================*

*Idea*
*----*

*For every price, search towards the right and find the first*
*price which is less than or equal to the current price.*

*As soon as we find it, subtract it from the current price.*

*-------------------------------------------------*
*Pseudo Code*
*-------------------------------------------------*

*for i = 0 to n-1*

*    for j = i+1 to n-1*

*        if prices[j] <= prices[i]*

*            prices[i] -= prices[j]*

*            break*

*return prices*

*-------------------------------------------------*
*Complete Brute Force Code*
*-------------------------------------------------*

*class Solution {*
*public:*
*    vector<int> finalPrices(vector<int>& prices) {*
*        int n = prices.size();*

*        for (int i = 0; i < n; i++) {*

*            for (int j = i + 1; j < n; j++) {*

*                if (prices[j] <= prices[i]) {*
*                    prices[i] -= prices[j];*
*                    break;*
*                }*
*            }*
*        }*

*        return prices;*
*    }*
*};*

*-------------------------------------------------*
*Time Complexity*
*-------------------------------------------------*

*O(n^2)*

*For every element, we may scan all elements to its right.*

*-------------------------------------------------*
*Space Complexity*
*-------------------------------------------------*

*O(1) auxiliary space*

*==================================================*
*                Optimal Approach                  *
*               (Monotonic Stack)                  *
*==================================================*

*Observation*
*-----------*

*For every element, we need the FIRST element to its right*
*which is smaller than or equal to it.*

*This is a classic "Next Smaller or Equal Element" problem.*

*Instead of searching to the right for every element, we can*
*use a monotonic stack.*

*-------------------------------------------------*
*Intuition*
*-------------------------------------------------*

*Process the array from left to right.*

*The stack stores indices of prices for which we have not yet*
*found a valid discount.*

*When the current price is less than or equal to the price*
*at the index on top of the stack:*

*    prices[stack.top()] >= prices[i]*

*then the current price is the FIRST valid discount for that*
*previous element.*

*So:*

*    prices[stack.top()] -= prices[i]*

*Then remove that index from the stack.*

*If the current price cannot give a discount to the top element,*
*push the current index and continue.*

*-------------------------------------------------*
*Why Stack Works*
*-------------------------------------------------*

*The stack maintains unresolved elements in decreasing order*
*of their prices.*

*Once a smaller/equal price appears, it becomes the first valid*
*discount for all suitable unresolved elements on the stack.*

*Each index is pushed exactly once and popped at most once.*

*Therefore, the total work is O(n).*

*-------------------------------------------------*
*Pseudo Code*
*-------------------------------------------------*

*create empty stack*

*for i = 0 to n-1*

*    while stack is not empty AND*
*          prices[stack.top()] >= prices[i]*

*        prices[stack.top()] -= prices[i]*

*        pop stack*

*    push i into stack*

*return prices*

*-------------------------------------------------*
*Complete Optimal Code*
*-------------------------------------------------*

*class Solution {*
*public:*
*    vector<int> finalPrices(vector<int>& prices) {*
*        int n = prices.size();*
*        vector<int> st;*

*        for (int i = 0; i < n; i++) {*

*            while (!st.empty() &&*
*                   prices[st.back()] >= prices[i]) {*

*                prices[st.back()] -= prices[i];*
*                st.pop_back();*
*            }*

*            st.push_back(i);*
*        }*

*        return prices;*
*    }*
*};*

*-------------------------------------------------*
*Time Complexity*
*-------------------------------------------------*

*O(n)*

*Every element is pushed once and popped at most once.*

*-------------------------------------------------*
*Space Complexity*
*-------------------------------------------------*

*O(n)*

*The monotonic stack can contain up to n indices.*

*==================================================*
*                     Dry Run                     *
*==================================================*

*prices = {8,4,6,2,3}*

*Start:*
*stack = {}*

*-------------------------------------------------*
*i = 0, price = 8*
*-------------------------------------------------*

*Stack is empty.*

*Push index 0.*

*stack = {0}*

*-------------------------------------------------*
*i = 1, price = 4*
*-------------------------------------------------*

*prices[0] = 8 >= 4*

*So 4 is the first valid discount for 8.*

*8 - 4 = 4*

*Pop 0.*

*Push 1.*

*stack = {1}*

*prices = {4,4,6,2,3}*

*-------------------------------------------------*
*i = 2, price = 6*
*-------------------------------------------------*

*prices[1] = 4 >= 6 -> false*

*Push 2.*

*stack = {1,2}*

*-------------------------------------------------*
*i = 3, price = 2*
*-------------------------------------------------*

*prices[2] = 6 >= 2*

*6 - 2 = 4*

*Pop 2.*

*Now prices[1] = 4 >= 2*

*4 - 2 = 2*

*Pop 1.*

*Push 3.*

*stack = {3}*

*prices = {4,2,4,2,3}*

*-------------------------------------------------*
*i = 4, price = 3*
*-------------------------------------------------*

*prices[3] = 2 >= 3 -> false*

*Push 4.*

*stack = {3,4}*

*No more elements.*

*Final Answer:*

*    {4,2,4,2,3}*

*==================================================*
*                 Interview Notes                 *
*==================================================*

*Pattern*
*-------*

*Monotonic Stack*

*Specifically:*

*    Next Smaller or Equal Element*

*-------------------------------------------------*
*Key Observation*
*-------------------------------------------------*

*The discount for an element is the FIRST element on its right*
*that is smaller than or equal to it.*

*Whenever we encounter such an element, we can immediately*
*resolve the previous unresolved elements using a stack.*

*-------------------------------------------------*
*Common Mistakes*
*-------------------------------------------------*

*1. Using < instead of <=.*

*The discount condition is:*

*    prices[j] <= prices[i]*

*2. Finding any smaller element instead of the FIRST one.*

*3. Forgetting to pop the resolved index.*

*4. Using a normal stack of values when indices are needed.*

*5. Using O(n^2) nested loops when a monotonic stack can solve*
*   the problem in O(n).*

*-------------------------------------------------*
*When to use this approach*
*-------------------------------------------------*

*Use a monotonic stack when a problem asks for:*

*- Next smaller element*
*- Next greater element*
*- Previous smaller element*
*- Previous greater element*
*- First element satisfying a comparison condition*
*- Nearest element on the left/right*

*Core Pattern:*

*    Process Array*
*          ↓*
*    Maintain Stack*
*          ↓*
*    Current Element Resolves Previous Elements*
*          ↓*
*       Pop + Update*
*          ↓*
*       Push Current*

*==================================================*

*/
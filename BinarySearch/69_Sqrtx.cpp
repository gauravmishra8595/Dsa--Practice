#include <iostream>
using namespace std;

int mySqrt(int x)
{
    if (x < 2)
        return x;

    long long left = 1;
    long long right = x;
    int ans = 0;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;
        long long sq = mid * mid;

        if (sq == x)
        {
            return mid;
        }
        else if (sq < x)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return ans;
}

int main()
{
    int x;

    cout << "Enter a number: ";
    cin >> x;

    cout << "Square root (floor value) = " << mySqrt(x) << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// Simulated API for local testing
int firstBad = 4; // change this to test different cases

bool isBadVersion(int version) {
    return version >= firstBad;
}

class Solution {
public:
    int firstBadVersion(int n) {
        int s = 1;
        int e = n;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (isBadVersion(mid)) {
                e = mid;       // move left
            } else {
                s = mid + 1;   // move right
            }
        }

        return s;
    }
};

int main() {
    Solution obj;

    int n = 10; // total versions

    cout << "First bad version: " << obj.firstBadVersion(n) << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        for (int a : asteroids) {
            bool destroyed = false;

            // Collision happens only when:
            // top asteroid is moving right (+)
            // current asteroid is moving left (-)
            while (!st.empty() && a < 0 && st.top() > 0) {

                if (abs(st.top()) < abs(a)) {
                    // Stack asteroid gets destroyed
                    st.pop();
                }
                else if (abs(st.top()) == abs(a)) {
                    // Both destroy each other
                    st.pop();
                    destroyed = true;
                    break;
                }
                else {
                    // Current asteroid gets destroyed
                    destroyed = true;
                    break;
                }
            }

            if (!destroyed) {
                st.push(a);
            }
        }

        // Convert stack to vector
        vector<int> ans(st.size());

        for (int i = st.size() - 1; i >= 0; i--) {
            ans[i] = st.top();
            st.pop();
        }

        return ans;
    }
};

int main() {
    Solution obj;

    // Example input
    vector<int> asteroids = {5, 10, -5};

    vector<int> result = obj.asteroidCollision(asteroids);

    cout << "Remaining asteroids: ";
    for (int x : result) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}
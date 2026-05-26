#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;

        for (int i = 0; i < tokens.size(); i++) {

            // Check if token is an operator
            if (tokens[i] == "+" || tokens[i] == "-" ||
                tokens[i] == "*" || tokens[i] == "/") {

                int b = st.top();
                st.pop();

                int a = st.top();
                st.pop();

                if (tokens[i] == "+") {
                    st.push(a + b);

                } else if (tokens[i] == "-") {
                    st.push(a - b);

                } else if (tokens[i] == "*") {
                    st.push(a * b);

                } else {
                    st.push(a / b);
                }

            } else {
                // Convert string to integer
                st.push(stoi(tokens[i]));
            }
        }

        return st.top();
    }
};

int main() {

    vector<string> tokens = {
        "10","6","9","3","+","11","*","/","*","17","+","5","+"
    };

    Solution obj;

    int ans = obj.evalRPN(tokens);

    cout << "Answer = " << ans << endl;

    return 0;
}
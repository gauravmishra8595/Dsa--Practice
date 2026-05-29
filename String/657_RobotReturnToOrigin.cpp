#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0;
        int y = 0;

        for (int i = 0; i < moves.size(); i++) {

            if (moves[i] == 'R') {
                x++;
            }
            else if (moves[i] == 'L') {
                x--;
            }
            else if (moves[i] == 'U') {
                y++;
            }
            else if (moves[i] == 'D') {
                y--;
            }
        }

        return (x == 0 && y == 0);
    }
};

int main() {
    Solution obj;

    string moves;
    
    cout << "Enter moves: ";
    cin >> moves;

    if (obj.judgeCircle(moves)) {
        cout << "Robot returned to origin" << endl;
    } else {
        cout << "Robot did not return to origin" << endl;
    }

    return 0;
}
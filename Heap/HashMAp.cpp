#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<string, int> m;
    pair<string, int> p = make_pair("Dubey", 3);
    m.insert(p);

    pair<string, int> pair2("Gaurav", 2);
    m.insert(pair2);

    m["Gaurav mishra"] = 1;

    cout << m["Gaurav mishra"] << endl;
    cout << m["Ayushi"] << endl;
    cout << m.at("Dubey") << endl;
    // cout<<m.at("Aushi")<<endl;

    cout << m.count("Dubey") << endl;

    cout << m.size() << endl;

    m.erase("Gaurav mishra");
    cout << m.size() << endl;

    unordered_map<string, int>::iterator it = m.begin();
    while (it != m.end())
    {
        cout << it->first << " " << it->second << endl;
        it++;
    }

    return 0;
}
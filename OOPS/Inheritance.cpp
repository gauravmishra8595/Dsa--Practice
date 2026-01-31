#include <iostream>
using namespace std;
class Human{
    public:
    int height;
    int weight;
    int age;

    public:
    int getAge(int age){
        return this->age;
    }
    int setweight(int weight){
        return this->weight;
    }
};
class Male: public Human{
    public:
    string color;
    void sleep(){
        cout<<"Male is sleeping"<<endl;
    }
};

int main()
{
    Male object1;
    cout<<object1.age<<endl;
    cout<<object1.height<<endl;
    cout<<object1.weight<<endl;
    cout<<object1.color<<endl;
    object1.sleep();
    return 0;
}


#include <iostream>
using namespace std;
class Animal{
    public:
    int age;
    int weight;
     
    public:
    void bark(){
        cout<<"Barking"<<endl;
    }
};

class Human{
    public:
    string color;

    public:
    void speak(){
        cout<<"Speaking"<<endl;
    }


};

class Hybrid: public Animal, public Human{

};

int main()
{
    Hybrid j1;
    j1.speak();
    j1.bark();
    return 0;
}
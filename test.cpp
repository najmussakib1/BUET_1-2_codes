#include <iostream>
#include<string>

using namespace std;
class prac{
    string name;
public:
    prac(string n){
        name=n;
    }
    prac operator = (const prac& other){
        name=other.name;
        return *this;
    }
    void get(){
        cout<<name<<endl;
    }
};
int main(){
    prac obj1("hello");
    prac obj2=obj1;
    obj1.get();
    obj2.get();
}
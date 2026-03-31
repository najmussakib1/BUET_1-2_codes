#include <iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> nums;
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);
    // for(auto x=nums.begin();x!=nums.end();x++){
    //     cout<<*x<<endl;
    // }
    // for(auto x:nums){
    //     cout<<x<<endl;
    // }
    // 
    auto x = nums.end();
    while(x!=nums.begin()){
        x--;
        cout<<*x<<endl;
    }
    return 0;
}
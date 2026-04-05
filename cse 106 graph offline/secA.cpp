#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
int main(){
    int n;
    cin>> n;
    cin.ignore();
    vector<pair<char,char>> family;
    vector<vector<int>> adjacency(n);
    for(int i=0;i<n;i++){
        char a,b;
        cin>>a>>b;
        family.push_back({a,b});
        adjacency[a-'A'].push_back(b-'A');
    }
    
}
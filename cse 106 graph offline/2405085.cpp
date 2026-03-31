#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

void dfs(int u, vector<int>& comp, vector<bool>& visited, vector<set<int>>& adj) {
    visited[u] = true;
    comp.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, comp, visited, adj);
        }
    }
}

int main(){
    int n;
    cin >> n;
    cin.ignore();
    vector<pair<int,int>> matches;
    string line;
    while(getline(cin,line)){
        int a,b;
        if(sscanf(line.c_str(),"[%d, %d]",&a,&b)==2){
            matches.push_back({a,b});
        }
    }

    vector<set<int>> adjacency_list(n);
    for(auto &m:matches){
        adjacency_list[m.first].insert(m.second);
        adjacency_list[m.second].insert(m.first);
    }

    vector<bool> visited(n, false);
    vector<vector<int>> groups;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> comp;
            dfs(i, comp, visited, adjacency_list);
            groups.push_back(comp);
        }
    }

    cout << groups.size() << endl;

    int grp = 1;
    for(auto &g: groups){
        sort(g.begin(), g.end());
        cout << "Group " << grp++ << ": {";
        for(int i = 0; i < g.size(); i++){
            cout << g[i];
            if(i + 1 < g.size()) cout << ", ";
        }
        cout << "} | ";

        vector<pair<int,int>> missing_matches;
        for(int i = 0; i < g.size(); i++){
            for(int j = i + 1; j < g.size(); j++){
                int p1 = g[i], p2 = g[j];
                if(adjacency_list[p1].find(p2) == adjacency_list[p1].end()){
                    missing_matches.push_back({p1, p2});
                }
            }
        }

        if(missing_matches.empty()){
            cout << "none" << endl;
        }
        else{
            for(int i = 0; i < missing_matches.size(); i++){
                cout << "[" << missing_matches[i].first << "," << missing_matches[i].second << "]";
                if(i + 1 < missing_matches.size()) cout << ", ";
            }
            cout << endl;
        }
    }
}

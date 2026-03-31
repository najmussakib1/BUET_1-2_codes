#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <functional>
using namespace std;

typedef struct {
    int id;
    int x;
    int y;
} city;
typedef struct {
    int u;
    int v;
    double cost;
} Edge;

vector<Edge> resultEdges;
double totalCost = 0.0;

double dist(const city &a, const city &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
void basecasesolve(vector<city> &cities, int m){
    int n = cities.size();
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({
                cities[i].id,
                cities[j].id,
                dist(cities[i], cities[j])
            });
        }
    }
    sort(edges.begin(), edges.end(),[](const Edge &a, const Edge &b) {
        return a.cost < b.cost;
    });

    unordered_map<int, int> parent;

    function<int(int)> find = [&](int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    };

    auto unite = [&](int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    };

    for (auto &c : cities){
        parent[c.id] = c.id;
    }
    for (auto &e : edges) {
        if (find(e.u) != find(e.v)) {
            unite(e.u, e.v);
            resultEdges.push_back(e);
            totalCost += e.cost;
        }
    }
}


void solve(vector<city> &cities, int m){
    int size = cities.size();
    if(size<=m){
        basecasesolve(cities, m);
        return;
    }
    int mid = size/2;
    vector<city> left(cities.begin(), cities.begin()+mid);
    vector<city> right(cities.begin()+mid, cities.end());
    solve(left, m);
    solve(right, m);
    
    int l = min(m, (int)left.size());
    int r = min(m, (int)right.size());
    double best = 1e9;
    int u=-1, v=-1;
    for (int i = left.size() - l; i < left.size(); i++) {
        for (int j = 0; j < r; j++) {
            double d = dist(left[i], right[j]);
            if (d < best) {
                best = d;
                u = left[i].id;
                v = right[j].id;
            }
        }
    }
    resultEdges.push_back({u, v, best});
    totalCost += best;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<city> cities(n);
    for(int i=0; i<n; i++){
        cin >> cities[i].id >> cities[i].x >> cities[i].y;
        cities[i].id = i+1;
    }
    sort(cities.begin(), cities.end(), [](const city &a, const city &b){
        return a.x < b.x;
    });
    solve(cities, m);
    cout<<"Total cost: "<<totalCost<<endl;
    cout<<"Edges:"<<endl;
    for(const auto &e : resultEdges){
        cout<<e.u<<" "<<e.v<<endl;
    }
}
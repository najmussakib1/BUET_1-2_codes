#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

class city {
public:
    int id;
    double x, y;
    city(int i=0,double x=0,double y=0){
        id=i;
        this->x=x;
        this->y=y;
    }
    double distance_calculate(const city& another){
        return sqrt((x-another.x)*(x-another.x)+(y-another.y)*(y-another.y));
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<city> cities(n);
    for(int i=0;i<n;i++){
        cin >> cities[i].id >> cities[i].x >> cities[i].y;
    }
    vector<bool> is_visited(n,false);
    is_visited[0] = true;
    double totalCost = 0;
    vector<pair<int,int>> edges;

    for(int step=1; step<n; step++){
        double bestDist = 1e18;
        int u=-1,v=-1;
        for(int i=0;i<n;i++) if(is_visited[i]){
            for(int j=0;j<n;j++) if(!is_visited[j]){
                double d = cities[i].distance_calculate(cities[j]);
                if(d < bestDist){
                    bestDist = d;
                    u = i; v = j;
                }
            }
        }
        is_visited[v] = true;
        totalCost += bestDist;
        edges.push_back({cities[u].id, cities[v].id});
    }

    cout << "Total Cost: " << fixed << setprecision(2) << totalCost << endl;
    cout << "Edges:" << endl;
    for(auto &e: edges) cout << e.first << " " << e.second << endl;
}
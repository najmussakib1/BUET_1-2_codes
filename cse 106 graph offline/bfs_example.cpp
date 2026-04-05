#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int minShares(int n, vector<vector<int>> &adj, int u, int v) {
    vector<int> dist(n + 1, -1);
    queue<int> q;

    q.push(u);
    dist[u] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }

    return dist[v]; // -1 if unreachable
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int u, v;
    cin >> u >> v;

    int ans = minShares(n, adj, u, v);

    if (ans == -1)
        cout << "Not reachable\n";
    else
        cout << ans << endl;

    return 0;
}
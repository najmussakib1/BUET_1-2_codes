#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int> > adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;

    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    vector<int> ans(k + 1, 0);
    for (int i = 1; i <= n; i++) {
        int product = a[i - 1];
        ans[product] = max(ans[product], dist[i]);
    }

    for (int i = 1; i <= k; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}

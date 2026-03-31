#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n), b;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    b = a;
    sort(b.begin(), b.end());

    // Already sorted
    if (a == b) {
        cout << "yes\n1 1\n";
        return 0;
    }

    int l = -1, r = -1;

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            if (l == -1) l = i;
            r = i;
        }
    }

    reverse(a.begin() + l, a.begin() + r + 1);

    if (a == b) {
        cout << "yes\n";
        cout << l + 1 << " " << r + 1 << "\n";
    } else {
        cout << "no\n";
    }

    return 0;
}
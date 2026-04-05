#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<long long> a(n + 1);

        a[1] = 1;

        for (int i = 2; i <= n; i++)
            a[i] = a[i-1]*2;

        for (int i = 2; i <= n; i++)
            cout << gcd(a[i], a[i - 1]) << " ";
        cout << endl;

        for (int i = 1; i <= n; i++)
            cout << a[i] << " ";
        cout << endl;
    }
}
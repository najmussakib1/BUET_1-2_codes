#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
    int I, D, R;
    cin >> I >> D >> R;
    cin.ignore();
    string s, t;
    getline(cin, s);
    getline(cin, t);
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp_table(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++)
    {
        dp_table[i][0] = i * D;
    }
    for (int j = 0; j <= m; j++)
    {
        dp_table[0][j] = j * I;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp_table[i][j] = dp_table[i - 1][j - 1];
            }
            else
            {
                dp_table[i][j] = min({dp_table[i - 1][j] + D, dp_table[i - 1][j - 1] + R, dp_table[i][j - 1] + I});
            }
        }
    }
    int i = n;
    int j = m;
    vector<string> operations;
    while (i > 0 || j > 0)
    {
        if (i == 0)
        {
            operations.push_back("Insert " + string(1, t[j - 1]));
            j--;
        }
        else if (j == 0)
        {
            operations.push_back("Delete " + string(1, s[i - 1]));
            i--;
        }
        else if (s[i - 1] == t[j - 1])
        {
            operations.push_back("Match " + string(1, s[i - 1]));
            i--;
            j--;
        }
        else if (dp_table[i][j] == dp_table[i - 1][j - 1] + R)
        {
            operations.push_back("Replace " + string(1, s[i - 1]) + " with " + string(1, t[j - 1]));
            i--, j--;
        }
        else if (dp_table[i][j] == dp_table[i][j - 1] + I)
        {
            operations.push_back("Insert " + string(1, t[j - 1]));
            j--;
        }
        else if (dp_table[i][j] == dp_table[i - 1][j] + D)
        {
            operations.push_back("Delete " + string(1, s[i - 1]));
            i--;
        }
    }
    reverse(operations.begin(), operations.end());
    cout << "Minimum Cost: " << dp_table[n][m] << "\n";
    cout << "Operations:\n";

    for (auto &op : operations)
    {
        cout << op << "\n";
    }
}
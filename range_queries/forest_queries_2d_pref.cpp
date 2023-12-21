#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

void solve()
{
    ll n, q;
    string s;
    vector<string> v;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
    {
        cin >> s;
        v.eb(s);
    }
    vvl pref(n, vl(n, 0));
    pref[0][0] = (v[0][0] == '*');
    for (ll i = 1; i < n; i++)
        pref[i][0] = pref[i - 1][0] + (v[i][0] == '*');

    for (ll j = 1; j < n; j++)
        pref[0][j] = pref[0][j - 1] + (v[0][j] == '*');

    for (ll i = 1; i < n; i++)
        for (ll j = 1; j < n; j++)
            pref[i][j] = pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1] + (v[i][j] == '*');
    ll y1, x1, y2, x2;
    for (ll i = 0; i < q; i++)
    {
        cin >> y1 >> x1 >> y2 >> x2;
        y1--, x1--, y2--, x2--;
        ll val = pref[y2][x2];
        if (x1 > 0)
            val -= pref[y2][x1 - 1];
        if (y1 > 0)
            val -= pref[y1 - 1][x2];
        if (x1 > 0 && y1 > 0)
            val += pref[y1 - 1][x1 - 1];
        cout << val << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
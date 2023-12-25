#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

// 2D BIT Template
// TC : O((n^2 + q)* (lg n)^2)
vvl fenwick;
ll sum_fenwick(ll r, ll c)
{
    ll c1;
    ll s = 0;
    while (r >= 1)
    {
        c1 = c;
        while (c1 >= 1)
        {
            s += fenwick[r][c1];
            c1 -= (c1 & -c1);
        }
        r -= (r & -r);
    }
    return s;
}
ll sum_fenwick(ll r1, ll c1, ll r2, ll c2)
{
    ll val = sum_fenwick(r2, c2);
    if (r1 > 1)
        val -= sum_fenwick(r1 - 1, c2);
    if (c1 > 1)
        val -= sum_fenwick(r2, c1 - 1);
    if (r1 > 1 && c1 > 1)
        val += sum_fenwick(r1 - 1, c1 - 1);
    return val;
}
void add_fenwick(ll r, ll c, ll val)
{
    ll n = fenwick.size() - 1;
    ll c1;
    while (r <= n)
    {
        c1 = c;
        while (c1 <= n)
        {
            fenwick[r][c1] += val;
            c1 += (c1 & -c1);
        }
        r += (r & -r);
    }
}
void build_fenwick(vvl v)
{
    ll n = v.size() - 1;
    fenwick.resize(n + 1, vl(n + 1, 0));
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            add_fenwick(i, j, v[i][j]);
}

void solve()
{
    ll n, q;
    string s;
    vector<string> v;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
    {
        cin >> s;
        v.emplace_back(s);
    }
    vvl grid(n + 1, vl(n + 1, 0));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (v[i][j] == '*')
                grid[i + 1][j + 1]++;
        }
    }
    build_fenwick(grid); // O((nlgn)^2)
    ll y1, x1, y2, x2, num, x, y;
    for (ll i = 0; i < q; i++) // O(q*(lgn)^2)
    {
        cin >> num;
        if (num == 1)
        {
            cin >> y >> x;
            ll r = y, c = x;
            if (grid[r][c] == 1)
            {
                add_fenwick(r, c, -1);
                grid[r][c]--;
            }
            else
            {
                add_fenwick(r, c, 1);
                grid[r][c]++;
            }
        }
        else
        {
            cin >> y1 >> x1 >> y2 >> x2;
            cout << sum_fenwick(y1, x1, y2, x2) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
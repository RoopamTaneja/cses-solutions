#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

// 1D BIT Template
// T.C : O((n+q)*lg n)
vl fenwick;
vl fenw_arr;
ll sum_fenwick(ll k)
{
    ll s = 0;
    while (k >= 1)
    {
        s += fenwick[k];
        k -= (k & -k);
    }
    return s;
}
ll sum_fenwick(ll l, ll r)
{
    if (l == 1)
        return sum_fenwick(r);
    else
        return sum_fenwick(r) - sum_fenwick(l - 1);
}
void add_fenwick(ll k, ll x)
{
    ll n = fenwick.size() - 1;
    fenw_arr[k] += x;
    while (k <= n)
    {
        fenwick[k] += x;
        k += (k & -k);
    }
}
void set_fenwick(ll k, ll x)
{
    add_fenwick(k, x - fenw_arr[k]);
}
void build_fenwick(vl v)
{
    ll n = v.size();
    fenwick.resize(n + 1, 0);
    fenw_arr.resize(n + 1, 0);
    for (ll i = 1; i <= n; i++)
        set_fenwick(i, v[i - 1]);
}

void solve()
{
    ll n, entry, q;
    vl v;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    build_fenwick(v); // O(n lg n)
    ll a, b, x;
    for (ll i = 0; i < q; i++) // O(q lg n)
    {
        cin >> x >> a >> b;
        if (x == 1)
            set_fenwick(a, b);
        else
            cout << sum_fenwick(a, b) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
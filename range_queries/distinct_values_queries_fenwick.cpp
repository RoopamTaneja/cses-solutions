#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vl fenwick;
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
    while (k <= n)
    {
        fenwick[k] += x;
        k += (k & -k);
    }
}

void solve()
{
    ll n, q;
    cin >> n >> q;
    vl v(n + 1);
    for (ll i = 1; i <= n; i++)
        cin >> v[i];
    vector<vector<pll>> queries(n + 1);
    ll a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        queries[a].emplace_back(mp(b, i));
    }
    fenwick.resize(n + 1, 0);
    map<ll, ll> last_ind;
    vl soln(q, -1);
    for (ll i = n; i > 0; i--)
    {
        ll val = v[i];
        if (last_ind.count(val) > 0)
            add_fenwick(last_ind[val], -1);
        last_ind[val] = i;
        add_fenwick(i, 1);
        for (auto &x : queries[i])
            soln[x.second] = sum_fenwick(x.first);
    }
    for (auto &i : soln)
        cout << i << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

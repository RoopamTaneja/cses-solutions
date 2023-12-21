#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;

vvl st;
void build_st(vl &v)
{
    // Building Sparse Table
    ll n = v.size();
    ll k = __lg(n) + 2;
    st.assign(k, vl(n + 5, 0));
    for (ll j = 0; j < n; j++)
        st[0][j] = v[j];
    for (ll i = 1; i <= k; i++)
    {
        for (ll j = 0; j + (1 << i) - 1 < n; j++)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]); // change fn here
    }
}

ll query_st(ll a, ll b)
{
    // Querying sparse table for [l,r] 0-indexed
    a--, b--; // only for 1 indexed
    ll i = __lg(b - a + 1);
    return min(st[i][a], st[i][b - (1 << i) + 1]); // change fn here
}

void solve()
{
    ll n, entry, q;
    vl v;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    build_st(v);
    ll a, b;
    for (ll x = 0; x < q; x++)
    {
        cin >> a >> b;
        cout << query_st(a, b) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
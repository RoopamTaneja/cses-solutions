#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
vvl children;
vl parent, level, trav, first;

void treeinit(ll n)
{
    children.assign(n + 1, vl(0));
    parent.assign(n + 1, -1);
    level.assign(n + 1, 0);
    first.assign(n + 1, -1);
}
void Traversal(ll node)
{
    trav.emplace_back(node);
    first[node] = trav.size() - 1;
    for (auto x : children[node])
    {
        if (x == parent[node])
            continue;
        parent[x] = node;
        level[x] = level[node] + 1;
        Traversal(x);
        trav.emplace_back(node);
    }
}

ll t_min(ll a, ll b)
{
    if (level[a] < level[b])
        return a;
    return b;
}

vvl st;
void build_st(vl &v)
{
    ll n = v.size();
    ll k = __lg(n) + 1;
    st.assign(k, vl(n + 1, 0));
    for (ll j = 0; j < n; j++)
        st[0][j] = v[j];
    for (ll i = 1; i <= k; i++)
    {
        for (ll j = 0; j + (1 << i) - 1 < n; j++)
            st[i][j] = t_min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
}
ll query_st(ll a, ll b)
{
    // Querying sparse table for [l,r] 0-indexed
    ll i = __lg(b - a + 1);
    return t_min(st[i][a], st[i][b - (1 << i) + 1]);
}

void solve()
{
    ll n, q, a, b;
    vl v;
    cin >> n >> q;
    treeinit(n);
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        children[a].emplace_back(b);
        children[b].emplace_back(a);
    }
    Traversal(1);
    ll sz = trav.size();
    build_st(trav);
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        ll l = first[a], r = first[b];
        if (r < l)
            swap(l, r);
        ll lca = query_st(l, r);
        cout << level[a] + level[b] - 2 * level[lca] << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
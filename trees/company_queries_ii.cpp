#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
vvl children;
vl parent;
vvl ances;
vl level;

void treeinit(ll n)
{
    ll k = log2(n) + 1;
    children.assign(n + 1, vl(0));
    parent.assign(n + 1, -1);
    ances.assign(n + 1, vl(k, -1));
    level.assign(n + 1, 0);
}

void Traversal(ll node)
{
    for (auto x : children[node])
    {
        if (x == parent[node])
            continue;
        level[x] = level[node] + 1;
        Traversal(x);
    }
}

void buildances(ll n)
{
    ll height = ances[0].size();
    for (ll node = 1; node <= n; node++)
        ances[node][0] = parent[node];
    for (ll i = 1; i < height; i++)
    {
        for (ll node = 1; node <= n; node++)
            if (ances[node][i - 1] != -1)
                ances[node][i] = ances[ances[node][i - 1]][i - 1];
    }
}

ll findances(ll node, ll k)
{
    ll height = ances[0].size();
    ll anc = node;
    for (ll i = 0; i < height; i++)
    {
        if (anc == -1)
            break;
        if (k & 1)
            anc = ances[anc][i];
        k >>= 1;
    }
    return anc;
}

ll lca(ll a, ll b)
{
    ll height = ances[0].size();
    if (level[a] > level[b])
        swap(a, b);
    if (level[b] != level[a])
        b = findances(b, level[b] - level[a]);
    if (a == b)
        return a;
    for (ll i = height - 1; i >= 0; i--)
    {
        if (ances[a][i] != ances[b][i])
        {
            a = ances[a][i];
            b = ances[b][i];
        }
    }
    return ances[a][0];
}

void solve()
{
    ll n, q, a, b;
    vl v;
    cin >> n >> q;
    treeinit(n);
    for (ll i = 2; i <= n; i++)
    {
        cin >> parent[i];
        children[parent[i]].emplace_back(i);
    }
    Traversal(1);
    buildances(n);
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

vl parent;
vvl ances;
void treeinit(ll n)
{
    ll k = log2(n) + 1;
    parent.assign(n + 1, -1);
    ances.assign(n + 1, vl(k, -1));
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

void solve()
{
    ll n, q, node, k;
    vl v;
    cin >> n >> q;
    treeinit(n);
    for (ll i = 2; i <= n; i++)
        cin >> parent[i];
    buildances(n);
    for (ll i = 0; i < q; i++)
    {
        cin >> node >> k;
        cout << findances(node, k) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
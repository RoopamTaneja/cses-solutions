#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

ll succ[200001];
ll steps[200001][31];

void buildsteps(ll n)
{
    ll height = 31;
    for (ll node = 1; node <= n; node++)
        steps[node][0] = succ[node];
    for (ll i = 1; i < height; i++)
    {
        for (ll node = 1; node <= n; node++)
            if (steps[node][i - 1] != -1)
                steps[node][i] = steps[steps[node][i - 1]][i - 1];
    }
}

ll findsteps(ll node, ll k)
{
    ll height = 31;
    ll anc = node;
    for (ll i = 0; i < height; i++)
    {
        if (anc == -1)
            break;
        if (k & 1)
            anc = steps[anc][i];
        k >>= 1;
    }
    return anc;
}

ll lca(ll node, vector<bool> vis, ll n)
{
    vis.assign(n + 1, false);
    vis[node] = true;
    ll height = 31;
    ll cnt = 0;
    for (ll i = height - 1; i >= 0; i--)
    {
        if (!vis[steps[node][i]])
        {
            node = steps[node][i];
            vis[node] = true;
            cnt++;
        }
    }
    return cnt + 1;
    ll cnt = 0;
    while (!vis[succ[node]])
    {
        node = succ[node];
        vis[node] = true;
        cnt++;
    }
    return cnt + 1;
}

void solve()
{
    ll n;
    vl v;
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> succ[i];
    buildsteps(n);
    vector<bool> vis;
    for (ll i = 1; i <= n; i++)
        cout << lca(i, vis, n) << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
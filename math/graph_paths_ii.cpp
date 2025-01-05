#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
vvl mul(vvl a, vvl b, ll n)
{
    vvl res(n + 1, vl(n + 1, 2e18));
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= n; j++)
            for (ll k = 1; k <= n; k++)
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
    return res;
}
vvl mat_exp(vvl a, ll b, ll n)
{
    vvl res(n + 1, vl(n + 1, 2e18));
    for (ll i = 1; i <= n; i++)
        res[i][i] = 0;
    while (b > 0)
    {
        if (b & 1)
            res = mul(res, a, n);
        a = mul(a, a, n);
        b >>= 1;
    }
    return res;
}
int main()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vvl adj(n + 1, vl(n + 1, 2e18));
    ll a, b, c;
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        adj[a][b] = min(adj[a][b], c);
    }
    adj = mat_exp(adj, k, n);
    if (adj[1][n] == 2e18)
        cout << -1 << "\n";
    else
        cout << adj[1][n] << "\n";
    return 0;
}
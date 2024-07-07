// Same as that of weighted tree
// NOTE : All weights >= 0

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;

vl dp1, dp2;
void dfs(ll s, ll e, vector<pll> adj[])
{
    if (adj[s].size() == 1 && e > 0)
    {
        dp1[s] = 0;
        dp2[s] = 0;
        return;
    }
    for (auto &[x, w] : adj[s])
    {
        if (x == e)
            continue;
        dfs(x, s, adj);
    }
    vl ans;
    for (auto &[x, w] : adj[s])
    {
        if (x == e)
            continue;
        ans.push_back(dp1[x] + w);
    }
    sort(ans.begin(), ans.end(), greater<ll>());
    dp1[s] = ans[0];
    if (ans.size() > 1)
        dp2[s] = ans[0] + ans[1];
}

int main()
{
    ll n;
    cin >> n;
    vector<pll> adj[n + 1];
    ll ans = 0;
    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        ans += 2 * c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    dp1.assign(n + 1, 0), dp2.assign(n + 1, 0);
    dfs(1, 0, adj);
    ll dia = 0;
    for (ll i = 1; i <= n; i++)
        dia = max(dia, max(dp1[i], dp2[i]));
    ans -= dia;
    cout << ans << "\n";
    return 0;
}
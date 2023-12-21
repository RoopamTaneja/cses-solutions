#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
struct project
{
    ll s, e, p;
};
bool comp(project &p1, project &p2)
{
    return p1.e <= p2.e;
}
void solve()
{
    ll n;
    cin >> n;
    vector<project> proj(n + 1);
    for (ll i = 1; i <= n; i++)
        cin >> proj[i].s >> proj[i].e >> proj[i].p;
    sort(proj.begin() + 1, proj.end(), comp);
    vl e(n + 1);
    for (ll i = 1; i <= n; i++)
        e[i] = proj[i].e;
    vl dp(n + 1, 0);
    dp[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1];
        ll j = distance(e.begin(), lower_bound(e.begin(), e.end(), proj[i].s)) - 1;
        dp[i] = max(proj[i].p + dp[j], dp[i]);
    }
    cout << dp[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
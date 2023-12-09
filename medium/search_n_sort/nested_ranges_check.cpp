#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

bool comp(pair<pll, ll> p1, pair<pll, ll> p2)
{
    if (p1.first.first < p2.first.first)
        return true;
    if (p1.first.first == p2.first.first && p1.first.second > p2.first.second)
        return true;
    return false;
}

void solve()
{
    ll n, a, b;
    vector<pair<pll, ll>> v;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> a >> b;
        v.eb(mp(mp(a, b), i));
    }
    sort(all(v), comp);
    ll maxRt = -1;
    ll minRt = 1e9 + 5;
    vector<bool> contained(n, 0), contains(n, 0);
    for (auto &p : v)
    {
        if (p.first.second <= maxRt)
            contained[p.second] = 1;
        maxRt = max(maxRt, p.first.second);
    }
    for (ll i = v.size() - 1; i >= 0; i--)
    {
        auto p = v[i];
        if (p.first.second >= minRt)
            contains[p.second] = 1;
        minRt = min(minRt, p.first.second);
    }
    for (auto i : contains)
        cout << i << " ";
    cout << "\n";
    for (auto j : contained)
        cout << j << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
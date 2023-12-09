#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
#define mp make_pair
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
    vl contained(n, 0), contains(n, 0);
    ordered_set<ll> s;
    s.insert(v[0].first.second);
    for (ll i = 1; i < n; i++)
    {
        auto p = v[i];
        contained[p.second] = s.size() - s.order_of_key(p.first.second);
        s.insert(p.first.second);
    }
    s.clear();
    s.insert(v[n - 1].first.second);
    for (ll i = n - 2; i >= 0; i--)
    {
        auto p = v[i];
        contains[p.second] = s.order_of_key(p.first.second + 1);
        s.insert(p.first.second);
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
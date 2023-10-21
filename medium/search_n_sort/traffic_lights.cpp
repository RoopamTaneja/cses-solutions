#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;

void solve()
{
    ll x, n, entry;
    vl v;
    cin >> x >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    set<ll> list;
    list.insert(0);
    list.insert(x);
    multiset<ll> diff;
    diff.insert(x);
    for (ll i = 0; i < n; i++)
    {
        auto it = list.lower_bound(v[i]);
        auto it2 = it;
        it2--;
        list.insert(v[i]);
        diff.erase(diff.find(*it - *it2));
        diff.insert(*it - v[i]);
        diff.insert(v[i] - *it2);
        auto max_val = diff.end();
        max_val--;
        cout << *max_val << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
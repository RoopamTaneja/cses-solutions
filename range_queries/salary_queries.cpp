#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve()
{
    ll n, entry, q;
    vl v;
    cin >> n >> q;
    ordered_set<pll> s;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
        s.insert(mp(entry, i));
    }
    char c;
    ll a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> c >> a >> b;
        if (c == '?')
            cout << s.order_of_key(mp(b + 1, -1)) - s.order_of_key(mp(a, -1)) << "\n";
        else
        {
            ll val = v[a - 1];
            v[a - 1] = b;
            s.erase(mp(val, a - 1));
            s.insert(mp(b, a - 1));
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
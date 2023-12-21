#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

// Pairs
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve()
{
    ll n, entry;
    vl v;
    cin >> n;
    ordered_set<ll> s;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        s.insert(i);
        v.eb(entry);
    }
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        auto it = s.find_by_order(--entry);
        ll ind = *it;
        s.erase(it);
        cout << v[ind] << " ";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
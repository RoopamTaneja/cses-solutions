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

void solve()
{
    ll n, entry;
    vl v;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    sort(all(v));
    ll ans = 1;
    for (auto &x : v)
    {
        if (x > ans)
            break;
        ans += x;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
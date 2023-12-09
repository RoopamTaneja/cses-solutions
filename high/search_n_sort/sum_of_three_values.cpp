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

void triplet(ll x, ll n, vector<pll> &v)
{
    ll j, k;
    sort(all(v));
    for (ll i = 0; i < n - 2; i++)
    {
        j = i + 1, k = n - 1;
        ll val = x - v[i].first;
        while (j < k)
        {
            if (v[j].first + v[k].first < val)
            {
                j++;
            }
            else if (v[j].first + v[k].first > val)
            {
                k--;
            }
            else
            {
                cout << v[i].second << " " << v[j].second << " " << v[k].second << "\n";
                return;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main()
{
    ll n, x, entry;
    cin >> n >> x;
    vector<pll> v;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(mp(entry, i + 1));
    }
    triplet(x, n, v);
    return 0;
}
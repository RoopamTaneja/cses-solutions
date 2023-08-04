#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

int main()
{
    vl v;
    ll n, entry;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    ll ans = 0;
    for (int i = 1; i < n; i++)
    {
        ll diff = v[i] - v[i - 1];
        if (diff < 0)
        {
            v[i] += abs(diff);
            ans += abs(diff);
        }
    }
    cout << ans;
    return 0;
}
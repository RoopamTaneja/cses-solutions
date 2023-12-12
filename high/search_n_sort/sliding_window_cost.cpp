#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

void solve()
{
    ll n, entry, k;
    vl v;
    cin >> n >> k;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    multiset<ll> low, upp;
    if (k == 1)
    {
        for (auto &i : v)
            cout << 0 << " ";
        cout << "\n";
    }
    else if (k == 2)
    {
        for (ll i = 0; i < n - 1; i++)
            cout << abs(v[i] - v[i + 1]) << " ";
        cout << "\n";
    }
    else
    {
        vl st;
        for (ll i = 0; i < k; i++) // initializing the sets
            st.eb(v[i]);
        sort(all(st));
        for (ll i = 0; i < (k + 1) / 2; i++)
            low.insert(st[i]);
        for (ll i = (k + 1) / 2; i < k; i++)
            upp.insert(st[i]);
        ll low_sum = accumulate(all(low), 0LL);
        ll upp_sum = accumulate(all(upp), 0LL);
        ll ans = upp_sum - low_sum;
        if (k % 2)
            ans += *low.rbegin();
        cout << ans << " ";
        // shifting windows
        ll low_sz = (k + 1) / 2;
        for (ll i = k; i < n; i++)
        {
            auto lit = low.find(v[i - k]);
            if (lit != low.end())
                low.erase(lit), low_sum -= v[i - k];
            else
                upp.erase(upp.find(v[i - k])), upp_sum -= v[i - k];
            if (v[i] <= *low.rbegin())
                low.insert(v[i]), low_sum += v[i];
            else
                upp.insert(v[i]), upp_sum += v[i];
            while (low.size() > low_sz)
            {
                ll val = *low.rbegin();
                low.erase(low.find(val)), low_sum -= val;
                upp.insert(val), upp_sum += val;
            }
            while (low.size() < low_sz)
            {
                auto it = upp.begin();
                ll val = *it;
                upp.erase(it), upp_sum -= val;
                low.insert(val), low_sum += val;
            }
            ans = upp_sum - low_sum;
            if (k % 2)
                ans += *low.rbegin();
            cout << ans << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
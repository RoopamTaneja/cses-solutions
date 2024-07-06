// Linearity of expectation :
// Xij = 1 if v[i] > v[j], 0 otherwise
// No of inversions => X = Sum of Xij over all i, j st i<j
// E(X) = Sum of E(Xij) over all i, j st i<j (linearity yes, symmetry no)
// E(Xij) = P(i, j form an inversion)
// P(i, j) easy to find by some casework :
//  Total outcomes = v[i]*v[j]
//  Favourable outcomes : 2nd no = 1, 1st no = (2 .. v[i]) -> v[i] - 1 options
//  2nd no = 2, 1st no = (3 .. v[i]) -> v[i] - 2 options
//  ... 2nd no = val, 1st no = (val+1..v[i]) -> v[i] - val options
// where val = min(v[j], v[i] - 1).
// Find P(i, j) individually and sum over all pairs to get the answer

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef long double ld;

int main()
{
    ll n;
    cin >> n;
    vl v(n);
    for (auto &x : v)
        cin >> x;
    ld ans = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            ll val = min(v[i] - 1, v[j]);
            ld num = v[i] * val - val * (val + 1) / 2;
            ll deno = v[i] * v[j];
            ans += num / deno;
        }
    }
    // rounding to 6 decimal places
    ans *= 1e6;
    if (ans - (ll)ans == 0.5l) // rounding half to even
    {
        ll val = (ll)ans;
        if (val % 2)
            val++;
        ans = val;
    }
    else
        ans = llround(ans);
    ans /= 1e6;
    cout << fixed << setprecision(6) << ans << "\n"; // 6 decimals
    return 0;
}
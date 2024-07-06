#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
const int MOD = 1e9 + 7;
using Matrix = array<array<ll, 6>, 6>;

Matrix mul(Matrix a, Matrix b)
{
    Matrix res = {{{0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0}}};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < 6; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
    return res;
}

Matrix mat_exp(Matrix a, ll b)
{
    Matrix res = {{{1, 0, 0, 0, 0, 0},
                   {0, 1, 0, 0, 0, 0},
                   {0, 0, 1, 0, 0, 0},
                   {0, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 1}}};
    while (b > 0)
    {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int main()
{
    ll n;
    cin >> n;
    ll dp[6] = {1, 1, 2, 4, 8, 16};
    Matrix a = {{{0, 1, 0, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0},
                 {0, 0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 1, 0},
                 {0, 0, 0, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1}}};
    a = mat_exp(a, n);
    ll new_dp[6] = {0, 0, 0, 0, 0, 0};
    for (ll i = 0; i < 6; i++)
        for (ll j = 0; j < 6; j++)
        {
            new_dp[i] += dp[j] * a[i][j];
            new_dp[i] %= MOD;
        }
    cout << new_dp[0] << "\n";
    return 0;
}
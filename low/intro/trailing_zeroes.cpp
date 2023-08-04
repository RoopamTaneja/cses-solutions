#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, pow2 = 0, pow5 = 0;
    cin >> n;
    int temp = n;
    while (n > 0)
    {
        n /= 5;
        pow5 += n;
    }
    // though pow2 is not needed since pow2 >= pow5 always
    while (temp > 0)
    {
        temp /= 2;
        pow2 += temp;
    }
    cout << min(pow2, pow5);
}
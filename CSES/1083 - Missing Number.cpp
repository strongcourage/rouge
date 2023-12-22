/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll n; cin >> n;
  ll s1 = n * (n + 1) / 2;
  ll s2 = 0;
  for (int i = 1; i <= n - 1; ++i) {
    ll a; cin >> a;
    s2 += a;
  }
  cout << s1 - s2 << endl;
}

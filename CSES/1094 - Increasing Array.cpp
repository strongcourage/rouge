/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  ll ans = 0, last = 0;
  for (int i = 0; i < n; ++i) {
    ll a; cin >> a;
    if (a < last)
      ans += (last - a);
    else last = a;
  }
  cout << ans << endl;
}

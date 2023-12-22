/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  vector<ll> arr(n), pref(n + 1);
  for (int i = 0; i < n; ++i) cin >> arr[i];
  pref[0] = 0;
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + arr[i - 1];
  }
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    cout << pref[b] - pref[a - 1] << endl;
  }
}

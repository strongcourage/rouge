/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    string s; cin >> s;
    int left = 0, right = n - 1;
    if (n == 1) {
      cout << 1 << endl;
      continue;
    }
    int i = 0;
    while (left <= right and s[left] != s[right]) {
      i += 2;
      left += 1;
      right -= 1;
    }
    cout << n - i << endl;
  }
}

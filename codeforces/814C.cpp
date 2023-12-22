/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;

int solve(string s, char c, int m) {
  int n = s.size();
  int left = 0, right = 0;
  int max_freq = 0, ans = 0;
  while (left <= right and right < n) {
    char end = s[right];
    right += 1;
    if (end == c) max_freq += 1;
    while (right - left - max_freq > m) {
      char start = s[left];
      left += 1;
      if (start == c) max_freq -= 1;
    }
    ans = max(ans, right - left);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  string s; cin >> s;
  int q; cin >> q;
  while (q--) {
    int m; char c; cin >> m >> c;
    cout << solve(s, c, m) << endl;
  }
}

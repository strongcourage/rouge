/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  string s; cin >> s;
  int left = 0, right = 0;
  unordered_map<char, int> freq, window;
  int num_distinct = 0;
  for (char c : s) {
    freq[c] += 1;
    if (freq[c] == 1) num_distinct += 1;
  }
  int cur_distinct = 0, ans = INT_MAX;
  while (right < n) {
    char end = s[right];
    right += 1;
    window[end] += 1;
    if (window[end] == 1) cur_distinct += 1;
    while (left < right and cur_distinct == num_distinct) {
      ans = min(ans, right - left);
      char start = s[left];
      left += 1;
      window[start] -= 1;
      if (window[start] == 0) cur_distinct -= 1;
    }
  }
  cout << ans << endl;
}

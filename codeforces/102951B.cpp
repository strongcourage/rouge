/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int N, X; cin >> N >> X;
  vector<int> arr(N);
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }
  sort(arr.begin(), arr.end());
  int ans = 0, cur_mins = 0;
  for (int i = 0; i < N; ++i) {
    cur_mins += arr[i];
    if (cur_mins <= X) {
      ans += 1;
    } else {
      break;
    }
  }
  cout << ans << endl;
}

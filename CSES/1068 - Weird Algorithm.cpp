/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  long long n; cin >> n;
  vector<long long> ans;
  if (n == 1) {
    cout << "1" << endl;
    return 0;
  }
  ans.push_back(n);
  while (n != 1) {
    if (n % 2 == 1) n = n * 3 + 1;
    else n /= 2;
    ans.push_back(n);
  }
  for (auto i : ans) cout << i << " ";
  cout << endl;
}

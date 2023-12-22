/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;
const int MAXN = 100010;
vector<ll> arr(MAXN), sum(MAXN * 4);

void build(int id, int l, int r) {
  if (l == r) {
    sum[id] = arr[l];
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

int get(int id, int l, int r, int k) {
  if (l == r) {
    return l; // Return the index of the k-th one
  }

  int mid = (l + r) / 2;
  if (k < sum[id * 2]) {
    return get(id * 2, l, mid, k);
  } else {
    return get(id * 2 + 1, mid + 1, r, k - sum[id * 2]);
  }
}

void update(int id, int l, int r, int pos) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    arr[pos] ^= 1;
    sum[id] = arr[pos];
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos);
  update(id * 2 + 1, mid + 1, r, pos);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  build(1, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int t, k; cin >> t >> k;
    if (t == 1) update(1, 0, n - 1, k);
    if (t == 2) cout << get(1, 0, n - 1, k) << endl;
  } 
}

/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
vector<ll> arr(MAXN), segtree(MAXN * 4);

void build(int id, int l, int r) {
  if (l == r) {
    segtree[id] = arr[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  segtree[id] = min(segtree[id * 2], segtree[id * 2 + 1]);
}

ll get(int id, int l, int r, int u, int v) {
  if (r < u || v < l) return LLONG_MAX;
  if (u <= l && r <= v) return segtree[id];

  int mid = (l + r) / 2;
  ll min_left = get(id * 2, l, mid, u, v);
  ll min_right = get(id * 2 + 1, mid + 1, r, u, v);
  return min(min_left, min_right);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  build(1, 0, n - 1);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    cout << get(1, 0, n - 1, a - 1, b - 1) << endl;
  }
}

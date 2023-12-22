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
  if (v < l || r < u) return LLONG_MAX;
  if (u <= l && r <= v) return segtree[id];

  int mid = (l + r) / 2;
  ll min_left = get(id * 2, l, mid, u, v);
  ll min_right = get(id * 2 + 1, mid + 1, r, u, v);
  return min(min_left, min_right);
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) {
    arr[pos] = val;
    segtree[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  segtree[id] = min(segtree[id * 2], segtree[id * 2 + 1]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  build(1, 1, n);
  for (int i = 0; i < q; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int k; ll u; cin >> k >> u;
      update(1, 1, n, k, u);
    }
    if (t == 2) {
      int a, b; cin >> a >> b;
      cout << get(1, 1, n, a, b) << endl;
    }
  }
}

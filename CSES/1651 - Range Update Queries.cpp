/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
vector<ll> arr(MAXN), segtree(MAXN * 4), lazy(MAXN * 4);

void build(int id, int l, int r) {
  if (l == r) {
    segtree[id] = arr[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  segtree[id] = segtree[id * 2] + segtree[id * 2 + 1];
}

void push(int id, int l, int r) {
  if (lazy[id] != 0) {
    segtree[id] += (r - l + 1) * lazy[id];

    if (l != r) {
      lazy[id * 2] += lazy[id];
      lazy[id * 2 + 1] += lazy[id];
    }

    lazy[id] = 0;
  }
}

ll get(int id, int l, int r, int k) {
  push(id, l, r);

  if (l == r) return segtree[id];

  int mid = (l + r) / 2;
  if (k <= mid)
    return get(id * 2, l, mid, k);
  else
    return get(id * 2 + 1, mid + 1, r, k);
}

void updateLazy(int id, int l, int r, int u, int v, ll val) {
  push(id, l, r);

  if (v < l || r < u) return;
  if (u <= l && r <= v) {
    segtree[id] += (r - l + 1) * val;

    if (l != r) {
      lazy[id * 2] += val;
      lazy[id * 2 + 1] += val;
    }

    return;
  }

  int mid = (l + r) / 2;
  updateLazy(id * 2, l, mid, u, v, val);
  updateLazy(id * 2 + 1, mid + 1, r, u, v, val);
  segtree[id] = segtree[id * 2] + segtree[id * 2 + 1];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  build(1, 1, n);
  for (int i = 0; i < q; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int a, b; ll u; cin >> a >> b >> u;
      updateLazy(1, 1, n, a, b, u);
    }
    if (t == 2) {
      int k; cin >> k;
      cout << get(1, 1, n, k) << endl;
    }
  }
}

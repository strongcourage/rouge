/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
int nn;
vector<ll> arr(MAXN), segtree(MAXN * 4);

int level(int id) {
  return int(log2(id));
}

void build(int id, int l, int r) {
  if (l == r) {
    segtree[id] = arr[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  int lv = level(id);
  if (lv % 2 != nn % 2) {
    segtree[id] = segtree[id * 2] | segtree[id * 2 + 1];
  } else {
    segtree[id] = segtree[id * 2] ^ segtree[id * 2 + 1];
  }
}

ll get(int id, int l, int r, int u, int v) {
  if (v < l || r < u) return 0;
  if (u <= l && r <= v) return segtree[id];

  int mid = (l + r) / 2;
  ll left = get(id * 2, l, mid, u, v);
  ll right = get(id * 2 + 1, mid + 1, r, u, v);
  int lv = level(id);
  if (lv % 2 != nn % 2) return left | right;
  return left ^ right;
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
  int lv = level(id);
  if (lv % 2 != nn % 2) segtree[id] = segtree[id * 2] | segtree[id * 2 + 1];
  else segtree[id] = segtree[id * 2] ^ segtree[id * 2 + 1];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int m; cin >> nn >> m;
  int n = pow(2, nn);
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  build(1, 1, n);
  for (int i = 0; i < m; ++i) {
    int p, b; cin >> p >> b;
    update(1, 1, n, p, b);
    cout << get(1, 1, n, 1, n) << endl;
  }
}

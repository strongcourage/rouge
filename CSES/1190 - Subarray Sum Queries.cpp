/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
vector<ll> arr(MAXN);

struct Node {
  ll sum;
  ll max_pref;
  ll max_suff;
  ll max_sum;
};

Node segtree[4 * MAXN];

void merge(int id) {
  segtree[id].sum = segtree[id * 2].sum + segtree[id * 2 + 1].sum;
  segtree[id].max_pref = max(segtree[id * 2].max_pref, 
                            segtree[id * 2].sum + segtree[id * 2 + 1].max_pref);
  segtree[id].max_suff = max(segtree[id * 2 + 1].max_suff, 
                            segtree[id * 2].max_suff + segtree[id * 2 + 1].sum);
  segtree[id].max_sum = max({segtree[id * 2].max_sum, segtree[id * 2 + 1].max_sum,
                            segtree[id * 2].max_suff + segtree[id * 2 + 1].max_pref});
}

void build(int id, int l, int r) {
  if (l == r) {
    segtree[id].sum = arr[l];
    segtree[id].max_pref = arr[l];
    segtree[id].max_suff = arr[l];
    segtree[id].max_sum = arr[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  merge(id);
}

Node get(int id, int l, int r, int u, int v) {
  if (v < l || r < u) {
    Node tmp;
    tmp.sum = tmp.max_pref = tmp.max_suff = tmp.max_sum = 0;
    return tmp;
  }
  if (u <= l && r <= v) return segtree[id];

  int mid = (l + r) / 2;
  Node left = get(id * 2, l, mid, u, v);
  Node right = get(id * 2 + 1, mid + 1, r, u, v);
  Node res;
  res.sum = left.sum + right.sum;
  res.max_pref = max(left.max_pref, left.sum + right.max_pref);
  res.max_suff = max(right.max_suff, left.max_suff + right.sum);
  res.max_sum = max({left.max_sum, right.max_sum, left.max_suff + right.max_pref});
  return res;
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) {
    segtree[id].sum = val;
    segtree[id].max_pref = val;
    segtree[id].max_suff = val;
    segtree[id].max_sum = val;
    return;
  }
  
  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  merge(id);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  build(1, 1, n);
  for (int i = 1; i <= q; ++i) {
    int k; ll x; cin >> k >> x;
    update(1, 1, n, k, x);
    cout << max(0LL, get(1, 1, n, 1, n).max_sum) << endl;
  }
}
